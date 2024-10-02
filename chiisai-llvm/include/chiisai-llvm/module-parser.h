//
// Created by creeper on 9/5/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_H
#include <chiisai-llvm/autogen/LLVMParserVisitor.h>
namespace llvm {
struct Module;
struct LLVMContext;
struct ModuleParser : public LLVMParserVisitor {
  std::any visitType(LLVMParser::TypeContext *ctx) override {
    auto basicTy = ctx->basicType();
    auto arrayTy = ctx->arrayType();
    auto pointerTy = ctx->pointerType();
    if (basicTy) {
      assert(!arrayTy && ! pointerTy);
      visitBasicType(basicTy);
    } else if (arrayTy) {
      assert(!pointerTy);
      visitArrayType(arrayTy);
    } else if (pointerTy) {
      visitPointerType(pointerTy);
    } else
      throw std::runtime_error("the type is neither basic, array nor pointer type, which is impossible");
    return {};
  }
  std::any visitBasicType(LLVMParser::BasicTypeContext *ctx) override;
  std::any visitArrayType(LLVMParser::ArrayTypeContext *ctx) override;
  std::any visitPointerType(LLVMParser::PointerTypeContext *ctx) override;
  std::any visitModule(LLVMParser::ModuleContext *ctx) override;
  std::any visitGlobalDeclaration(LLVMParser::GlobalDeclarationContext *ctx) override {
    visitType(ctx->type());
    auto varType = ctx->type()->typeRef;
    std::string name = ctx->globalIdentifier()->NamedIdentifier()->getText();
    return {};
  }
  std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) override {
    return {};
  }
  std::any visitBasicBlock(LLVMParser::BasicBlockContext *ctx) override {
    ctx->basicBlockInstance = std::make_unique<BasicBlock>(ctx->Label()->getText());
    const auto& instructions = ctx->instruction();
    for (auto inst : instructions) {
      visitInstruction(inst);
      ctx->basicBlockInstance->instructions.push_back<Instruction>(std::move(inst->inst));
    }
    return {};
  }
  std::any visitInstruction(LLVMParser::InstructionContext *ctx) override {
    if (ctx->arithmeticInstruction()) {
      visitArithmeticInstruction(ctx->arithmeticInstruction());
    }
  }
  std::any visitArithmeticInstruction(LLVMParser::ArithmeticInstructionContext *ctx) override {
    auto op = stoinst(ctx->binaryOperation()->getText());
    auto lhs = ctx->localVariable();
    ctx->inst =
  }
  std::map<std::string, CRef<Value>> instructionResultMap{};
  std::unique_ptr<Module> module{};
  std::unique_ptr<LLVMContext> llvmContext{};
private:
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_H
