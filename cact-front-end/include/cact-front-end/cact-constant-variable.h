//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_

#include <cact-front-end/cact-typedef.h>
#include <cact-front-end/cact-type.h>
#include <string>
#include <vector>
#include <iostream>

namespace cactfrontend {

struct CactConstVar;
struct CactConstant;
struct CactVariable;
struct CactFuncParam;

struct CactConstVar {
  std::string name;
  CactType type;
  std::vector<ConstEvalResult> init_values; // the initial values

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

  // is constant
  [[nodiscard]]
  bool isConstant() const {
    return this->is_const;
  }

  // check if the variable is initialized
  [[nodiscard]]
  bool isInitialized() const {
    return this->initialized;
  }

protected:
  bool is_const{}; // if is const type
  bool initialized{}; // initialized or not, defaultly false for variable
};

void printInitValues(CactConstVar &symbol);

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

// a parameter in the function definition
struct CactFuncParam : CactConstVar {
  // constructor
  explicit CactFuncParam() = default;
  explicit CactFuncParam(const std::string &function_name, const CactBasicType return_type) :
    CactConstVar(function_name, return_type, true, false) {}
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
