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
      assert(!arrayTy && !pointerTy);
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
    auto returnTypeCtx = ctx->type();
    auto funcName = ctx->globalIdentifier()->NamedIdentifier()->getText();
    visitType(returnTypeCtx);
    auto returnType = returnTypeCtx->typeRef;
    auto args = ctx->functionArguments();
    visitFunctionArguments(args);
    const auto &basicBlocks = ctx->basicBlock();
    std::list<BasicBlock> basicBlocksList{};
    for (auto bb : basicBlocks) {
      visitBasicBlock(bb);
    }
    return {};
  }
  std::any visitFunctionArguments(LLVMParser::FunctionArgumentsContext *ctx) override {
    visitParameterList(ctx->parameterList());
    return {};
  }
  std::any visitParameterList(LLVMParser::ParameterListContext *ctx) override {
    const auto &params = ctx->parameter();
    for (auto param : params)
      visitParameter(param);
    return {};
  }
  std::any visitParameter(LLVMParser::ParameterContext *ctx) override {
    auto argType = ctx->type();
    auto argName = ctx->localIdentifier()->NamedIdentifier()->getText();
    visitType(argType);
    return {};
  }
  std::any visitBasicBlock(LLVMParser::BasicBlockContext *ctx) override {
    ctx->basicBlockInstance = std::make_unique<BasicBlock>(ctx->Label()->getText());
    const auto &instructions = ctx->instruction();
    for (auto inst : instructions) {
      visitInstruction(inst);
      ctx->basicBlockInstance->instructions.push_back<Instruction>(std::move(inst->inst));
    }
    return {};
  }
  std::any visitInstruction(LLVMParser::InstructionContext *ctx) override {
    if (ctx->arithmeticInstruction())
      visitArithmeticInstruction(ctx->arithmeticInstruction());
  }
  std::any visitArithmeticInstruction(LLVMParser::ArithmeticInstructionContext *ctx) override {
    auto op = stoinst(ctx->binaryOperation()->getText());
    auto lhs = ctx->localVariable();
    const auto &operands = ctx->value();
    if (operands.size() != 2)
      throw std::runtime_error("Arithmetic instruction must have exactly two operands");
    auto operandLeftRef = resolveValueUsage(operands[0]);
    auto operandRightRef = resolveValueUsage(operands[1]);
    instructionResultMap[lhs->getText()] = std::make_unique<Instruction>(op, operands[0], operands[1]);
    return {};
  }
  std::any visitVariable(LLVMParser::VariableContext *ctx) override {
    ctx->isGlobal = ctx->globalIdentifier() != nullptr;
    return {};
  }
  std::any visitValue(LLVMParser::ValueContext *ctx) override {
    auto var = ctx->variable();
    auto number = ctx->number();
    if (var) {
      visitVariable(var);
      ctx->isConstant = false;
      ctx->isGlobal = var->isGlobal;
    } else if (number) {
      visitNumber(number);
      ctx->isConstant = true;
    } else
      throw std::runtime_error("Value must be either a variable or a number");
    return {};
  }
  std::map<std::string, CRef<Value>> instructionResultMap{};
  std::unique_ptr<Module> module{};
  std::unique_ptr<LLVMContext> llvmContext{};
private:
  CRef<Value> resolveValueUsage(LLVMParser::ValueContext *ctx) {
    visitValue(ctx);
    auto str = ctx->getText();
    if (ctx->isConstant) {

    } else if (ctx->isGlobal) {
      return module->globalVariable(str);
    }
    if (!instructionResultMap.contains(str))
      throw std::runtime_error("Value is not defined");
    return instructionResultMap[str];
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_PARSER_H
