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

[[nodiscard]]
observer_ptr<CactExpr> getObserverPtrExpr(CactExpr expr);

[[nodiscard]]
observer_ptr<CactExpr> getObserverPtrBiExpr(CactBinaryExpr expr);


struct CactExpr {
  ExprType expr_type; // the type of the expression

  observer_ptr<UnaryOperator> unary_operator; // the operator
  observer_ptr<CactExpr> expr; // the left expression

  observer_ptr<BinaryOperator> binary_operator; // the operator
  observer_ptr<CactExpr> left_expr; // the left expression
  observer_ptr<CactExpr> right_expr; // the right expression

  // constructors
  explicit CactExpr() = default;

  // operator: copy
  CactExpr(const CactExpr &expr) {
    this->expr_type       = expr.expr_type;
    this->unary_operator  = expr.unary_operator;
    this->expr            = expr.expr;
    this->binary_operator = expr.binary_operator;
    this->left_expr       = expr.left_expr;
    this->right_expr      = expr.right_expr;
    this->variable        = std::make_unique<CactConstVarArray>(*expr.variable);
    this->const_value     = expr.const_value;
    this->function        = expr.function;
    this->args            = expr.args;
  }

  explicit CactExpr(const ConstEvalResult __const_value) { setConstant(__const_value); }
  // explicit CactExpr(const int32_t __const_value) { setConstant(ConstEvalResult(__const_value)); }
  // explicit CactExpr(const float   __const_value) { setConstant(ConstEvalResult(__const_value)); }
  // explicit CactExpr(const double  __const_value) { setConstant(ConstEvalResult(__const_value)); }
  // explicit CactExpr(const bool    __const_value) { setConstant(ConstEvalResult(__const_value)); }

  explicit CactExpr(const observer_ptr<CactConstVarArray>  __variable) { setVariable(__variable); }

  explicit CactExpr(const observer_ptr<CactFunction> __func, const std::vector<observer_ptr<CactExpr>> __args) {
    setFunctionCall(__func, __args);
  }
  

  // check the expression's type
  [[nodiscard]] bool isVariable()         const { return expr_type == ExprType::Variable; }
  [[nodiscard]] bool isConstant()         const { return expr_type == ExprType::Constant; }
  [[nodiscard]] bool isFunctionCall()     const { return expr_type == ExprType::FunctionCall; }
  [[nodiscard]] bool isUnaryExpression()  const { return expr_type == ExprType::UnaryExpression; }
  [[nodiscard]] bool isBinaryExpression() const { return expr_type == ExprType::BinaryExpression; }

  // set up this struct for variable or constant
  void setVariable(const observer_ptr<CactConstVarArray> __variable) {
    expr_type = ExprType::Variable;
    variable = std::make_unique<CactConstVarArray>(*__variable);
  }
  void setConstant(const ConstEvalResult __const_value) {
    expr_type = ExprType::Constant;
    const_value = __const_value;
  }
  void setFunctionCall(const observer_ptr<CactFunction> __func, const std::vector<observer_ptr<CactExpr>> __args) {
    expr_type = ExprType::FunctionCall;
    args = __args;
  }

  // get the value of the constant
  [[nodiscard]]
  ConstEvalResult getConstantValue() const {
    assert(isConstant());
    return const_value;
  }

  // operator: assign
  void operator=(const CactExpr &expr) {
    this->expr_type       = expr.expr_type;
    this->unary_operator  = expr.unary_operator;
    this->expr            = expr.expr;
    this->binary_operator = expr.binary_operator;
    this->left_expr       = expr.left_expr;
    this->right_expr      = expr.right_expr;
    this->variable        = std::make_unique<CactConstVarArray>(*expr.variable);
    this->const_value     = expr.const_value;
    this->function        = expr.function;
    this->args            = expr.args;
  }


// protected:
  std::unique_ptr<CactConstVarArray> variable; // the variable
  ConstEvalResult const_value; // the value of the constant
  observer_ptr<CactFunction> function; // the function
  std::vector<observer_ptr<CactExpr>> args; // the arguments of the function call
};


