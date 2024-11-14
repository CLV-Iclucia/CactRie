//
// Created by creeper on 8/15/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#include <cact-front-end/cact-type.h>
#include <cact-front-end/cact-constant-variable.h>
// #include <functional>
#include <string>

namespace cactfrontend {

// a parameter in the function definition
struct FuncParameter : CactConstVar {
  // constructor
  explicit FuncParameter() = default;
  explicit FuncParameter(const std::string &funcName, const CactBasicType retType) :
    CactConstVar(funcName, retType, true, false) {}
};

// a list of function parameters
typedef std::vector<FuncParameter> FuncParameters;

// a function in the Cact language
struct CactFunction {
  CactBasicType returnType; // return type
  std::string name; // function name
  FuncParameters parameters; // parameters

  // set up name and return type
  void init(const std::string &funcName, CactBasicType retType) {
    this->name = std::move(funcName);
    this->returnType = retType;
  }

  // add a new parameter
  void addParameter(FuncParameter newParam) {
    // check if parameter name is used
    for (auto &p : this->parameters)
      if (p.name == newParam.name)
        throw std::runtime_error("duplicate parameter name");

    this->parameters.emplace_back(newParam);
  }
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
