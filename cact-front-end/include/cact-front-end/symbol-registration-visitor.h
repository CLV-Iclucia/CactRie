//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
#include <cact-front-end/CactParserBaseVisitor.h>
#include <cact-front-end/symbol-registry.h>
namespace cactfrontend {
struct SymbolRegistrationVisitor : public CactParserBaseVisitor {
  SymbolRegistrationVisitor() : registry(std::make_unique<SymbolRegistry>()) = default;
  std::any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override {
    currentScope = registry->newScope();
    for (auto &child : ctx->children)
      visit(child);
    return {};
  }
  std::any visitVariableDefinition(CactParser::VariableDefinitionContext *ctx) override {
    ctx->scope = currentScope;
    auto name = ctx->Identifier()->getText();
    ctx->scope->registerVariable(name, variable);
    return {};
  }
  std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override {
    ctx->scope = currentScope;
    auto name = ctx->Identifier()->getText();
    auto function = CactFunction{};
    registry->newFunction(name, function);
    return {};
  }
  std::unique_ptr<SymbolRegistry> registry{};
  observer_ptr<Scope> currentScope{};
};
}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
