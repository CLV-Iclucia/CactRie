//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#include <cact-front-end/cact-expr.h>
#include <functional>
#include <set>

namespace cactfrontend {

struct OperandTypeChecker {
  const std::string error_message;
  const std::set<CactBasicType> valid_oprand_types;

  // constructor
  explicit OperandTypeChecker(const std::string __error_message, const std::set<CactBasicType> __valid_oprand_types) :
    error_message(__error_message), valid_oprand_types(__valid_oprand_types) {}

  // type check
  [[nodiscard]]
  bool inValidSet(const CactBasicType __basic_type) const {
    return valid_oprand_types.contains(__basic_type);
  }
};

// in cact-operator.cc
extern const OperandTypeChecker operand_checker_all;
extern const OperandTypeChecker operand_checker_int_float;
extern const OperandTypeChecker operand_checker_int;
extern const OperandTypeChecker operand_checker_bool;

enum class CactOperatorType {
  // Unary operators
  UnaryNop,
  Plus,
  Neg,
  LogicalNot,
  // Return,

  // Binary operators
  BinaryNop,
  Mul,
  Div,
  Mod,
  Add,
  Sub,
  Less,
  Greater,
  LessEqual,
  GreaterEqual,
  LogicalEqual,
  LogicalNotEqual,
  LogicalAnd,
  LogicalOr,
};


struct Operator {
  Operator(CactOperatorType __op_type, const OperandTypeChecker *__op_checker)
      : operator_type(__op_type), operand_type_checker(__op_checker) {}

  // check if the operand's basic type is valid
  [[nodiscard]]
  bool isValidOperandDataType(const CactBasicType basic_type) const {
    if (!this->operand_type_checker->inValidSet(basic_type)) {
      throw std::runtime_error(this->operand_type_checker->error_message);
      return false;
    }
    return true;
  }

  // check if the operand is valid
  [[nodiscard]]
  bool isValidOperand(const CactType type) const {
    if (!type.validOperandType()){
      throw std::runtime_error("expression must be a scalar");
      return false;
    }

    return isValidOperandDataType(type.basic_type);
  }

  // get the operator type
  [[nodiscard]]
  CactOperatorType getOpType() const {
    return operator_type;
  }

  [[nodiscard]]
  std::set<CactBasicType> getValidOperandTypes() const {
    return operand_type_checker->valid_oprand_types;
  }


private:
  CactOperatorType operator_type;
  const OperandTypeChecker *operand_type_checker;
};

struct UnaryOperator : Operator {
  UnaryOperator(CactOperatorType __op_type, const OperandTypeChecker *__op_checker) : Operator(__op_type, __op_checker) {}

  [[nodiscard]]
  virtual std::optional<ConstEvalResult> unaryConstCheck(const ConstEvalResult& x) const = 0;
};

struct UnaryNopOperator : UnaryOperator {
  UnaryNopOperator() : UnaryOperator(CactOperatorType::UnaryNop, &operand_checker_all) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> unaryConstCheck(const ConstEvalResult& x) const override {
    switch (constEvalResultBasicType(x)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(x)};
      case CactBasicType::Float:  return {std::get<float>(x)};
      case CactBasicType::Double: return {std::get<double>(x)};
      case CactBasicType::Bool:   return {std::get<bool>(x)};
      default:                    return std::nullopt;
    }
  }
};

struct PlusOperator : UnaryOperator {
  PlusOperator() : UnaryOperator(CactOperatorType::Plus, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> unaryConstCheck(const ConstEvalResult& x) const override {
    switch (constEvalResultBasicType(x)) {
      case CactBasicType::Int32:  return {+std::get<int32_t>(x)};
      case CactBasicType::Float:  return {+std::get<float>(x)};
      case CactBasicType::Double: return {+std::get<double>(x)};
      default:                    return std::nullopt;
    }
  }
};

struct NegOperator : UnaryOperator {
  NegOperator() : UnaryOperator(CactOperatorType::Neg, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> unaryConstCheck(const ConstEvalResult& x) const override {
    switch (constEvalResultBasicType(x)) {
      case CactBasicType::Int32:  return {-std::get<int32_t>(x)};
      case CactBasicType::Float:  return {-std::get<float>(x)};
      case CactBasicType::Double: return {-std::get<double>(x)};
      default:                    return std::nullopt;
    }
  }
};

struct LogicalNotOperator : UnaryOperator {
  LogicalNotOperator() : UnaryOperator(CactOperatorType::LogicalNot, &operand_checker_bool) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> unaryConstCheck(const ConstEvalResult& x) const override {
    switch (constEvalResultBasicType(x)) {
      case CactBasicType::Bool:   return {!std::get<bool>(x)};
      default:                    return std::nullopt;
    }
  }
};

struct BinaryOperator : Operator {
  BinaryOperator(CactOperatorType __op_type, const OperandTypeChecker *__op_checker) : Operator(__op_type, __op_checker) {}

