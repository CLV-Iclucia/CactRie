//
// Created by creeper on 8/14/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
#include <cact-front-end/CactParserBaseVisitor.h>
#include <cact-front-end/cact-parser-context.h>
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/cact-operator.h>
#include <cact-front-end/symbol-registry.h>

namespace cactfrontend {

struct ConstEvalVisitor : CactParserBaseVisitor {

  // ---------------------------------------

  // initialization
  explicit ConstEvalVisitor(std::shared_ptr<SymbolRegistry> __registry) {
    this->registry = __registry;
  }

  /**
   * constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
   */
  // visit a constant definition
  std::any visitConstantDefinition(ConstantDefinitionCtx *ctx) override {
    // set the initial value of the constant
    if (ctx->constant->isInitialized()) {
      ctx->constant->init_values = getConstInitVal(ctx->constantInitialValue());
    }
    
    return {};
  }

  // constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;
  // visit a constant initial value
  std::any visitConstantInitialValue(ConstantInitialValueCtx *ctx) override {
    // If it is a constant expression, return the value's type by visiting constant expression and return the result
    if (ctx->constantExpression()) {
      std::vector<ConstEvalResult> return_vec;
      auto res = getConstExpr(ctx->constantExpression());
      return_vec.emplace_back(res);
      return return_vec;
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
  std::vector<ConstEvalResult> getConstInitVal(ConstantInitialValueCtx *ctx) {
    assert(ctx != nullptr);
    return std::any_cast<std::vector<ConstEvalResult>>(visitConstantInitialValue(ctx));
  }
  

  /**
   * variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;
   * functionParameter: dataType Identifier (LeftBracket IntegerConstant? RightBracket
   *                      (LeftBracket IntegerConstant RightBracket)*)?;
   */
  // visit a variable definition
  std::any visitVariableDefinition(VariableDefinitionCtx *ctx) override {
    // set the initial value of the variable
    if (ctx->variable->isInitialized()) {
      ctx->variable->init_values = getConstInitVal(ctx->constantInitialValue());
    }
    return {};
  }

  // visitting a functionParameter does not need to be overrided
  

  // cast std::any to std::shared_ptr<CactExpr>
  [[nodiscard]]
  std::shared_ptr<CactExpr> std_any_to_expr_ptr(std::any any) {
    return std::any_cast<std::shared_ptr<CactExpr>>(any);
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
  std::any visitAssignStatement(AssignStatementCtx *ctx) override {
    ctx->expr = std_any_to_expr_ptr(visit(ctx->expression()));
    ctx->lvalue = std::make_shared<CactExpr>(std::make_shared<CactConstVarArray>(getLeftValue(ctx->leftValue())));

    return {};
  }

  // visit a return statement
  std::any visitReturnStatement(ReturnStatementCtx *ctx) override {
    if (ctx->expression())
      ctx->expr = std_any_to_expr_ptr(visit(ctx->expression()));
    else
      ctx->expr = nullptr;
    return {};
  }  

  // visit a if statement
  std::any visitIfStatement(IfStatementCtx *ctx) override {
    ctx->cond_expr = std_any_to_expr_ptr(visit(ctx->condition()));
    // visit all statements as children of ifStatement
    for (auto &stmt : ctx->statement()) {
      visitStatement(stmt);
    }
    return {};
  }

  // visit a while statement
  std::any visitWhileStatement(WhileStatementCtx *ctx) override {
    ctx->cond_expr = std_any_to_expr_ptr(visit(ctx->condition()));
    visit(ctx->statement());
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
  std::any visitExpression(ExpressionCtx *ctx) override {
    if (ctx->addExpression()) {
      return std_any_to_expr_ptr(visit(ctx->addExpression()));
    }
    else if (ctx->BooleanConstant()) {
      bool boolean_value = (ctx->BooleanConstant()->getText().compare("true") == 0) ? true : false;
      return std::make_shared<CactExpr>(ConstEvalResult(boolean_value));
    }
    assert(0);
  }

  // visit a constant expression, and return a ConstEvalResult
  std::any visitConstantExpression(ConstantExpressionCtx *ctx) override {
    if (ctx->number()) {
      return getNumber(ctx->number());
    }
    else if (ctx->BooleanConstant()) {
      bool boolean_value = (ctx->BooleanConstant()->getText().compare("true") == 0) ? true : false;
      return ConstEvalResult(boolean_value);
    }
    assert(0);
  }

  // get the constant value of a constant expression
  ConstEvalResult getConstExpr(ConstantExpressionCtx *ctx) {
    return std::any_cast<ConstEvalResult>(visitConstantExpression(ctx));
  }

  // visit a condition
  std::any visitCondition(ConditionCtx *ctx) override {
    return std_any_to_expr_ptr(visit(ctx->logicalOrExpression()));
  }

  // visit a left value, return a CactConstVarArray
  std::any visitLeftValue(LeftValueCtx *ctx) override {
    auto symbol = CactConstVarArray(ctx->symbol);

    // "symbol" is an array and is indexed in this context
    for (auto &expr : ctx->expression()) {
      symbol.addIndex(std_any_to_expr_ptr(visit(expr)));
    }

    symbol.setOffsetByIndices();

    return symbol;
  }

  // get the array representation of a left value
  CactConstVarArray getLeftValue(LeftValueCtx *ctx) {
    return std::any_cast<CactConstVarArray>(visitLeftValue(ctx));
  }

  // visit a primary expression
  std::any visitPrimaryExpression(PrimaryExpressionCtx *ctx) override {
    CactExpr expr;
    if (ctx->expression()) {
      return std_any_to_expr_ptr(visit(ctx->expression()));
    }
    else if (ctx->leftValue()) {
      return std::make_shared<CactExpr>(std::make_shared<CactConstVarArray>(getLeftValue(ctx->leftValue())));
    }
    else if (ctx->number()) {
      return std::make_shared<CactExpr>(getNumber(ctx->number()));
    }
    assert(0);
  }

  // visit a number
  std::any visitNumber(NumberCtx *ctx) override {
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
  ConstEvalResult getNumber(NumberCtx *ctx) {
    return std::any_cast<ConstEvalResult>(visitNumber(ctx));
  }

  // visit a unary expression
  std::any visitUnaryExpression(UnaryExpressionCtx *ctx) override {
    if (ctx->primaryExpression()) {
      return std_any_to_expr_ptr(visit(ctx->primaryExpression()));
    }
    else if (ctx->unaryExpression()) {
      auto expr = std_any_to_expr_ptr(visit(ctx->unaryExpression()));
      return std::make_shared<CactExpr>(CactUnaryExpr(ctx->unary_operator, expr));
    }
    else if (ctx->Identifier()) {
      // gather all arguments into a vector of shared pointers
      std::vector<std::shared_ptr<CactExpr>> args;
      if (ctx->functionArguments()) {
        for (auto &arg : ctx->functionArguments()->expression()) {
          args.emplace_back(std_any_to_expr_ptr(visit(arg)));
        }
      }
      return std::make_shared<CactExpr>(ctx->function, args);
    }
    assert(0);
  }

  /**
   * functionArguments: expression (Comma expression)*;
   */
  // no need to override visitFunctionArguments, since it is not used in the current context

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
  // visit a mul expression
  std::any visitMulExpression(MulExpressionCtx *ctx) override {
    auto unary_expr = ctx->unaryExpression();
    auto mul_expr = ctx->mulExpression();

    if (!mul_expr && unary_expr) {
      return std_any_to_expr_ptr(visit(unary_expr));
    }
    else if (mul_expr && unary_expr) {
      auto lhs = std_any_to_expr_ptr(visit(mul_expr));
      auto rhs = std_any_to_expr_ptr(visit(unary_expr));
      return std::make_shared<CactExpr>(CactBinaryExpr(ctx->binary_operator, lhs, rhs));
    }
    assert(0);
  }

  // visit an additive expression
  std::any visitAddExpression(AddExpressionCtx *ctx) override {
    auto add_expr_ctx = ctx->addExpression();
    auto mul_expr_ctx = ctx->mulExpression();

    if (!add_expr_ctx && mul_expr_ctx) {
      return std_any_to_expr_ptr(visit(mul_expr_ctx));
    }
    else if (add_expr_ctx && mul_expr_ctx) {
      auto lhs = std_any_to_expr_ptr(visit(add_expr_ctx));
      auto rhs = std_any_to_expr_ptr(visit(mul_expr_ctx));
      return std::make_shared<CactExpr>(CactBinaryExpr(ctx->binary_operator, lhs, rhs));
    }
    assert(0);
  }

  // visit a relational expression
  std::any visitRelationalExpression(RelationalExpressionCtx *ctx) override {
    auto bool_const_ctx = ctx->BooleanConstant();
    auto add_expr_ctxs = ctx->addExpression();

    if (bool_const_ctx) {
      bool boolean_value = (bool_const_ctx->getText().compare("true") == 0) ? true : false;
      return std::make_shared<CactExpr>(ConstEvalResult(boolean_value));
    }
    else if (add_expr_ctxs.size() == 1) {
      return std_any_to_expr_ptr(visit(add_expr_ctxs.at(0)));
    }
    else if (add_expr_ctxs.size() == 2) {
      auto lhs = std_any_to_expr_ptr(visit(add_expr_ctxs.at(0)));
      auto rhs = std_any_to_expr_ptr(visit(add_expr_ctxs.at(1)));
      return std::make_shared<CactExpr>(CactBinaryExpr(ctx->binary_operator, lhs, rhs));
    }
    assert(0);
  }

  // visit a logical equal expression
  std::any visitLogicalEqualExpression(LogicalEqualExpressionCtx *ctx) override {
    auto rel_expr_ctxs = ctx->relationalExpression();

    if (rel_expr_ctxs.size() == 1) {
      return std_any_to_expr_ptr(visit(rel_expr_ctxs.at(0)));
    }
    else if (rel_expr_ctxs.size() == 2) {
      auto lhs = std_any_to_expr_ptr(visit(rel_expr_ctxs.at(0)));
      auto rhs = std_any_to_expr_ptr(visit(rel_expr_ctxs.at(1)));
      return std::make_shared<CactExpr>(CactBinaryExpr(ctx->binary_operator, lhs, rhs));
    }
    assert(0);
  }

  // visit a logical and expression
  std::any visitLogicalAndExpression(LogicalAndExpressionCtx *ctx) override {
    auto logical_eq_expr = ctx->logicalEqualExpression();
    auto logical_and_expr = ctx->logicalAndExpression();

    if (logical_eq_expr && !logical_and_expr) {
      return std_any_to_expr_ptr(visit(logical_eq_expr));
    }
    else if (logical_eq_expr && logical_and_expr) {
      auto lhs = std_any_to_expr_ptr(visit(logical_and_expr));
      auto rhs = std_any_to_expr_ptr(visit(logical_eq_expr));
      return std::make_shared<CactExpr>(CactBinaryExpr(ctx->binary_operator, lhs, rhs));
    }

    assert(0);
  }

  // visit a logical or expression
  std::any visitLogicalOrExpression(LogicalOrExpressionCtx *ctx) override {
    auto logical_and_expr = ctx->logicalAndExpression();
    auto logical_or_expr = ctx->logicalOrExpression();

    if (logical_and_expr && !logical_or_expr) {
      return std_any_to_expr_ptr(visit(logical_and_expr));
    }
    else if (logical_and_expr && logical_or_expr) {
      auto lhs = std_any_to_expr_ptr(visit(logical_or_expr));
      auto rhs = std_any_to_expr_ptr(visit(logical_and_expr));
      return std::make_shared<CactExpr>(CactBinaryExpr(ctx->binary_operator, lhs, rhs));
    }

    assert(0);
  }

  // ---------------------------------------

  std::shared_ptr<SymbolRegistry> registry;

};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_TYPE_CHECK_AND_CONST_EVAL_H_
