//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRY_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRY_H_
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cact-front-end/cact-constant-variable.h>
#include <cact-front-end/cact-functions.h>
#include <cact-front-end/mystl/observer_ptr.h>

namespace cactfrontend {

struct SymbolRegistry;

// A scope in the symbol table
struct Scope {
  std::string scopeName; // the name of a function scope (if any)
  // register a variable in the scope
  void registerVariable(const CactConstVar symbol) {
    // check if variable with same name is already in the scope
    if (this->findVarLocal(symbol.name))
      throw std::runtime_error("conflicting declaration ‘" + symbol.toString() + "’");

    this->variableVec.emplace_back(std::make_shared<CactConstVar>(symbol));
    this->variableMap.insert({symbol.name, this->variableVec.size() - 1});
  }

  // set the parent scope
  void setParent(observer_ptr<Scope> parent) {
    this->parent = parent;
  }

  // set the parent scope
  [[nodiscard]]
  observer_ptr<Scope> getParent() const {
    return this->parent;
  }

  // find a variable in the scope
  [[nodiscard]]
  bool findVarLocal(const std::string &name) const {
    return this->variableMap.contains(name);
  }

  // get a variable in the scope
  [[nodiscard]]
  std::shared_ptr<CactConstVar> getVariable(const std::string &name) {
    auto scope = make_observer(this);
    // search for the variable in the current scope, its parent, grandparent, and so on, until the global scope
    do {
      if (scope->findVarLocal(name))
        return scope->variableVec[scope->variableMap.at(name)];
      scope = scope->parent;
    } while (scope.get());
    throw std::runtime_error("Variable not found: " + name);
  }

private:
  observer_ptr<Scope> parent{}; // the parent scope
  std::map<std::string, int> variableMap; // variable ID map
  std::vector<std::shared_ptr<CactConstVar>> variableVec; // variables
};

// A symbol registry
struct SymbolRegistry {
  // // constructor
  // SymbolRegistry() : scopes(std::vector<std::unique_ptr<Scope>>()), scopeID(std::map<std::string, int>()), functions(std::vector<CactFunction>()), functionID(std::map<std::string, int>()) {}

  // create a new scope
  [[nodiscard]]
  observer_ptr<Scope> newScope() {
    scopes.emplace_back(std::make_unique<Scope>());
    return make_observer(scopes.back().get());
  }

  // return the global scope
  [[nodiscard]]
  observer_ptr<Scope> createGlobalScope() {
    globalScope = newScope();
    return globalScope;
  }

  // return the global scope
  [[nodiscard]]
  observer_ptr<Scope> getGlobalScope() {
    return globalScope;
  }

  // return the function scope
  [[nodiscard]]
  observer_ptr<Scope> getScopeByFunc(const std::string &name) {
    return make_observer(scopes[scopeID.at(name)].get());
  }

  // create a new function
  observer_ptr<CactFunction> newFunction(std::string name, CactBasicType return_type) {
    // check if function with same name is already in the scope
    if (functionID.contains(name))
      throw std::runtime_error("‘" + func2String(name) + "’ cannot be overloaded");

    functions.emplace_back(std::make_unique<CactFunction>());
    functionID.insert({name, functions.size() - 1});

    auto func = make_observer(functions.back().get());
    func->init(name, return_type);
    return func;
  }

  // create a new function
  observer_ptr<CactFunction> newFunction(std::string name, CactBasicType return_type, FuncParameters params) {
    auto func = newFunction(name, return_type);

    for (auto &param : params)
      func->addParameter(param);

    return func;
  }

  // get a function by name
  [[nodiscard]]
  observer_ptr<CactFunction> getFunction(const std::string &name) {
    // check if function with same name is not defined
    if (!functionID.contains(name))
      return make_observer<CactFunction>(nullptr);
    return make_observer(functions[functionID.at(name)].get());
  }

  // function name and type to string
  [[nodiscard]]
  std::string func2String(const std::string &name) {
    auto func = getFunction(name);

    // check if function with same name is not defined
    if (!func)
      return nullptr;

    std::string result = type2String(func->return_type) + " " + name + "(";
    // print all parameters
    for (auto &param : func->parameters) {
      result += param.type.toStringFull() + param.name;
      if (&param != &func->parameters.back())
        result += ", ";
    }

    result += ")";
    return result;
  }

private:
  observer_ptr<Scope> globalScope; // global scope
  std::map<std::string, int> scopeID; // function name to scope index
  std::vector<std::unique_ptr<Scope>> scopes; // scopes
  std::map<std::string, int> functionID; // function name to index
  std::vector<std::unique_ptr<CactFunction>> functions; // functions
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRY_H_
