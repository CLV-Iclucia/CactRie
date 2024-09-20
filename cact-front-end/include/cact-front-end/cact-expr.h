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

namespace cactparser {

// an alias for std::variant<int32_t, float, double>

using ConstEvalResult = std::variant<int32_t, float, double, bool>;

inline CactType constEvalResultType(const ConstEvalResult &value) {
  if (std::holds_alternative<int32_t>(value)) {
    return CactType{false, CactBasicType::Int32};
  } else if (std::holds_alternative<float>(value)) {
    return CactType{false, CactBasicType::Float};
  } else if (std::holds_alternative<double>(value)) {
    return CactType{false, CactBasicType::Double};
  } else {
    return CactType{false, CactBasicType::Bool};
  }
}
inline CactBasicType constEvalResultBasicType(const ConstEvalResult &value) {
  if (std::holds_alternative<int32_t>(value)) {
    return CactBasicType::Int32;
  } else if (std::holds_alternative<float>(value)) {
    return CactBasicType::Float;
  } else if (std::holds_alternative<double>(value)) {
    return CactBasicType::Double;
  } else {
    return CactBasicType::Bool;
  }
}
inline std::optional<bool> conditionEvalResult(const ConstEvalResult &value) {
  if (constEvalResultBasicType(value) == CactBasicType::Bool)
    return std::make_optional<bool>(get<bool>(value));
  else return std::nullopt;
}
struct EvalResult {
  [[nodiscard]] virtual CactType type() const = 0;
  [[nodiscard]] virtual std::optional<ConstEvalResult> compileTimeEvalResult() const = 0;
};

struct CompileTimeConstant final : EvalResult {
  explicit CompileTimeConstant(int32_t value) : value(value) {}
  explicit CompileTimeConstant(float value) : value(value) {}
  explicit CompileTimeConstant(double value) : value(value) {}
  explicit CompileTimeConstant(bool value) : value(value) {}
  [[nodiscard]] CactType type() const override {
    return constEvalResultType(value);
  }
  [[nodiscard]] std::optional<ConstEvalResult> compileTimeEvalResult() const override {
    return std::make_optional<ConstEvalResult>(value);
  }
  ConstEvalResult value;
};

struct ExpressionResult final : EvalResult {
  explicit ExpressionResult(const CactType& type) : m_type(type) {}
  explicit ExpressionResult(ConstEvalResult value)
      : compileTimeEvaluationResult(value), m_type(constEvalResultType(value)) {}
  [[nodiscard]] CactType type() const override {
    if (compileTimeEvaluationResult.has_value())
      return constEvalResultType(*compileTimeEvaluationResult);
    else
      return m_type;
  }
  [[nodiscard]] std::optional<ConstEvalResult> compileTimeEvalResult() const override {
    return compileTimeEvaluationResult;
  }
  std::optional<ConstEvalResult> compileTimeEvaluationResult{};
  [[nodiscard]] std::string toString() const {
    if (compileTimeEvaluationResult.has_value()) {
      if (std::holds_alternative<int32_t>(compileTimeEvaluationResult.value()))
        return std::to_string(get<int32_t>(compileTimeEvaluationResult.value()));
      else if (std::holds_alternative<float>(compileTimeEvaluationResult.value()))
        return std::to_string(get<float>(compileTimeEvaluationResult.value()));
      else if (std::holds_alternative<double>(compileTimeEvaluationResult.value()))
        return std::to_string(get<double>(compileTimeEvaluationResult.value()));
      else
        return get<bool>(compileTimeEvaluationResult.value()) ? "true" : "false";
    } else {
      throw std::runtime_error("not a compile time constant");
    }
  }
 private:
  CactType m_type;
};

struct CactExpr {
  CactType result_type{};
  std::vector<std::reference_wrapper<CactExpr>> sub_expressions;
};

inline bool binaryOperandCheck(const EvalResult &lhs, const EvalResult &rhs) {
  return lhs.type().validOperandType() && rhs.type().validOperandType() && lhs.type().type == rhs.type().type;
}

inline bool binaryArithmeticOperandCheck(const EvalResult &lhs, const EvalResult &rhs) {
  return binaryOperandCheck(lhs, rhs) && lhs.type().type != CactBasicType::Bool;
}

inline bool binaryConditionalOperandCheck(const EvalResult &lhs, const EvalResult &rhs) {
  return binaryOperandCheck(lhs, rhs) && lhs.type().type == CactBasicType::Bool;
}
}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
