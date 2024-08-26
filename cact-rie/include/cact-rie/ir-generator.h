//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
#include "cact-parser/CactParserBaseVisitor.h"
#include "cact-rie/mini-llvm/llvm-ir.h"
#include "cact-parser/cact-operator.h"
#include <sstream>
#include <format>
namespace cactrie {

struct IRGenerator : public cactparser::CactParserBaseVisitor {
  explicit IRGenerator(std::ostream &os, const std::string &name) : irCodeStream(os), name(name) {}
  std::any visitCompilationUnit(cactparser::CactParser::CompilationUnitContext *ctx) override {
    irCodeStream << std::format("; ModuleID = '{}'\nsource_filename = \"{}.cact\"\n", name, name);
    for (auto &child : ctx->children)
      visit(child);
    return {};
  }

  std::any visitFunctionDefinition(cactparser::CactParser::FunctionDefinitionContext *ctx) override {
    for (auto &child : ctx->children)
      visit(child);
    irCodeStream << "}\n";
    return {};
  }

  std::any visitAddExpression(cactparser::CactParser::AddExpressionContext *ctx) override {
    if (ctx->expressionResult.compileTimeEvalResult().has_value())
      return {};
    if (ctx->addExpression())
      visitAddExpression(ctx->addExpression());
    visitMulExpression(ctx->mulExpression());
    ctx->tmpResultID = temporaryID++;
    irCodeStream << std::format("%{} = {} {} {} {}\n",

                                temporaryName(ctx->tmpResultID),
                                typeString(toLLVMType(ctx->expressionResult.type())),
                                resultString(ctx->addExpression()),
                                resultString(ctx->mulExpression()));
    return {};
  }

  std::any visitMulExpression(cactparser::CactParser::MulExpressionContext *ctx) override {
    if (ctx->mulExpression())
      visitMulExpression(ctx->mulExpression());
    visitUnaryExpression(ctx->unaryExpression());
    ctx->tmpResultID = temporaryID++;

    return {};
  }

private:
  template<typename ExpressionContext>
  std::string resultString(ExpressionContext *ctx) {
    if (ctx->expressionResult.compileTimeEvalResult.has_value())
      return ctx->expressionResult.toString();
    return "%" + temporaryName(ctx->expressionResult.tmpResultID);
  }
  std::string temporaryName(int id) {
    return "_tmp_" + std::to_string(id);
  }
  std::string operatorString(cactparser::CactParser::AddExpressionContext *ctx) {
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
