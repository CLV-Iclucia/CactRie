//
// Created by creeper on 9/5/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_VISITOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_VISITOR_H
#include <chiisai-llvm/autogen/LLVMParserVisitor.h>
#include <chiisai-llvm/llvm-ir.h>
namespace llvm {
struct LLVMModuleParserVisitor : public LLVMParserVisitor {
  std::any visitType(LLVMParser::TypeContext* ctx) override {
    std::string typeStr = ctx->getText();

  }
  std::any visitModule(LLVMParser::ModuleContext *ctx) override {
    std::vector<Variable> globalVars;
    std::list<Function> functions;
    std::string name;
    for (auto *decl : ctx->globalDeclaration()) {
      visitGlobalDeclaration(decl);
      globalVars.push_back(decl->globalVar);
    }
    for (auto *def : ctx->functionDefinition()) {
      visitFunctionDefinition(def);
      functions.push_back(std::move(def->function));
    }
    module = std::make_unique<Module>(ModuleInfo{
        .functions = std::move(functions),
        .globalVars = std::move(globalVars),
        .name = std::move(name)
    });
    return {};
  }
  std::any visitGlobalDeclaration(LLVMParser::GlobalDeclarationContext *ctx) override {
    visitType(ctx->type());
    auto varType = ctx->type()->type;
    std::string name = ctx->globalIdentifier()->NamedIdentifier()->getText();
    ctx->globalVar = Variable(VariableInfo{
        .name = std::move(name),
        .isConstant = false,
        .initialValue = std::nullopt
    });
    return {};
  }
  std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) override {
    visitType(ctx->type());
    std::string name = ctx->functionIdentifier()->NamedIdentifier()->getText();
    std::vector<Variable> args;
    for (auto *arg : ctx->functionArguments()->functionArgument()) {
      visitFunctionArgument(arg);
      args.push_back(arg->arg);
    }
    std::list<BasicBlock> blocks;
    for (auto *block : ctx->basicBlock()) {
      visitBasicBlock(block);
      blocks.push_back(std::move(block->block));
    }
    ctx->function = Function(FunctionInfo{
        .name = std::move(name),
        .args = std::move(args),
        .blocks = std::move(blocks)
    });
    return {};
  }
  std::unique_ptr<Module> module{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_VISITOR_H
