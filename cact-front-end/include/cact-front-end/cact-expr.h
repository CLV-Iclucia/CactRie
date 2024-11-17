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
enum class ExprType {
  Const,
  Variable,
  Expression,
};

struct CactExpr {
  ExprType expr_type; // the type of the expression

  observer_ptr<UnaryOperator> unary_operator; // the operator
  observer_ptr<CactExpr> expr; // the left expression

  observer_ptr<BinaryOperator> binary_operator; // the operator
  observer_ptr<CactExpr> left_expr; // the left expression
  observer_ptr<CactExpr> right_expr; // the right expression

  // default constructor
  explicit CactExpr() = default;
  explicit CactExpr(const observer_ptr<CactConstVar> __variable_name) { setVariable(__variable_name); }
  explicit CactExpr(ConstEvalResult __const_value) { setConst(__const_value); }
  explicit CactExpr(int32_t         __const_value) { setConst(ConstEvalResult(__const_value)); }
  explicit CactExpr(float           __const_value) { setConst(ConstEvalResult(__const_value)); }
  explicit CactExpr(double          __const_value) { setConst(ConstEvalResult(__const_value)); }
  explicit CactExpr(bool            __const_value) { setConst(ConstEvalResult(__const_value)); }

  // check the expression's type
  [[nodiscard]] bool isVariable()   const { return expr_type == ExprType::Variable; }
  [[nodiscard]] bool isConst()      const { return expr_type == ExprType::Const; }
  [[nodiscard]] bool isExpression() const { return expr_type == ExprType::Expression; }

  // set up this struct for variable or constant
  void setVariable(observer_ptr<CactConstVar> __variable) {
    expr_type = ExprType::Variable;
    variable = CactConstVarArray(__variable);
  }
  void setConst(ConstEvalResult __const_value) {
    expr_type = ExprType::Const;
    const_value = __const_value;
  }

  // get the value of the constant
  [[nodiscard]]
  ConstEvalResult getConstValue() const {
    assert(isConst());
    return const_value;
  }

  // // get the variable
  // [[nodiscard]]
  // observer_ptr<CactConstVarArray> getVariable() const {
  //   assert(isVariable());
  //   return variable;
  // }

protected:
  CactConstVarArray variable; // the variable
  ConstEvalResult const_value; // the value of the constant
};

struct CactUnaryExpr : CactExpr {
  // default constructor
  explicit CactUnaryExpr() = default;
  explicit CactUnaryExpr(observer_ptr<UnaryOperator> __unary_operator, observer_ptr<CactExpr> __expr) {
    auto res_value = __unary_operator->unaryConstCheck(__expr->getConstValue());
    // if this result can be calculated at compile time
    if (res_value != std::nullopt)
      setConst(res_value.value());
    else // if not
      setExpression(__unary_operator, __expr);
  }

  // set up this struct for unary expression
  void setExpression(observer_ptr<UnaryOperator> __unary_operator, observer_ptr<CactExpr> __expr) {
    expr_type = ExprType::Expression;
    expr = __expr;
    unary_operator = __unary_operator;
  }
};

struct CactBinaryExpr : CactExpr {
  // default constructor
  explicit CactBinaryExpr() = default;
  explicit CactBinaryExpr(observer_ptr<BinaryOperator> __binary_operator,
                          observer_ptr<CactExpr> __left_expr, observer_ptr<CactExpr> __right_expr) {
    auto res_value = __binary_operator->binaryConstCheck(__left_expr->getConstValue(), __right_expr->getConstValue());
    // if this result can be calculated at compile time
    if (res_value != std::nullopt)
      setConst(res_value.value());
    else // if not
      setExpression(__binary_operator, __left_expr, __right_expr);
  }

  // set up this struct for binary expression
  void setExpression(observer_ptr<BinaryOperator> __binary_operator,
                     observer_ptr<CactExpr> __left_expr, observer_ptr<CactExpr> __right_expr) {
    expr_type = ExprType::Expression;
    left_expr = __left_expr;
    right_expr = __right_expr;
    binary_operator = __binary_operator;
  }
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

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
