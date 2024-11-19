//
// Created by creeper on 8/14/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
#include <cact-front-end/CactParserBaseVisitor.h>
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/cact-operator.h>
#include <cact-front-end/symbol-registry.h>

namespace cactfrontend {

struct ConstEvalVisitor : CactParserBaseVisitor {

  /**
   * // declaration & defination
   * compilationUnit: (declaration | functionDefinition)*;
   * declaration: constantDeclaration | variableDeclaration;
   * constantDeclaration: Const dataType constantDefinition (Comma constantDefinition)* Semicolon;
   * dataType: Int32 | Bool | Float | Double;
   * constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
   * constantInitialValue: constantExpression | LeftBrace (constantInitialValue
   *                         (Comma constantInitialValue)*)? RightBrace;
   * variableDeclaration: dataType variableDefinition (Comma variableDefinition)* Semicolon;
   * variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;
   * functionDefinition: functionType Identifier LeftParenthesis (functionParameters)? RightParenthesis block;
   * functionType: Void | Int32 | Float | Double | Bool;
   * functionParameters: functionParameter (Comma functionParameter)*;
   * functionParameter: dataType Identifier (LeftBracket IntegerConstant? RightBracket
   *                      (LeftBracket IntegerConstant RightBracket)*)?;
   * 
   * // statement & expression
   * block: LeftBrace (blockItem)* RightBrace;
   * blockItem: declaration | statement;
   * statement: assignStatement | expressionStatement | block | returnStatement | ifStatement
   *          | whileStatement | breakStatement | continueStatement;
   * assignStatement: leftValue Equal expression Semicolon;
   * expressionStatement: (expression)? Semicolon;
   * returnStatement: Return expression? Semicolon;
   * ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?;
   * whileStatement: While LeftParenthesis condition RightParenthesis statement;
   * breakStatement: Break Semicolon;
   * continueStatement: Continue Semicolon;
   * expression: addExpression | BooleanConstant;
   * constantExpression: number | BooleanConstant;
   * condition: logicalOrExpression;
   * leftValue: Identifier (LeftBracket expression RightBracket)*;
   * primaryExpression: LeftParenthesis expression RightParenthesis | leftValue | number;
   * number: IntegerConstant | FloatConstant | DoubleConstant;
   * unaryExpression: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
   *                 | Identifier LeftParenthesis (functionArguments)? RightParenthesis;
   * functionArguments: expression (Comma expression)*;
   * mulExpression: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;
   * addExpression: mulExpression | addExpression (Plus | Minus) mulExpression;
   * relationalExpression: BooleanConstant | addExpression
   *                     | addExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;
   * logicalEqualExpression: relationalExpression | relationalExpression (LogicalEqual | NotEqual) relationalExpression;
   * logicalAndExpression: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;
   * logicalOrExpression: logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;
   */

  /**
   * compilationUnit,
   * declaration,
   * constantDeclaration,
   * dataType,
   * constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
   * They do not have a constant value
   */

  // constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;

  /**
   * variableDeclaration,
   * variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;
   * functionDefinition,
   * functionType,
   * functionParameters,
   * functionParameter: dataType Identifier (LeftBracket IntegerConstant? RightBracket
   *                      (LeftBracket IntegerConstant RightBracket)*)?;
   * They do not have a constant value
   */

  /**
   * block,
   * blockItem,
   * statement,
   * assignStatement: leftValue Equal expression Semicolon;
   * expressionStatement,
   * returnStatement: Return expression? Semicolon;
   * ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?;
   * whileStatement: While LeftParenthesis condition RightParenthesis statement;
   * breakStatement: Break Semicolon;
   * continueStatement: Continue Semicolon;
   */

