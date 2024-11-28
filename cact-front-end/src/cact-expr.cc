//
// Created by creeper on 11/25/24.
//
#include <iostream>
#include <cact-front-end/cact-expr.h>

namespace cactfrontend {

void CactConstVarArray::setOffsetByIndices() {
  // assert(this->indexing_times == this->symbol->type.dim());

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

  offset = std::make_shared<CactExpr>(const_offset);

  // calculate non-constant offset
  std::shared_ptr<CactExpr> expr_tmp_ptr;

  for (int i = 0; i < this->indexing_times; i++) {
    // indexing times might be less than the dimension of the array
    if (this->indexing_times <= i) {
      break;
    }

    if (!indices[i]->isConstant()) {
      expr_tmp_ptr = std::make_shared<CactExpr>((int32_t) (this->symbol->type.size(i)));
      expr_tmp_ptr = std::make_shared<CactBinaryExpr>(std::make_shared<MulOperator>(), indices[i], expr_tmp_ptr);
      offset = std::make_shared<CactBinaryExpr>(std::make_shared<AddOperator>(), offset, expr_tmp_ptr);
    }
  }

  int32_t const_flattened_idx = 0;
  for (int i = 0; i < this->indexing_times; i++) {
    // indexing times might be less than the dimension of the array
    if (this->indexing_times <= i) {
      break;
    }

    if (indices[i]->isConstant()) {
      assert(symbol->type.size(i) % sizeOf(symbol->type.basic_type) == 0);
      const_flattened_idx += std::get<int32_t>(indices[i]->getConstantValue()) * this->symbol->type.size(i) / sizeOf(this->symbol->type.basic_type);
    }
  }

  flattenedIndex = std::make_shared<CactExpr>(const_flattened_idx);

  // calculate non-constant offset
  std::shared_ptr<CactExpr> expr_ptr_flattened;

  for (int i = 0; i < this->indexing_times; i++) {
    // indexing times might be less than the dimension of the array
    if (this->indexing_times <= i) {
      break;
    }

    if (!indices[i]->isConstant()) {
      assert(symbol->type.size(i) % sizeOf(symbol->type.basic_type) == 0);
      expr_ptr_flattened = std::make_shared<CactExpr>(ConstEvalResult{(int32_t)(symbol->type.size(i) / sizeOf(symbol->type.basic_type))});
      expr_ptr_flattened = std::make_shared<CactBinaryExpr>(std::make_shared<MulOperator>(), indices[i], expr_ptr_flattened);
      flattenedIndex = std::make_shared<CactBinaryExpr>(std::make_shared<AddOperator>(), offset, expr_ptr_flattened);
    }
  }
}
void CactExpr::setVariable(std::shared_ptr<CactConstVarArray> _variable) {
  expr_type = ExprType::Variable;
  variable = _variable;
}
void CactExpr::setConstant(ConstEvalResult _const_value) {
  expr_type = ExprType::Constant;
  const_value = _const_value;
}
void CactExpr::setFunctionCall(observer_ptr<CactFunction> _func,
                               const std::vector<std::shared_ptr<CactExpr>>& _args) {
  function = _func;
  expr_type = ExprType::FunctionCall;
  args = _args;
}
void CactUnaryExpr::setUnaryExpression(std::shared_ptr<UnaryOperator> _unary_operator,
                                       std::shared_ptr<CactExpr> _expr) {
  expr_type = ExprType::UnaryExpression;
  expr = _expr;
  unary_operator = _unary_operator;
}
void CactBinaryExpr::setBinaryExpression(std::shared_ptr<BinaryOperator> _binary_operator,
                                         std::shared_ptr<CactExpr> _left_expr,
                                         std::shared_ptr<CactExpr> _right_expr) {
  expr_type = ExprType::BinaryExpression;
  left_expr = _left_expr;
  right_expr = _right_expr;
  binary_operator = _binary_operator;
}

static CactBasicType getConstCactType(ConstEvalResult result) {
  if (std::holds_alternative<int32_t>(result)) {
    return CactBasicType::Int32;
  } else if (std::holds_alternative<float>(result)) {
    return CactBasicType::Float;
  } else if (std::holds_alternative<double>(result)) {
    return CactBasicType::Double;
  } else if (std::holds_alternative<bool>(result)) {
    return CactBasicType::Bool;
  }
  assert(0);
}

CactBasicType CactExpr::resultBasicType() const {
  if (isConstant())
    return getConstCactType(const_value);
  if (isVariable())
    return variable->symbol->type.basic_type;
  if (isUnaryExpression())
    return expr->resultBasicType();
  if (isBinaryExpression())
    return left_expr->resultBasicType();
  if (isFunctionCall())
    return function->return_type;
  assert(0);
}
}