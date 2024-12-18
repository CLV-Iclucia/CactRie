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

struct BuildResult {
  std::unique_ptr<Module> module{};
  std::unique_ptr<LLVMContext> llvmContext{};
};

struct ModuleBuilder final : public LLVMParserVisitor {

  std::any visitInitializer(LLVMParser::InitializerContext *ctx) override;

  std::any visitType(LLVMParser::TypeContext *ctx) override;

  std::any visitBasicType(LLVMParser::BasicTypeContext *ctx) override;

  std::any visitArrayType(LLVMParser::ArrayTypeContext *ctx) override;

  std::any visitPointerType(LLVMParser::PointerTypeContext *ctx) override;

  std::any visitModule(LLVMParser::ModuleContext *ctx) override;

  std::any visitGlobalDeclaration(LLVMParser::GlobalDeclarationContext *ctx) override {
  }

  std::any visitScalarType(LLVMParser::ScalarTypeContext *ctx) override;

  std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) override;

  std::any visitFunctionArguments(LLVMParser::FunctionArgumentsContext *ctx) override {
    auto params = ctx->parameterList();
    visitParameterList(params);
    ctx->argNames = std::move(params->argNames);
    ctx->argTypes = std::move(params->argTypes);
    return {};
  }

  std::any visitParameterList(LLVMParser::ParameterListContext *ctx) override {
    for (auto params = ctx->parameter(); auto param : params) {
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

  std::any visitImmediatelyUsableValue(LLVMParser::ImmediatelyUsableValueContext *ctx) override;

  std::any visitGepInstruction(LLVMParser::GepInstructionContext *ctx) override;

  std::any visitConstantArray(LLVMParser::ConstantArrayContext *ctx) override;

  std::any visitReturnInstruction(LLVMParser::ReturnInstructionContext *ctx) override;

  std::any visitBranchInstruction(LLVMParser::BranchInstructionContext *ctx) override;

  std::any visitCallInstruction(LLVMParser::CallInstructionContext *ctx) override;

  std::any visitPhiInstruction(LLVMParser::PhiInstructionContext *ctx) override;

  std::any visitPhiValue(LLVMParser::PhiValueContext *ctx) override;

  std::any visitComparisonOperation(LLVMParser::ComparisonOperationContext *ctx) override {
    throw std::runtime_error("Comparison operation should not be visited");
  }

  std::any visitBinaryOperation(LLVMParser::BinaryOperationContext *ctx) override {
    throw std::runtime_error("Binary operation should not be visited");
  }

  std::any visitComparisonPredicate(LLVMParser::ComparisonPredicateContext *ctx) override {
    throw std::runtime_error("Comparison predicate should not be visited");
  }

  std::any visitLiteral(LLVMParser::LiteralContext *ctx) override {
    throw std::runtime_error("Literal context should not be visited");
  }

  std::any visitNumber(LLVMParser::NumberContext *ctx) override {
    throw std::runtime_error("Number context should not be visited");
  }

  BuildResult build(LLVMParser::ModuleContext *ctx);

  Ref<Function> currentFunction{};
  Ref<BasicBlock> currentBasicBlock{};
private:
  std::unique_ptr<Module> module{};
  std::unique_ptr<LLVMContext> llvmContext{};
  Ref<Value> resolveImmediateValueUsage(LLVMParser::ImmediatelyUsableValueContext *ctx);
  Ref<Value> resolveValueUsage(CRef<Type> type, const std::string& name);
  Ref<Value> resolveVariableUsage(LLVMParser::VariableContext *ctx);
  Ref<Value> resolveVariableUsageAfterVisit(LLVMParser::VariableContext *ctx) const;
  template<typename T>
  static std::string variableName(T *ctx) {
    return ctx->getText();
  }

public:
  std::any visitGlobalIdentifier(LLVMParser::GlobalIdentifierContext* context) override;
  std::any visitLocalIdentifier(LLVMParser::LocalIdentifierContext* context) override;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_BUILDER_H
