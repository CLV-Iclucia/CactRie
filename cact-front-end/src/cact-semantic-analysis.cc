//
// Created by creeper on 8/15/24.
//
#include <cact-front-end/type-check-and-const-eval.h>
#include <cact-front-end/cact-variable.h>
#include <memory>
namespace cactfrontend {

// a function to check if the type of the expression is valid
// and evaluate the constant expression if possible
// the result is stored in the expressionResult field of the context
// std::any TypeCheckAndConstEvalVisitor::visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) {
//   auto expr = ctx->expression(); // get the expression
//   auto num = ctx->number(); // get the number
//   auto lvalue = ctx->leftValue(); // get the left value
//   if (expr) {
//     ctx->expressionResult = TypeCheckAndConstEvalVisitor::visitExpression(expr);
//   } else if (num) {
//     ctx->expressionResult = TypeCheckAndConstEvalVisitor::visitNumber(num);
//   } else if (lvalue) {
//     ctx->expressionResult = TypeCheckAndConstEvalVisitor::visitLeftValue(lvalue);
//   } else
//     throw std::runtime_error("Invalid primary expression context");
//   return {};
// }

}