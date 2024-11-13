//
// Created by creeper on 8/15/24.
//
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-operator.h>
#include <memory>
namespace cactfrontend {

OperandTypeCheck operandTypeCheckIntFloat = OperandTypeCheck(
  "expression must have integral or float-point type",
  {CactBasicType::Int32,
   CactBasicType::Float,
   CactBasicType::Double});

OperandTypeCheck operandTypeCheckInt = OperandTypeCheck(
  "expression must have integral type",
  {CactBasicType::Int32});

OperandTypeCheck operandTypeCheckBool = OperandTypeCheck(
  "expression must have boolean type",
  {CactBasicType::Bool});

std::unique_ptr<BinaryOperator> binaryOperator(CactParser::MulExpressionContext &ctx)
{
  auto ast = ctx.Asterisk();
  auto slash = ctx.Slash();
  auto percent = ctx.Percent();
  if (ast && !slash && !percent)
    return std::make_unique<MulOperator>();
  if (!ast && slash && !percent)
    return std::make_unique<DivOperator>();
  if (!ast && !slash && percent)
    return std::make_unique<ModOperator>();
  throw std::runtime_error("Only exactly one of * / % should be present");
}

std::unique_ptr<BinaryOperator> binaryOperator(CactParser::AddExpressionContext &ctx) {
  auto plus = ctx.Plus();
  auto minus = ctx.Minus();
  if (plus && !minus)
    return std::make_unique<AddOperator>();
  if (!plus && minus)
    return std::make_unique<SubOperator>();
  throw std::runtime_error("Only exactly one of + - should be present");
}

std::unique_ptr<BinaryOperator> binaryOperator(CactParser::RelationalExpressionContext &ctx) {
  auto less = ctx.Less();
  auto greater = ctx.Greater();
  auto lessEqual = ctx.LessEqual();
  auto greaterEqual = ctx.GreaterEqual();
  if (less && !greater && !lessEqual && !greaterEqual)
    return std::make_unique<LessOperator>();
  if (!less && greater && !lessEqual && !greaterEqual)
    return std::make_unique<GreaterOperator>();
  if (!less && !greater && lessEqual && !greaterEqual)
    return std::make_unique<LessEqualOperator>();
  if (!less && !greater && !lessEqual && greaterEqual)
    return std::make_unique<GreaterEqualOperator>();
  throw std::runtime_error("Only exactly one of < > <= >= should be present");
}

std::unique_ptr<UnaryOperator> unaryOperator(CactParser::UnaryExpressionContext &ctx) {
  auto plus = ctx.Plus();
  auto minus = ctx.Minus();
  auto exclamation = ctx.ExclamationMark();
  if (plus && !minus && !exclamation)
    return std::make_unique<PlusOperator>();
  if (!plus && minus && !exclamation)
    return std::make_unique<NegOperator>();
  if (!plus && !minus && exclamation)
    return std::make_unique<LogicalNotOperator>();
  throw std::runtime_error("Only exactly one of + - ! should be present");
}

std::unique_ptr<BinaryOperator> binaryOperator(CactParser::LogicalEqualExpressionContext &ctx) {
  auto equal = ctx.LogicalEqual();
  auto notEqual = ctx.NotEqual();
  if (equal && !notEqual)
    return std::make_unique<EqualOperator>();
  if (!equal && notEqual)
    return std::make_unique<NotEqualOperator>();
  throw std::runtime_error("Only exactly one of == != should be present");
}

}