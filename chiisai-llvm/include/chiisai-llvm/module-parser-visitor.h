//
// Created by creeper on 9/5/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_VISITOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_VISITOR_H
#include <chiisai-llvm/autogen/LLVMParserVisitor.h>
#include <chiisai-llvm/llvm-ir.h>
namespace llvm {
struct LLVMModuleParserVisitor : public LLVMParserVisitor {
  std::any visitType(LLVMParser::TypeContext *ctx) override {
    std::string typeStr = ctx->getText();
    if (typeStr == "i32") {
      ctx->llvmType = LLVMType::i32;
    } else if (typeStr == "i1") {
      ctx->llvmType = LLVMType::i1;
    } else if (typeStr == "f32") {
      ctx->llvmType = LLVMType::f32;
    } else if (typeStr == "f64") {
      ctx->llvmType = LLVMType::f64;
    } else if (typeStr == "void") {
      ctx->llvmType = LLVMType::Void;
    } else {
      throw std::runtime_error("Invalid type");
    }
    return {};
  }
  std::any visitModule(LLVMParser::ModuleContext *ctx) override {
    std::vector<Variable> globalVars{};
    std::list<Function> functions{};
    std::string name;
    for (auto *decl : ctx->globalDeclaration()) {
      visitGlobalDeclaration(decl);
      globalVars.push_back(decl->globalVar);
    }
    for (auto *def : ctx->functionDefinition()) {
      visitFunctionDefinition(def);
      functions.push_back(std::move(*def->function));
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
    auto varType = ctx->type()->llvmType;
    std::string name = ctx->globalIdentifier()->NamedIdentifier()->getText();
    ctx->globalVar = Variable(VariableInfo{
        .name = std::move(name),
        .isConstant = false,
        .initialValue = std::nullopt
    });
    auto literal = ctx->literal();
    if (literal) {
      visitLiteral(literal);
      ctx->globalVar.initialValue() = literal->result;
      if (!ctx->globalVar.match(varType)) {
        // ERROR
      }
    }
    return {};
  }
  std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) override {
    visitType(ctx->type());
    std::string name = ctx->globalIdentifier()->NamedIdentifier()->getText();
    std::vector<Variable> args;
    visitFunctionArguments(ctx->functionArguments());
    visitBlock(ctx->block());
    ctx->function = std::make_unique<Function>(FunctionInfo{
        .name = std::move(name),
    });
    return {};
  }
  std::unique_ptr<Module> module{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_VISITOR_H
