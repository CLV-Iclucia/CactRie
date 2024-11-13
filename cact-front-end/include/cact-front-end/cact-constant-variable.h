//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
#include <cact-front-end/cact-expr.h>
#include <string>

namespace cactfrontend {

// a constant or variable in the Cact language
struct CactConstVar {
  CactType type; // the type of the variable
  bool isConst{}; // const type
  bool initialized{}; // initialized or not
  // ExpressionResult value; // the type value

  // construct a variable with a type
  // explicit CactConstVar(const CactType& type) : value(type) {}

  // construct a constant
  void constInit(CactBasicType basicType) {
    this->type.init(basicType, false);
    this->isConst = initialized = true;
  }

  // construct a variable
  void varInit(CactBasicType basicType) {
    this->type.init(basicType, false);
    this->isConst = initialized = false;
  }

  void paramInit(CactBasicType basicType) {
    this->type.init(basicType, true);
    this->isConst = initialized = false;
  }

  // check if this type is a valid left value in an assignment statement
  [[nodiscard]]
  bool isValidLValue() const {
    return this->type.validOperandType() && !this->isConst;
  }


};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
