//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_LUT_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_LUT_H_
#include <ranges>
#include <vector>
#include <map>
#include <string>
#include <cact-front-end/cact-constant-variable.h>
#include <cact-front-end/cact-functions.h>
#include <cact-front-end/mystl/observer_ptr.h>

namespace cactfrontend {

struct SymbolRegistry;

// A scope in the symbol table
struct Scope {
  std::string name; // the name of a function scope (if any)

  // register a variable in the scope
  void registerVariable(const std::string &name, const CactConstVar &symbol) {
    variables.emplace_back(symbol);
    variableID.insert({name, variables.size() - 1});
  }

  // set the parent scope
  void setParent(observer_ptr<Scope> parent) {
    this->parent = parent;
  }

  // set the parent scope
  [[nodiscard]]
  observer_ptr<Scope> getParent() {
    return this->parent;
  }

  // find a variable in the scope
  [[nodiscard]]
  bool find(const std::string &name) const {
    return variableID.contains(name);
  }

  // get a variable in the scope
  [[nodiscard]]
  CactConstVar &variable(const std::string &name) {
    auto scope = make_observer(this);
    while (scope->parent) {
      if (variableID.contains(name))
        return variables[variableID.at(name)];
      scope = scope->parent;
    }
    throw std::runtime_error("Variable not found");
  }

private:
  observer_ptr<Scope> parent; // the parent scope
  std::map<std::string, int> variableID; // variable ID map
  std::vector<CactConstVar> variables; // variables
};

// A symbol registry
struct SymbolRegistry {
  // // constructor
  // SymbolRegistry() : scopes(std::vector<std::unique_ptr<Scope>>()), scopeID(std::map<std::string, int>()), functions(std::vector<CactFunction>()), functionID(std::map<std::string, int>()) {}

  // create a new scope
  [[nodiscard]]
  observer_ptr<Scope> newScope() {
    scopes.push_back(std::make_unique<Scope>());
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
  observer_ptr<CactFunction> newFunction(std::string &name, CactBasicType returnType) {
    functions.push_back(std::make_unique<CactFunction>());
    functionID.insert({name, functions.size() - 1});

    auto func = make_observer(functions.back().get());
    func->init(name, returnType);
    return func;
  }

  // get a function by name
  [[nodiscard]]
  observer_ptr<CactFunction> getFunction(const std::string &name) {
    return make_observer(functions[functionID.at(name)].get());
  }

private:
  observer_ptr<Scope> globalScope; // global scope
  std::map<std::string, int> scopeID; // function name to scope index
  std::vector<std::unique_ptr<Scope>> scopes; // scopes
  std::map<std::string, int> functionID; // function name to index
  std::vector<std::unique_ptr<CactFunction>> functions; // functions
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_LUT_H_
