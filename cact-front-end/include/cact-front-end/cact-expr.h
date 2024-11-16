//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/cact-type.h>
#include <cact-front-end/cact-operator.h>
#include <utility>
#include <variant>
#include <memory>
#include <optional>

namespace cactfrontend {

// an alias for std::variant<int32_t, float, double>

using ConstEvalResult = std::variant<int32_t, float, double, bool>;

// A reference to an expression. Contains a pointer to different sub-expressions and an operator
struct CactExpr {
  observer_ptr<CactExpr> left_expr; // the left expression
  observer_ptr<CactExpr> right_expr; // the right expression
  observer_ptr<BinaryOperator> binary_operator; // the operator

  bool is_variable; // if the expression is a variable, var/param
  std::string variable_name; // the name of the variable

  // default constructor
  explicit CactExpr() = default;
  explicit CactExpr(observer_ptr<CactExpr> left_expr, observer_ptr<CactExpr> right_expr,
                    observer_ptr<BinaryOperator> binary_operator) {
    is_variable = false;
    left_expr = left_expr;
    right_expr = right_expr;
    binary_operator = binary_operator;
  }
  explicit CactExpr(const std::string &variable_name) : is_variable(true), variable_name(variable_name) {}
};

// get a CactType based on the type of the variant
inline CactType constEvalResultType(const ConstEvalResult &value) {
  // return a CactType object based on the type of the variant
  if (std::holds_alternative<int32_t>(value)) {
    return CactType(CactBasicType::Int32, false);
  } else if (std::holds_alternative<float>(value)) {
    return CactType(CactBasicType::Float, false);
  } else if (std::holds_alternative<double>(value)) {
    return CactType(CactBasicType::Double, false);
  } else {
    return CactType(CactBasicType::Bool, false);
  }
}

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
  bool isCompileTimeConstant() const {return this->is_compile_time_constant;}

  [[nodiscard]]
  virtual std::optional<ConstEvalResult> compileTimeEvalResult() const = 0;

protected:
  bool is_compile_time_constant;
};

// A compile time constant, might be an attribute in the AST
struct CompileTimeConstant final : EvalResult {
  // use a value to generate a CompileTimeConstant object
  explicit CompileTimeConstant(ConstEvalResult value) : value(value) {
    this->is_compile_time_constant = true;
  }

  // return the type of the value
  [[nodiscard]]
  CactType type() const override {
    return constEvalResultType(value);
  }

  [[nodiscard]]
  std::optional<ConstEvalResult> compileTimeEvalResult() const override {
    return std::make_optional<ConstEvalResult>(value);
  }

private:
  ConstEvalResult value;
};

// An expression result, attribute in the AST
struct ExpressionResult final : EvalResult {
  // use a value to generate an ExpressionResult object
  explicit ExpressionResult(CactType expr_type) : expr_type(expr_type), expr(expr) {
    this->is_compile_time_constant = false;
  }

  // return the type of the value
  [[nodiscard]]
  CactType type() const override {
    return expr_type;
  }

  [[nodiscard]]
  std::optional<ConstEvalResult> compileTimeEvalResult() const override {
    return std::nullopt;
  }

private:
  CactType expr_type;
  CactExpr expr;
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
