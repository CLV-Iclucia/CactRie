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
  explicit FuncParameter(const std::string &function_name, const CactBasicType return_type) :
    CactConstVar(function_name, return_type, true, false) {}
};

// a list of function parameters
typedef std::vector<FuncParameter> FuncParameters;

// a function in the Cact language
struct CactFunction {
  CactBasicType return_type; // return type
  std::string name; // function name
  FuncParameters parameters; // parameters

  // set up name and return type
  void init(const std::string &function_name, CactBasicType return_type) {
    this->name = function_name;
    this->return_type = return_type;
  }

  // add a new parameter
  void addParameter(FuncParameter new_parameter) {
    // check if parameter name is used
    for (auto &p : this->parameters)
      if (p.name == new_parameter.name)
        throw std::runtime_error("duplicate parameter name");

    this->parameters.emplace_back(new_parameter);
  }
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