  /**
   *   [COULD HAVE CONSTANT VALUE]
   * expression: addExpression | BooleanConstant;
   * constantExpression: number | BooleanConstant;
   * condition: logicalOrExpression;
   * leftValue: Identifier (LeftBracket expression RightBracket)*;
   * primaryExpression: LeftParenthesis expression RightParenthesis | leftValue | number;
   * number: IntegerConstant | FloatConstant | DoubleConstant;
   * unaryExpression: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
   *                 | Identifier LeftParenthesis (functionArguments)? RightParenthesis;
   */

  /**
   * functionArguments: expression (Comma expression)*;
   */

  /**
   *   [COULD HAVE CONSTANT VALUE]
   * mulExpression: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;
   * addExpression: mulExpression | addExpression (Plus | Minus) mulExpression;
   * relationalExpression: BooleanConstant | addExpression
   *                     | addExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;
   * logicalEqualExpression: relationalExpression | relationalExpression (LogicalEqual | NotEqual) relationalExpression;
   * logicalAndExpression: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;
   * logicalOrExpression: logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;
   */

  /**
   * The task now: generate a tree of semantic analysis,
   * consisted declarations, statement, expressions, variables and constants.
   * 
   * This visitor is responsible for constant evaluation.
   */

  // visit a number
  std::any visitNumber(CactParser::NumberContext *ctx) override {
    if (ctx->IntegerConstant()) {
      return CompileTimeConstant(std::stoi(ctx->IntegerConstant()->getText()));
    } else if (ctx->FloatConstant()) {
      return CompileTimeConstant(std::stof(ctx->FloatConstant()->getText()));
    } else if (ctx->DoubleConstant()) {
      return CompileTimeConstant(std::stod(ctx->DoubleConstant()->getText()));
    }
    throw std::runtime_error("Invalid number context");
  }

  // visit a function definition
  std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override {
  }

  // visit a primary expression
  std::any visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) override {
    auto expr = ctx->expression();
    auto num = ctx->number();
    auto lvalue = ctx->leftValue();
    if (expr) {
      ctx->expressionResult = visitExpression(expr);
    } else if (num) {
      ctx->expressionResult = visitNumber(num);
    } else if (lvalue) {
      ctx->expressionResult = visitLeftValue(lvalue);
    } else
      throw std::runtime_error("Invalid primary expression context");
    return {};
  }

