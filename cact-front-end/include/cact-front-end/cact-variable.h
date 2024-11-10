//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_VARIABLE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_VARIABLE_H_
#include <cact-front-end/cact-expr.h>
#include <string>

namespace cactfrontend {

// a variable in the Cact language
struct CactVariable {
  // construct a variable with a type
  explicit CactVariable(const CactType& type) : value(type) {}

  ExpressionResult value; // the type value

  // get the type from the variable
  [[nodiscard]] CactType type() const {
    return value.type();
  }
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_VARIABLE_H_
