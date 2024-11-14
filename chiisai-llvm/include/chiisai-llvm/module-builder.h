//
// Created by creeper on 9/5/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_BUILDER_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_BUILDER_H
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/ir-builder.h>
#include <chiisai-llvm/autogen/LLVMParserVisitor.h>
namespace llvm {
struct Module;
struct LLVMContext;

struct ModuleBuilder : public LLVMParserVisitor {
  std::any visitType(LLVMParser::TypeContext *ctx) override;

  std::any visitBasicType(LLVMParser::BasicTypeContext *ctx) override;

  std::any visitArrayType(LLVMParser::ArrayTypeContext *ctx) override;

  std::any visitPointerType(LLVMParser::PointerTypeContext *ctx) override;

  std::any visitModule(LLVMParser::ModuleContext *ctx) override;

  std::any visitGlobalDeclaration(LLVMParser::GlobalDeclarationContext *ctx) override {
    visitType(ctx->type());
    auto varType = ctx->type()->typeRef;
    std::string name = variableName(ctx->globalIdentifier());
    return {};
  }

  std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) override;

  std::any visitFunctionArguments(LLVMParser::FunctionArgumentsContext *ctx) override {
    auto params = ctx->parameterList();
    visitParameterList(params);
    ctx->argNames = std::move(params->argNames);
    ctx->argTypes = std::move(params->argTypes);
    return {};
  }

  std::any visitParameterList(LLVMParser::ParameterListContext *ctx) override {
    auto params = ctx->parameter();
    for (auto param : params) {
      visitParameter(param);
      ctx->argTypes.emplace_back(param->argType);
      ctx->argNames.emplace_back(param->argName);
    }
    return {};
  }

  std::any visitParameter(LLVMParser::ParameterContext *ctx) override {
    auto argType = ctx->type();
    auto argName = variableName(ctx->localIdentifier());
    visitType(argType);
    ctx->argType = argType->typeRef;
    ctx->argName = argName;
    return {};
  }

  std::any visitBasicBlock(LLVMParser::BasicBlockContext *ctx) override;

  std::any visitComparisonInstruction(LLVMParser::ComparisonInstructionContext *ctx) override;

  std::any visitInstruction(LLVMParser::InstructionContext *ctx) override {
    if (ctx->arithmeticInstruction())
      visitArithmeticInstruction(ctx->arithmeticInstruction());

    if (ctx->allocaInstruction())
      visitAllocaInstruction(ctx->allocaInstruction());

    if (ctx->comparisonInstruction())
      visitComparisonInstruction(ctx->comparisonInstruction());

    if (ctx->loadInstruction())
      visitLoadInstruction(ctx->loadInstruction());

    if (ctx->storeInstruction())
      visitStoreInstruction(ctx->storeInstruction());

    if (ctx->gepInstruction())
      visitGepInstruction(ctx->gepInstruction());

    if (ctx->terminatorInstruction())
      visitTerminatorInstruction(ctx->terminatorInstruction());

    return {};
  }

  std::any visitTerminatorInstruction(LLVMParser::TerminatorInstructionContext *ctx) override {
    if (ctx->returnInstruction())
      visitReturnInstruction(ctx->returnInstruction());

    if (ctx->branchInstruction())
      visitBranchInstruction(ctx->branchInstruction());

    return {};
  }

  std::any visitLoadInstruction(LLVMParser::LoadInstructionContext *ctx) override;

  std::any visitStoreInstruction(LLVMParser::StoreInstructionContext *ctx) override;

  std::any visitAllocaInstruction(LLVMParser::AllocaInstructionContext *ctx) override;

  std::any visitArithmeticInstruction(LLVMParser::ArithmeticInstructionContext *ctx) override;

  std::any visitVariable(LLVMParser::VariableContext *ctx) override {
    ctx->isGlobal = ctx->globalIdentifier() != nullptr;
    return {};
  }

  std::any visitValue(LLVMParser::ValueContext *ctx) override;

  std::any visitGepInstruction(LLVMParser::GepInstructionContext *ctx) override;
  std::unique_ptr<Module> module{};
  std::unique_ptr<LLVMContext> llvmContext{};
  Ref<Function> currentFunction{};
  Ref<BasicBlock> currentBasicBlock{};

private:
  Ref<Value> resolveValueUsage(LLVMParser::ValueContext *ctx);
  template<typename T>
  std::string variableName(T *ctx) {
    return ctx->getText();
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_BUILDER_H
