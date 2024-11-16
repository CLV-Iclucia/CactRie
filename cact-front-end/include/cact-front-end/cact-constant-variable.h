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
  explicit CactConstVar(const std::string &_name, const CactBasicType _basic_type, bool _is_param, bool _is_const) :
    name(_name), type(_basic_type, _is_param), is_const(_is_const), initialized(_is_const) {}

  // check if this type is a modifiable left value
  [[nodiscard]]
  bool isModifiableLValue() const {
    return this->type.validOperandType() && !this->is_const;
  };

  // convert the variable to a string
  [[nodiscard]]
  std::string toString() const {
    return (this->is_const ? "const " : "") + this->type.toString() + " " + this->name;
  }

protected:
  bool is_const{}; // if is const type
  bool initialized{}; // initialized or not, defaultly false for variable
};

struct CactConstant : CactConstVar {
  // constructor
  explicit CactConstant() = default;
  explicit CactConstant(const std::string &const_name, const CactBasicType basic_type) :
    CactConstVar(const_name, basic_type, false, true) {}
};

struct CactVariable : CactConstVar {
  // constructor
  explicit CactVariable() = default;
  explicit CactVariable(const std::string &var_name, const CactBasicType basic_type) :
    CactConstVar(var_name, basic_type, false, false) {}

  // set the initialized flag for the variable
  void setInitialized() {
    this->initialized = true;
  }
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
