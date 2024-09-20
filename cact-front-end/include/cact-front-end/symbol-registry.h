//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_LUT_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_LUT_H_
#include <ranges>
#include <vector>
#include <map>
#include <string>
#include <cact-front-end/cact-variable.h>
#include <cact-front-end/cact-functions.h>
#include <cact-front-end/mystl/observer_ptr.h>
namespace cactfrontend {

struct SymbolRegistry;

struct Scope {
  void registerVariable(const std::string &name, const CactType &type) {
    variables.emplace_back(type);
    variableID.insert({name, variables.size() - 1});
  }
  [[nodiscard]] bool find(const std::string &name) const {
    return variableID.contains(name);
  }
  [[nodiscard]] CactVariable &variable(const std::string &name) {
    auto scope = make_observer(this);
    while (scope->parent) {
      if (variableID.contains(name))
        return variables[variableID.at(name)];
      scope = scope->parent;
    }
    throw std::runtime_error("Variable not found");
  }
private:
  observer_ptr<Scope> parent;
  std::map<std::string, int> variableID;
  std::vector<CactVariable> variables;
};

struct SymbolRegistry {
  observer_ptr<Scope> newScope() {
    scopes.push_back(std::make_unique<Scope>());
    return make_observer(scopes.back().get());
  }
  void newFunction(const std::string &name, const CactFunction &function) {
    functions.push_back(function);
    functionID.insert({name, functions.size() - 1});
  }
private:
  std::vector<std::unique_ptr<Scope>> scopes;
  std::vector<CactFunction> functions;
  std::map<std::string, int> functionID;
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_LUT_H_
