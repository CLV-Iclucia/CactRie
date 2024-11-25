//
// Created by creeper on 11/22/24.
//

#ifndef CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_CACT_BASE_VISITOR_H
#define CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_CACT_BASE_VISITOR_H
#include <cact-front-end/CactParser.h>
#include <cact-front-end/CactParserVisitor.h>
namespace cactfrontend {
struct CactBaseVisitor : CactParserVisitor {
  // all the visits throws an error indicating that they should not be visited
  std::any visitCompilationUnit(CactParser::CompilationUnitContext *context) override {
    throw std::runtime_error("Compilation unit should not be visited");
  }

  std::any visitDeclaration(CactParser::DeclarationContext *context) override {
    throw std::runtime_error("Declaration should not be visited");
  }

  std::any visitConstantDeclaration(CactParser::ConstantDeclarationContext *context) override {
    throw std::runtime_error("Constant declaration should not be visited");
  }

  std::any visitDataType(CactParser::DataTypeContext *context) override {
    throw std::runtime_error("Data type should not be visited");
  }

  std::any visitConstantDefinition(CactParser::ConstantDefinitionContext *context) override {
    throw std::runtime_error("Constant definition should not be visited");
  }

  std::any visitConstantInitialValue(CactParser::ConstantInitialValueContext *context) override {
    throw std::runtime_error("Constant initial value should not be visited");
  }

  std::any visitVariableDeclaration(CactParser::VariableDeclarationContext *context) override {
    throw std::runtime_error("Variable declaration should not be visited");
  }

  std::any visitVariableDefinition(CactParser::VariableDefinitionContext *context) override {
    throw std::runtime_error("Variable definition should not be visited");
  }

  std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *context) override {
    throw std::runtime_error("Function definition should not be visited");
  }

  std::any visitFunctionType(CactParser::FunctionTypeContext *context) override {
    throw std::runtime_error("Function type should not be visited");
  }

  std::any visitFunctionParameters(CactParser::FunctionParametersContext *context) override {
    throw std::runtime_error("Function parameters should not be visited");
  }

  std::any visitFunctionParameter(CactParser::FunctionParameterContext *context) override {
    throw std::runtime_error("Function parameter should not be visited");
  }

  std::any visitBlock(CactParser::BlockContext *context) override {
    throw std::runtime_error("Block should not be visited");
  }

  std::any visitBlockItem(CactParser::BlockItemContext *context) override {
    throw std::runtime_error("Block item should not be visited");
  }

  std::any visitStatement(CactParser::StatementContext *context) override {
    throw std::runtime_error("Statement should not be visited");
  }

  std::any visitAssignStatement(CactParser::AssignStatementContext *context) override {
    throw std::runtime_error("Assign statement should not be visited");
  }

  std::any visitExpressionStatement(CactParser::ExpressionStatementContext *context) override {
    throw std::runtime_error("Expression statement should not be visited");
  }

  std::any visitReturnStatement(CactParser::ReturnStatementContext *context) override {
    throw std::runtime_error("Return statement should not be visited");
  }

  std::any visitIfStatement(CactParser::IfStatementContext *context) override {
    throw std::runtime_error("If statement should not be visited");
  }

  std::any visitWhileStatement(CactParser::WhileStatementContext *context) override {
    throw std::runtime_error("While statement should not be visited");
  }

  std::any visitBreakStatement(CactParser::BreakStatementContext *context) override {
    throw std::runtime_error("Break statement should not be visited");
  }

  std::any visitContinueStatement(CactParser::ContinueStatementContext *context) override {
    throw std::runtime_error("Continue statement should not be visited");
  }

  std::any visitExpression(CactParser::ExpressionContext *context) override {
    throw std::runtime_error("Expression should not be visited");
  }

  std::any visitConstantExpression(CactParser::ConstantExpressionContext *context) override {
    throw std::runtime_error("Constant expression should not be visited");
  }

  std::any visitCondition(CactParser::ConditionContext *context) override {
    throw std::runtime_error("Condition should not be visited");
  }

  std::any visitLeftValue(CactParser::LeftValueContext *context) override {
    throw std::runtime_error("Left value should not be visited");
  }

  std::any visitPrimaryExpression(CactParser::PrimaryExpressionContext *context) override {
    throw std::runtime_error("Primary expression should not be visited");
  }

  std::any visitNumber(CactParser::NumberContext *context) override {
    throw std::runtime_error("Number should not be visited");
  }

  std::any visitUnaryExpression(CactParser::UnaryExpressionContext *context) override {
    throw std::runtime_error("Unary expression should not be visited");
  }

  std::any visitFunctionArguments(CactParser::FunctionArgumentsContext *context) override {
    throw std::runtime_error("Function arguments should not be visited");
  }

  std::any visitMulExpression(CactParser::MulExpressionContext *context) override {
    throw std::runtime_error("Mul expression should not be visited");
  }

  std::any visitAddExpression(CactParser::AddExpressionContext *context) override {
    throw std::runtime_error("Add expression should not be visited");
  }

  std::any visitRelationalExpression(CactParser::RelationalExpressionContext *context) override {
    throw std::runtime_error("Relational expression should not be visited");
  }

  std::any visitLogicalEqualExpression(CactParser::LogicalEqualExpressionContext *context) override {
    throw std::runtime_error("Logical equal expression should not be visited");
  }

  std::any visitLogicalAndExpression(CactParser::LogicalAndExpressionContext *context) override {
    throw std::runtime_error("Logical and expression should not be visited");
  }

  std::any visitLogicalOrExpression(CactParser::LogicalOrExpressionContext *context) override {
    throw std::runtime_error("Logical or expression should not be visited");
  }
};
}
#endif //CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_CACT_BASE_VISITOR_H