  [[nodiscard]]
  virtual std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                          const ConstEvalResult rhs) const = 0;

  // [[nodiscard]]
  bool binaryOperandCheck(const CactType &lhs, const CactType &rhs) const {
    if (lhs.basic_type != rhs.basic_type) {
      throw std::runtime_error("operands must have the same type");
      return false;
    }
    return isValidOperand(lhs) && isValidOperand(rhs);
  }

  // check if two ConstEvalResult have the same CactBasicType 
  inline bool sameValidBasicType(const ConstEvalResult x, const ConstEvalResult y) const {
    // if the type of x/y are among validTypes
    CactBasicType xType = constEvalResultBasicType(x);

    if (isValidOperandDataType(xType)) {
      return xType == constEvalResultBasicType(y);
    }
    return false;
  }
};

struct BinaryNopOperator : BinaryOperator {
  BinaryNopOperator() : BinaryOperator(CactOperatorType::BinaryNop, &operand_checker_all) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)};
      case CactBasicType::Bool:   return {std::get<bool>(lhs)};
      default:                    return std::nullopt;
    }
  }
};

struct AddOperator : BinaryOperator {
  AddOperator() : BinaryOperator(CactOperatorType::Add, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) + std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   + std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  + std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct SubOperator : BinaryOperator {
  SubOperator() : BinaryOperator(CactOperatorType::Sub, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) - std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   - std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  - std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct MulOperator : BinaryOperator {
  MulOperator() : BinaryOperator(CactOperatorType::Mul, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) * std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   * std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  * std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct DivOperator : BinaryOperator {
  DivOperator() : BinaryOperator(CactOperatorType::Div, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) / std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   / std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  / std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct ModOperator : BinaryOperator {
  ModOperator() : BinaryOperator(CactOperatorType::Mod, &operand_checker_int) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) % std::get<int32_t>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct LogicalOrOperator : BinaryOperator {
  LogicalOrOperator() : BinaryOperator(CactOperatorType::LogicalOr, &operand_checker_bool) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Bool:   return {std::get<bool>(lhs) || std::get<bool>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct LogicalAndOperator : BinaryOperator {
  LogicalAndOperator() : BinaryOperator(CactOperatorType::LogicalAnd, &operand_checker_bool) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Bool:   return {std::get<bool>(lhs) && std::get<bool>(rhs)};
      default:                    return std::nullopt;
    }
  }
};


struct LessOperator : BinaryOperator {
  LessOperator() : BinaryOperator(CactOperatorType::Less, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) < std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   < std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  < std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct GreaterOperator : BinaryOperator {
  GreaterOperator() : BinaryOperator(CactOperatorType::Greater, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) > std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   > std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  > std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct LessEqualOperator : BinaryOperator {
  LessEqualOperator() : BinaryOperator(CactOperatorType::LessEqual, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) <= std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   <= std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  <= std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct GreaterEqualOperator : BinaryOperator {
  GreaterEqualOperator() : BinaryOperator(CactOperatorType::GreaterEqual, &operand_checker_int_float) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) >= std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   >= std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  >= std::get<double>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct EqualOperator : BinaryOperator {
  EqualOperator() : BinaryOperator(CactOperatorType::LogicalEqual, &operand_checker_all) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) == std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   == std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  == std::get<double>(rhs)};
      case CactBasicType::Bool:   return {std::get<bool>(lhs)    == std::get<bool>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct NotEqualOperator : BinaryOperator {
  NotEqualOperator() : BinaryOperator(CactOperatorType::LogicalNotEqual, &operand_checker_all) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    assert(sameValidBasicType(lhs, rhs));
    switch (constEvalResultBasicType(lhs)) {
      case CactBasicType::Int32:  return {std::get<int32_t>(lhs) != std::get<int32_t>(rhs)};
      case CactBasicType::Float:  return {std::get<float>(lhs)   != std::get<float>(rhs)};
      case CactBasicType::Double: return {std::get<double>(lhs)  != std::get<double>(rhs)};
      case CactBasicType::Bool:   return {std::get<bool>(lhs)    != std::get<bool>(rhs)};
      default:                    return std::nullopt;
    }
  }
};

struct IndexOperator : BinaryOperator {
  IndexOperator() : BinaryOperator(CactOperatorType::BinaryNop, &operand_checker_int) {}

  [[nodiscard]]
  std::optional<ConstEvalResult> binaryConstCheck(const ConstEvalResult lhs,
                                                  const ConstEvalResult rhs) const override {
    return std::nullopt;
  }
};

}


#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
