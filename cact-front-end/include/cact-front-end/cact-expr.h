//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/cact-type.h>
#include <cact-front-end/cact-typedef.h>
#include <cact-front-end/cact-operator.h>
#include <cact-front-end/cact-functions.h>
#include <cact-front-end/cact-constant-variable.h>
#include <utility>
#include <variant>
#include <memory>
#include <optional>

namespace cactfrontend {

struct CactConstVarArray;
struct CactExpr;
struct CactUnaryExpr;
struct CactBinaryExpr;


struct CactExpr {
  ExprType expr_type; // the type of the expression

  std::shared_ptr<UnaryOperator> unary_operator{}; // the operator
  std::shared_ptr<CactExpr> expr{}; // the left expression

  std::shared_ptr<BinaryOperator> binary_operator{}; // the operator
  std::shared_ptr<CactExpr> left_expr{}; // the left expression
  std::shared_ptr<CactExpr> right_expr{}; // the right expression

  // constructors
  explicit CactExpr() = default;

  explicit CactExpr(ConstEvalResult _const_value) { setConstant(_const_value); }

  explicit CactExpr(std::shared_ptr<CactConstVarArray> _variable) {
    setVariable(_variable);
  }

  explicit CactExpr(observer_ptr<CactFunction> _func, const std::vector<std::shared_ptr<CactExpr>>& _args) {
    setFunctionCall(_func, _args);
  }

  // check the expression's type
  [[nodiscard]] bool isVariable()         const { return expr_type == ExprType::Variable; }
  [[nodiscard]] bool isConstant()         const { return expr_type == ExprType::Constant; }
  [[nodiscard]] bool isFunctionCall()     const { return expr_type == ExprType::FunctionCall; }
  [[nodiscard]] bool isUnaryExpression()  const { return expr_type == ExprType::UnaryExpression; }
  [[nodiscard]] bool isBinaryExpression() const { return expr_type == ExprType::BinaryExpression; }

  // set up this struct for variable or constant
  void setVariable(std::shared_ptr<CactConstVarArray> _variable);
  void setConstant(ConstEvalResult _const_value);
  void setFunctionCall(observer_ptr<CactFunction> _func, const std::vector<std::shared_ptr<CactExpr>>& _args);

  [[nodiscard]]
  ConstEvalResult getConstantValue() const {
    assert(isConstant());
    return const_value;
  }

  [[nodiscard]] CactBasicType resultBasicType() const;

  std::shared_ptr<CactConstVarArray> variable; // the variable
  ConstEvalResult const_value; // the value of the constant
  observer_ptr<CactFunction> function; // the function
  std::vector<std::shared_ptr<CactExpr>> args; // the arguments of the function call
};


struct CactUnaryExpr : CactExpr {
  // default constructor
  explicit CactUnaryExpr() = default;
  explicit CactUnaryExpr(const std::shared_ptr<UnaryOperator> _unary_operator, const std::shared_ptr<CactExpr> _expr) {
    auto is_const_expr = _expr->isConstant();
    // if this result can be calculated at compile time
    if (is_const_expr) {
      // calculate the result
      auto res_value = _unary_operator->unaryConstCheck(_expr->getConstantValue());
      setConstant(res_value.value());
    }
    else // if not
      setUnaryExpression(_unary_operator, _expr);
  }

  // set up this struct for unary expression
  void setUnaryExpression(const std::shared_ptr<UnaryOperator> _unary_operator, std::shared_ptr<CactExpr> _expr);
};

struct CactBinaryExpr : CactExpr {
  // default constructor
  explicit CactBinaryExpr() = default;
  explicit CactBinaryExpr(const std::shared_ptr<BinaryOperator> _binary_operator,
                          const std::shared_ptr<CactExpr> _left_expr, const std::shared_ptr<CactExpr> _right_expr) {
    auto is_const_expr = _left_expr->isConstant() && _right_expr->isConstant();
    // if this result can be calculated at compile time
    if (is_const_expr) {
      auto res_value = _binary_operator->binaryConstCheck(
        _left_expr->getConstantValue(), _right_expr->getConstantValue());
      setConstant(res_value.value());
    }
    else // if not
      setBinaryExpression(_binary_operator, _left_expr, _right_expr);
  }

  // set up this struct for binary expression
  void setBinaryExpression(const std::shared_ptr<BinaryOperator> _binary_operator,
                           const std::shared_ptr<CactExpr> _left_expr, const std::shared_ptr<CactExpr> _right_expr);
};


struct CactConstVarArray {
  std::shared_ptr<CactConstVar> symbol;
  std::shared_ptr<CactExpr> offset;
  uint32_t indexing_times; // 0 means not indexed, 1 means indexed once, etc.

  // constructor
  explicit CactConstVarArray() = default;
  explicit CactConstVarArray(std::shared_ptr<CactConstVar> symbol) : symbol(symbol), indexing_times(0) {}

  // add an index
  void addIndex(const std::shared_ptr<CactExpr> index) {
    this->indices.emplace_back(index);
    this->indexing_times++;
  }

  // create an expression to calculate the offset
  void setOffsetByIndices();

private:
  std::vector<std::shared_ptr<CactExpr>> indices;
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
