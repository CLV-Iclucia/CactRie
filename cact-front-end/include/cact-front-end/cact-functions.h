//
// Created by creeper on 8/15/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#include <cact-front-end/cact-type.h>
#include <string>
namespace cactfrontend {

struct FormalParameter {
  CactType type;
  std::string name;
  [[nodiscard]] bool valid() const {
    return type.validFormalParameterType();
  }
};

struct FormalParameters {
  std::vector<FormalParameter> parameters;
};

struct CactFunction {
  FormalParameters parameters;
  CactType returnType;
  bool isPure{};
};


}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
