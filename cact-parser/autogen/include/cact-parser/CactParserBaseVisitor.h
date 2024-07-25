
// Generated from ./grammar/CactParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CactParserVisitor.h"


namespace cactparser {

/**
 * This class provides an empty implementation of CactParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CactParserBaseVisitor : public CactParserVisitor {
public:

  virtual std::any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(CactParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(CactParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDefinition(CactParser::VariableDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(CactParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantDeclaration(CactParser::ConstantDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantDefinition(CactParser::ConstantDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantInitialValue(CactParser::ConstantInitialValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(CactParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionFormalParams(CactParser::FunctionFormalParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionFormalParam(CactParser::FunctionFormalParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(CactParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(CactParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CactParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(CactParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantExpression(CactParser::ConstantExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(CactParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLeftValue(CactParser::LeftValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(CactParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(CactParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(CactParser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionRealParams(CactParser::FunctionRealParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpression(CactParser::MulExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpression(CactParser::AddExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(CactParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalEqualExpression(CactParser::LogicalEqualExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace cactparser
