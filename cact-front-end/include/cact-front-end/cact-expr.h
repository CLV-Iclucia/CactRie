//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
#include <cact-front-end/cact-type.h>
#include <utility>
#include <variant>
#include <memory>
#include <optional>

namespace cactfrontend {

// an alias for std::variant<int32_t, float, double>

using ConstEvalResult = std::variant<int32_t, float, double, bool>;

// // get a CactType based on the type of the variant
// inline CactType constEvalResultType(const ConstEvalResult &value) {
//   // return a CactType object based on the type of the variant
//   if (std::holds_alternative<int32_t>(value)) {
//     return CactType::constType(CactBasicType::Int32);
//   } else if (std::holds_alternative<float>(value)) {
//     return CactType::constType(CactBasicType::Float);
//   } else if (std::holds_alternative<double>(value)) {
//     return CactType::constType(CactBasicType::Double);
//   } else {
//     return CactType::constType(CactBasicType::Bool);
//   }
// }

// get the basic type of the variant
inline CactBasicType constEvalResultBasicType(const ConstEvalResult &value) {
  if (std::holds_alternative<int32_t>(value)) {
    return CactBasicType::Int32;
  } else if (std::holds_alternative<float>(value)) {
    return CactBasicType::Float;
  } else if (std::holds_alternative<double>(value)) {
    return CactBasicType::Double;
  } else if (std::holds_alternative<bool>(value)) {
    return CactBasicType::Bool;
  } else {
    return CactBasicType::Unknown;
  }
}

// get the value of the variant
inline std::optional<bool> conditionEvalResult(const ConstEvalResult &value) {
  if (constEvalResultBasicType(value) == CactBasicType::Bool)
    return std::make_optional<bool>(std::get<bool>(value));
  else return std::nullopt;
}

// Base class for evaluation results
struct EvalResult {
  [[nodiscard]]
  virtual CactType type() const = 0;
  [[nodiscard]]
  virtual std::optional<ConstEvalResult> compileTimeEvalResult() const = 0;
};

// A compile time constant, might be an attribute in the AST
struct CompileTimeConstant final : EvalResult {
  // get compile time constant value
  explicit CompileTimeConstant(int32_t value) : value(value) {}
  explicit CompileTimeConstant(float value) : value(value) {}
  explicit CompileTimeConstant(double value) : value(value) {}
  explicit CompileTimeConstant(bool value) : value(value) {}

  // // get the type of the constant
  // [[nodiscard]]
  // CactType type() const override {
  //   return constEvalResultType(value);
  // }

  // get the compile time evaluation result
  [[nodiscard]]
  std::optional<ConstEvalResult> compileTimeEvalResult() const override {
    return std::make_optional<ConstEvalResult>(value);
  }
  ConstEvalResult value;
};

// An expression result, attribute in the AST
struct ExpressionResult final : EvalResult {
  ExpressionResult() = default;
  explicit ExpressionResult(const CactType& type) : m_type(type) {}
  // explicit ExpressionResult(ConstEvalResult value)
  //     : compileTimeEvaluationResult(value), m_type(constEvalResultType(value)) {}

  // // get the type of the expression
  // [[nodiscard]]
  // CactType type() const override {
  //   if (compileTimeEvaluationResult.has_value())
  //     return constEvalResultType(*compileTimeEvaluationResult);
  //   else
  //     return m_type;
  // }

  // get the compile time evaluation result
  [[nodiscard]]
  std::optional<ConstEvalResult> compileTimeEvalResult() const override {
    return compileTimeEvaluationResult;
  }

  std::optional<ConstEvalResult> compileTimeEvaluationResult{};

  // get the string representation of the expression
  [[nodiscard]]
  std::string toString() const {
    if (compileTimeEvaluationResult.has_value()) {
      if (std::holds_alternative<int32_t>(compileTimeEvaluationResult.value()))
        return std::to_string(std::get<int32_t>(compileTimeEvaluationResult.value()));
      else if (std::holds_alternative<float>(compileTimeEvaluationResult.value()))
        return std::to_string(std::get<float>(compileTimeEvaluationResult.value()));
      else if (std::holds_alternative<double>(compileTimeEvaluationResult.value()))
        return std::to_string(std::get<double>(compileTimeEvaluationResult.value()));
      else
        return std::get<bool>(compileTimeEvaluationResult.value()) ? "true" : "false";
    } else {
      throw std::runtime_error("not a compile time constant");
    }
  }
 private:
  CactType m_type{};
};

// A reference to an expression
struct CactExpr {
  CactType result_type{}; // the type of the expression
  std::vector<std::reference_wrapper<CactExpr>> sub_expressions; // sub expressions
};

// check if two operands are valid for binary operations
inline bool binaryOperandCheck(const EvalResult &lhs, const EvalResult &rhs) {
  return lhs.type().validOperandType() && rhs.type().validOperandType() && lhs.type().basicType == rhs.type().basicType;
}

// check if two operands are valid for binary arithmetic operations
inline bool binaryArithmeticOperandCheck(const EvalResult &lhs, const EvalResult &rhs) {
  return binaryOperandCheck(lhs, rhs) && lhs.type().basicType != CactBasicType::Bool;
}

// check if two operands are valid for binary conditional operations
inline bool binaryConditionalOperandCheck(const EvalResult &lhs, const EvalResult &rhs) {
  return binaryOperandCheck(lhs, rhs) && lhs.type().basicType == CactBasicType::Bool;
}

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
