//
// Created by creeper on 8/14/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
#include <cact-front-end/mystl/observer_ptr.h>
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

  // ---------------------------------------

  // initialization
  explicit ConstEvalVisitor(std::unique_ptr<SymbolRegistry> registry) {
    this->registry = make_observer(registry.get());
  }

  /**
   * constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
   */
  // visit a constant definition
  std::any visitConstantDefinition(CactParser::ConstantDefinitionContext *ctx) override {
    // set the initial value of the constant
    if (ctx->constant.isInitialized()) {
      ctx->constant.init_values = getConstInitVal(ctx->constantInitialValue());
    }
    
    return {};
  }

  // constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;
  // visit a constant initial value
  std::any visitConstantInitialValue(CactParser::ConstantInitialValueContext *ctx) override {
    // If it is a constant expression, return the value's type by visiting constant expression and return the result
    if (ctx->constantExpression()) {
      return std::vector<ConstEvalResult>(getConstExpr(ctx->constantExpression()));
    }
    // If it is a list of constant values, return a vector of constant values.
    // The return value is a vector of constant values with the same type.
    // The width of vector is (size(current_dim) / size(basic_type))
    else {
      std::vector<ConstEvalResult> values;

      uint32_t width = ctx->type.width(ctx->current_dim); // width of the current dimension
      assert(width != 0);
      uint32_t size_of_basic_type = sizeOf(ctx->type.basic_type); // size of the basic type
      uint32_t child_num = ctx->constantInitialValue().size(); // number of children in the list
      uint32_t expected_child_num; // expected number of children in the list
      uint32_t child_width; // width of the children

      // if flat_flag is set, the values are stored in a flat array at dim-0
      if (ctx->flat_flag) {
        assert(ctx->current_dim == 0);
        expected_child_num = ctx->type.size() / size_of_basic_type;
        child_width = 1u;
      }
      else {
       expected_child_num = width;
       child_width = ctx->type.size(ctx->current_dim + 1) / size_of_basic_type;
      }
      assert(child_num <= expected_child_num); // the number of children is no more than expected

      for (auto &child : ctx->constantInitialValue()) {
        auto value = getConstInitVal(child);
        values.insert(values.end(), value.begin(), value.end());
      }
      assert(values.size() == child_width * child_num); // check if the number of values inputed is correct

      // pad the values with 0 if the number of values is less than expected
      values.resize(child_width * expected_child_num, 0);

      return values;
    }
  }

  // get the value vector after visiting a constant expression
  std::vector<ConstEvalResult> getConstInitVal(CactParser::ConstantInitialValueContext *ctx) {
    assert(ctx != nullptr);
    return std::any_cast<std::vector<ConstEvalResult>>(visitConstantInitialValue(ctx));
  }
  

  /**
   * variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;
   * functionParameter: dataType Identifier (LeftBracket IntegerConstant? RightBracket
   *                      (LeftBracket IntegerConstant RightBracket)*)?;
   */
  // visit a variable definition
  std::any visitVariableDefinition(CactParser::VariableDefinitionContext *ctx) override {
    // set the initial value of the variable
    if (ctx->variable.isInitialized()) {
      ctx->variable.init_values = getConstInitVal(ctx->constantInitialValue());
    }
    return {};
  }

  // visitting a functionParameter does not need to be overrided
  

  // cast std::any to observer_ptr<CactExpr>
  [[nodiscard]]
  observer_ptr<CactExpr> std_any_to_expr_ptr(std::any any) {
    return std::any_cast<observer_ptr<CactExpr>>(any);
  }


  /**
   * assignStatement: leftValue Equal expression Semicolon;
   * returnStatement: Return expression? Semicolon;
   * ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?;
   * whileStatement: While LeftParenthesis condition RightParenthesis statement;
  xxx * breakStatement: Break Semicolon;
  xxx * continueStatement: Continue Semicolon;
   */
  // visit an assign statement
  std::any visitAssignStatement(CactParser::AssignStatementContext *ctx) override {
    ctx->expr = *std_any_to_expr_ptr(visit(ctx->expression()));
    ctx->lvalue = *std_any_to_expr_ptr(visit(ctx->leftValue()));

    return {};
  }

  // visit a return statement
  std::any visitReturnStatement(CactParser::ReturnStatementContext *ctx) override {
    ctx->expr = *std_any_to_expr_ptr(visit(ctx->expression()));
    return {};
  }  

  // visit a if statement
  std::any visitIfStatement(CactParser::IfStatementContext *ctx) override {
    ctx->cond_expr = *std_any_to_expr_ptr(visit(ctx->condition()));
    return {};
  }

  // visit a while statement
  std::any visitWhileStatement(CactParser::WhileStatementContext *ctx) override {
    ctx->cond_expr = *std_any_to_expr_ptr(visit(ctx->condition()));
    return {};
  }



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


  // visit an expression
  std::any visitExpression(CactParser::ExpressionContext *ctx) override {
    if (ctx->addExpression()) {
      return std_any_to_expr_ptr(visit(ctx->addExpression()));
    }
    else {
      assert(ctx->BooleanConstant());
      bool boolean_value = (ctx->BooleanConstant()->getText().compare("true") == 0) ? true : false;
      return make_uniq_observer<CactExpr>(CactExpr(boolean_value));
    }
  }

  // visit a constant expression, and return a ConstEvalResult
  std::any visitConstantExpression(CactParser::ConstantExpressionContext *ctx) override {
    if (ctx->number()) {
      return getNumber(ctx->number());
    }
    else {
      assert(ctx->BooleanConstant());
      bool boolean_value = (ctx->BooleanConstant()->getText().compare("true") == 0) ? true : false;
      return ConstEvalResult(boolean_value);
    }
  }

  // get the constant value of a constant expression
  ConstEvalResult getConstExpr(CactParser::ConstantExpressionContext *ctx) {
    return std::any_cast<ConstEvalResult>(visitConstantExpression(ctx));
  }

  // visit a condition
  std::any visitCondition(CactParser::ConditionContext *ctx) override {
    return std_any_to_expr_ptr(visit(ctx->logicalOrExpression()));
  }

  // visit a left value, return a CactConstVarArray
  std::any visitLeftValue(CactParser::LeftValueContext *ctx) override {
    auto symbol = CactConstVarArray(ctx->symbol);

    // "symbol" is an array and is indexed in this context
    for (auto &expr : ctx->expression()) {
      symbol.addIndex(*std_any_to_expr_ptr(visit(expr)));
    }

    symbol.setOffsetByIndices();

    return symbol;
  }

  // get the array representation of a left value
  CactConstVarArray getLeftValue(CactParser::LeftValueContext *ctx) {
    return std::any_cast<CactConstVarArray>(visitLeftValue(ctx));
  }

  // visit a primary expression
  std::any visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) override {
    CactExpr expr;
    if (ctx->expression()) {
      return std_any_to_expr_ptr(visit(ctx->expression()));
    }
    else if (ctx->leftValue()) {
      return make_uniq_observer<CactExpr>(CactExpr(getLeftValue(ctx->leftValue())));
    }
    else if (ctx->leftValue()) {
      return make_uniq_observer<CactExpr>(CactExpr(getNumber(ctx->number())));
    }
    assert(0);
  }

  // visit a number
  std::any visitNumber(CactParser::NumberContext *ctx) override {
    if (ctx->IntegerConstant()) {
      return ConstEvalResult(std::stoi(ctx->IntegerConstant()->getText()));
    } else if (ctx->FloatConstant()) {
      return ConstEvalResult(std::stof(ctx->FloatConstant()->getText()));
    } else if (ctx->DoubleConstant()) {
      return ConstEvalResult(std::stod(ctx->DoubleConstant()->getText()));
    }
    assert(0);
  }

  // get the constant value of a number
  ConstEvalResult getNumber(CactParser::NumberContext *ctx) {
    return std::any_cast<ConstEvalResult>(visitNumber(ctx));
  }

  // visit a unary expression
  std::any visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) override {
    if (ctx->primaryExpression()) {
      return std_any_to_expr_ptr(visit(ctx->primaryExpression()));
    }
    else if (ctx->unaryExpression()) {
      auto expr = std_any_to_expr_ptr(visit(ctx->unaryExpression()));
      return make_uniq_observer<CactExpr>(CactUnaryExpr(ctx->unary_operator, expr));
    }
    else if (ctx->Identifier()) {
      // the function has already been recorded
      auto func = ctx->function;

      // gather all arguments into a vector of observer_ptr
      std::vector<observer_ptr<CactExpr>> args;
      for 
    }
    assert(0);
  }

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
  // ---------------------------------------

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
      ctx->expressionResult = result.value();
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
      ctx->expressionResult = result.value();
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
      ctx->expressionResult = result.value();
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
      ctx->expressionResult = result.value();
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
      ctx->expressionResult = result.value();
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
      ctx->expressionResult = result.value();
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
      bool cond = condition->compileTimeResult.value();
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


  observer_ptr<SymbolRegistry> registry;

};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