struct CactUnaryExpr : CactExpr {
  // default constructor
  explicit CactUnaryExpr() = default;
  explicit CactUnaryExpr(const observer_ptr<UnaryOperator> __unary_operator, const observer_ptr<CactExpr> __expr) {
    auto res_value = __unary_operator->unaryConstCheck(__expr->getConstantValue());
    // if this result can be calculated at compile time
    if (res_value != std::nullopt)
      setConstant(res_value.value());
    else // if not
      setUnaryExpression(__unary_operator, __expr);
  }

  // set up this struct for unary expression
  void setUnaryExpression(const observer_ptr<UnaryOperator> __unary_operator, const observer_ptr<CactExpr> __expr) {
    expr_type = ExprType::UnaryExpression;
    expr = __expr;
    unary_operator = __unary_operator;
  }
};

struct CactBinaryExpr : CactExpr {
  // default constructor
  explicit CactBinaryExpr() = default;
  explicit CactBinaryExpr(const observer_ptr<BinaryOperator> __binary_operator,
                          const observer_ptr<CactExpr> __left_expr, const observer_ptr<CactExpr> __right_expr) {
    auto res_value = __binary_operator->binaryConstCheck(
      __left_expr->getConstantValue(), __right_expr->getConstantValue());
    // if this result can be calculated at compile time
    if (res_value != std::nullopt)
      setConstant(res_value.value());
    else // if not
      setBinaryExpression(__binary_operator, __left_expr, __right_expr);
  }

  // set up this struct for binary expression
  void setBinaryExpression(const observer_ptr<BinaryOperator> __binary_operator,
                           const observer_ptr<CactExpr> __left_expr, const observer_ptr<CactExpr> __right_expr) {
    expr_type = ExprType::BinaryExpression;
    left_expr = __left_expr;
    right_expr = __right_expr;
    binary_operator = __binary_operator;
  }
};


struct CactConstVarArray {
  observer_ptr<CactConstVar> symbol;
  observer_ptr<CactExpr> offset;
  uint32_t indexing_times; // 0 means not indexed, 1 means indexed once, etc.

  // constructor
  explicit CactConstVarArray() = default;
  explicit CactConstVarArray(observer_ptr<CactConstVar> symbol)
    : symbol(symbol), offset(nullptr), indexing_times(0) {}

  // add an index
  void addIndex(const observer_ptr<CactExpr> index) {
    this->indices.emplace_back(index);
    this->indexing_times++;
  }

  // get the index
  [[nodiscard]]
  observer_ptr<CactExpr> getIndex(const uint32_t index) const {
    return indices[index];
  }

  // create an expression to calculate the offset
  void setOffsetByIndices() {
    assert(this->indexing_times == this->symbol->type.dim());

    // calculate constant offset
    int32_t const_offset = 0;
    for (int i = 0; i < this->indexing_times; i++) {
      // indexing times might be less than the dimension of the array
      if (this->indexing_times <= i) {
        break;
      }

      if (indices[i]->isConstant()) {
        const_offset += std::get<int32_t>(indices[i]->getConstantValue()) * this->symbol->type.size(i);
      }
    }

    offset = getObserverPtrExpr(CactExpr(const_offset));

    // calculate non-constant offset
    observer_ptr<CactExpr> expr_tmp_ptr;

    for (int i = 0; i < this->indexing_times; i++) {
      // indexing times might be less than the dimension of the array
      if (this->indexing_times <= i) {
        break;
      }

      if (!indices[i]->isConstant()) {
        expr_tmp_ptr = getObserverPtrExpr(CactExpr((int32_t)(this->symbol->type.size(i))));
        expr_tmp_ptr = getObserverPtrBiExpr(
          CactBinaryExpr(
            make_observer<BinaryOperator>(std::make_unique<MulOperator>().get()),
            indices[i],
            expr_tmp_ptr));
        offset = getObserverPtrBiExpr(
          CactBinaryExpr(
            make_observer<BinaryOperator>(std::make_unique<AddOperator>().get()),
            offset,
            expr_tmp_ptr));
      }
    }
  }

private:
  std::vector<observer_ptr<CactExpr>> indices;
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_EXPR_H_
