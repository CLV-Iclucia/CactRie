//
// Created by creeper on 8/15/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#include <cact-front-end/cact-type.h>
#include <cact-front-end/cact-constant-variable.h>
#include <string>
#include <vector>

namespace cactfrontend {


// a list of function parameters
typedef std::vector<CactFuncParam> FuncParameters;

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
  void addParameter(CactFuncParam new_parameter) {
    // check if parameter name is used
    for (auto &p : this->parameters)
      if (p.name == new_parameter.name)
        throw std::runtime_error("duplicate parameter name");

    this->parameters.emplace_back(new_parameter);
  }
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
