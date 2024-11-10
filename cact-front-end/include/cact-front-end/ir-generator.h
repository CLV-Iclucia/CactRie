//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
#include <cact-front-end/CactParser.h>
#include <cact-front-end/CactParserVisitor.h>
#include <cact-front-end/cact-operator.h>
#include <sstream>

namespace cactfrontend {

// struct to generate IR code
struct IRGenerator : public CactParserVisitor {
  // constructor, initialize the output stream and the name of the module
  explicit IRGenerator(std::ostream &os, const std::string &name) : irCodeStream(os), name(name) {}

  // visit a compilation unit
  std::any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override {
    // output the module name
    irCodeStream << "; ModuleID = '"
                 << name
                 << "'\nsource_filename = \""
                 << name
                 << ".cact\"\n";
    // visit all children
    for (auto &child : ctx->children)
      visit(child);
    return {};
  }

  // visit a function definition
  std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override {
    // visit all children
    for (auto &child : ctx->children)
      visit(child);
    irCodeStream << "}\n";
    return {};
  }

  // visit an add expression
  std::any visitAddExpression(CactParser::AddExpressionContext *ctx) override {
    // if the result is a compile time constant, return
    if (ctx->expressionResult.compileTimeEvalResult().has_value())
      return {};
    // visit the add expression, and then the mul expression
    if (ctx->addExpression())
      visitAddExpression(ctx->addExpression());
    visitMulExpression(ctx->mulExpression());

    irCodeStream << "%"
                 << temporaryName(ctx->tmpResultID)
                 << " = "
                 << typeString(toLLVMType(ctx->expressionResult.type()))
                 << " "
                 << resultString(ctx->addExpression())
                 << " "
                 << resultString(ctx->mulExpression())
                 << "\n"
                 ;
    return {};
  }

  // visit a mul expression
  std::any visitMulExpression(CactParser::MulExpressionContext *ctx) override {
    // visit the mul expression, and then the unary expression
    if (ctx->mulExpression())
      visitMulExpression(ctx->mulExpression());
    visitUnaryExpression(ctx->unaryExpression());

    return {};
  }

private:
  template<typename ExpressionContext>

  // get the result string of the expression
  std::string resultString(ExpressionContext *ctx) {
    if (ctx->expressionResult.compileTimeEvalResult.has_value())
      return ctx->expressionResult.toString();
    return "%" + temporaryName(ctx->expressionResult.tmpResultID);
  }

  // get the temporary name
  std::string temporaryName(int id) {
    return "_tmp_" + std::to_string(id);
  }

  // get the operator type string
  std::string operatorString(CactParser::AddExpressionContext *ctx) {
    if (ctx->Plus())
      return "add";
    return "sub";
  }
  int temporaryID = 0;
  // and output stream to output the generated IR chars
  std::ostream &irCodeStream;
  std::string name;
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