  // visit a unary expression
  std::any visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) override {
    auto primary_expr = ctx->primaryExpression();
    auto unary_expr = ctx->unaryExpression();
    if (primary_expr) {
      ctx->expressionResult = visitPrimaryExpression(primary_expr);
    } else {
      visitUnaryExpression(unary_expr);
      auto result = unaryOperator(*ctx)->apply(unary_expr->expressionResult);
      if (!result.has_value()) {
        // compile error
      }
      ctx->expressionResult = result.pointee();
    }
    if (unary_expr) {
      ctx->expressionResult = visitUnaryExpression(unary_expr);
      if (!ctx->expressionResult.has_value()) {
        // compile error
      }
    }

    return ctx->expressionResult;
  }

  // visit an additive expression
  std::any visitAddExpression(CactParser::AddExpressionContext *ctx) override {
    auto add_expr = ctx->addExpression();
    auto mul_expr = ctx->mulExpression();
    assert(mul_expr);
    visitMulExpression(mul_expr);
    auto lhs = mul_expr->expressionResult;
    if (!add_expr)
      ctx->expressionResult = lhs;
    else {
      auto rhs = visitAddExpression(add_expr);
      auto result = binaryOperator(*ctx)->evaluate(lhs, rhs);
      if (!result.has_value()) {
        // compile error
      }
      ctx->expressionResult = result.pointee();
    }
    return ctx->expressionResult;
  }

  // visit a multiplicative expression
  std::any visitMulExpression(CactParser::MulExpressionContext *ctx) override {
    auto mul_expr = ctx->mulExpression();
    auto unary_expr = ctx->unaryExpression();
    assert(unary_expr);
    auto rhs = visitUnaryExpression(unary_expr);
    if (!mul_expr) {
      ctx->expressionResult = rhs;
    } else {
      auto lhs = visitMulExpression(mul_expr);
      auto result = binaryOperator(*ctx)->evaluate(lhs, rhs);
      if (!result.has_value()) {
        // compile error
      }
      ctx->expressionResult = result.pointee();
    }
    return ctx->expressionResult;
  }

  // visit a logical or expression
  std::any visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) override {
    auto bool_const = ctx->BooleanConstant();
    if (bool_const) {
      ctx->expressionResult = CompileTimeConstant(bool_const->getText() == "true");
      return ctx->expressionResult;
    }

    auto logical_or_expr = ctx->logicalOrExpression();
    auto logical_and_expr = ctx->logicalAndExpression();
    assert(logical_and_expr);
    auto rhs = visitLogicalAndExpression(logical_and_expr);
    if (!logical_or_expr)
      ctx->expressionResult = rhs;
    else {
      auto lhs = visitLogicalOrExpression(logical_or_expr);
      auto result = LogicalOrOperator().evaluate(lhs, rhs);
      if (!result.has_value()) {
        // compile error
      }
      ctx->expressionResult = result.pointee();
    }
    return ctx->expressionResult;
  }

  // visit a logical and expression
  std::any visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) override {
    auto logical_and_expr = ctx->logicalAndExpression();
    auto logical_eq_expr = ctx->logicalEqualExpression();
    assert(logical_eq_expr);
    visitLogicalEqualExpression(logical_eq_expr);
    auto rhs = logical_eq_expr->expressionResult;
    if (!logical_and_expr)
      ctx->expressionResult = rhs;
    else {
      auto lhs = visitLogicalAndExpression(logical_and_expr);
      auto result = LogicalAndOperator().evaluate(lhs, rhs);
      if (!result.has_value()) {

      }
      ctx->expressionResult = result.pointee();
    }
    return {};
  }

  // visit a relational expression
  std::any visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) override {
    auto relational_expr = ctx->relationalExpression();
    auto add_expr = ctx->addExpression();
    assert(add_expr);
    visitAddExpression(add_expr);
    auto rhs = add_expr->expressionResult;
    if (!relational_expr)
      ctx->expressionResult = rhs;
    else {
      auto lhs = visitRelationalExpression(relational_expr);
      auto result = binaryOperator(*ctx)->evaluate(lhs, rhs);
      if (!result.has_value()) {
        // compile error
      }
      ctx->expressionResult = result.pointee();
    }
    return {};
  }

  // visit a condition
  std::any visitCondition(CactParser::ConditionContext *ctx) override {
    auto logicalOrExpr = ctx->logicalOrExpression();
    assert(logicalOrExpr);
    visitLogicalOrExpression(logicalOrExpr);
    auto result = logicalOrExpr->expressionResult;
    if (!result.has_value())
      ctx->compileTimeResult = std::nullopt;
    else {
      assert(constEvalResultBasicType(result) == CactBasicType::Bool);
      ctx->compileTimeResult = std::make_optional<bool>(std::get<bool>(result));
    }
    return {};
  }

  // visit an if statement
  std::any visitIfStatement(CactParser::IfStatementContext *ctx) override {
    assert(ctx->statement().size() == 1 || ctx->statement().size() == 2);
    auto condition = ctx->condition();
    visitCondition(condition);
    for (auto &stmt : ctx->statement())
      visitStatement(stmt);
    if (!condition->compileTimeResult.has_value()) {
      // compile error
    } else {
      bool cond = condition->compileTimeResult.pointee();
      auto then = ctx->statement(0);
      if (cond) {
        then->reachable = std::make_optional<bool>(true);
        if (ctx->statement().size() == 2)
          ctx->statement(1)->reachable = std::make_optional<bool>(false);
      } else {
        then->reachable = std::make_optional<bool>(false);
        if (ctx->statement().size() == 2)
          ctx->statement(1)->reachable = std::make_optional<bool>(true);
      }
    }
    return {};
  }
  SymbolRegistry registry;
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
