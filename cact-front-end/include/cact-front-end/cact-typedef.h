//
// Created by sailinbay on Nov 18, 2024.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPEDEF_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPEDEF_H_

#include <variant>
#include <memory>

namespace cactfrontend {

// an alias for std::variant<int32_t, float, double>
typedef std::variant<int32_t, float, double, bool> ConstEvalResult;

// A reference to an expression. Contains a pointer to different sub-expressions and an operator
enum class ExprType {
  Constant,
  Variable,
  FunctionCall,
  UnaryExpression,
  BinaryExpression,
};

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

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPEDEF_H_