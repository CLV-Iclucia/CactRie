//
// Created by creeper on 8/15/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#include <cact-front-end/cact-type.h>
#include <string>

namespace cactfrontend {

// a parameter in the function definition
struct FuncParameter {
  CactBasicType basicType{}; // basic type
  std::string name; // parameter name
  std::vector<uint32_t> arrayDims{}; // array dimensions as a vector

  // // check if the parameter type is valid
  // [[nodiscard]] bool valid() const {
  //   // dummy, need to be implemented
  //   return basicType != CactBasicType::Unknown && basicType != CactBasicType::Void;
  // }
};

// a list of function parameters
typedef std::vector<FuncParameter> FuncParameters;

// a function in the Cact language
struct CactFunction {
  CactBasicType returnType; // return type
  std::string name; // function name
  FuncParameters parameters; // parameters
  // bool isPure{}; // is the function pure
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
