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
  std::string name;
  CactType type;
  // ExpressionResult value; // the type value

  // basic constructor
  explicit CactConstVar() = default;
  explicit CactConstVar(const std::string &_name, const CactBasicType _basicType, bool _isParam, bool _isConst) :
    name(std::move(_name)), type(_basicType, _isParam), isConst(_isConst), initialized(_isConst) {}

  // check if this type is a modifiable left value
  [[nodiscard]]
  bool isModifiableLValue() const {
    return this->type.validOperandType() && !this->isConst;
  };

  // convert the variable to a string
  [[nodiscard]]
  std::string toString() const {
    return (this->isConst ? "const " : "") + this->type.toString() + " " + this->name;
  }

protected:
  bool isConst{}; // if is const type
  bool initialized{}; // initialized or not, defaultly false for variable
};

struct CactConstant : CactConstVar {
  // constructor
  explicit CactConstant() = default;
  explicit CactConstant(const std::string &constName, const CactBasicType basicType) :
    CactConstVar(constName, basicType, false, true) {}
};

struct CactVariable : CactConstVar {
  // constructor
  explicit CactVariable() = default;
  explicit CactVariable(const std::string &varName, const CactBasicType basicType) :
    CactConstVar(varName, basicType, false, false) {}

  // set the initialized flag for the variable
  void setInitialized() {
    this->initialized = true;
  }
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
