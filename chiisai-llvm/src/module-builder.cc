//
// Created by creeper on 9/29/24.
//
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/module-builder.h>
#include <chiisai-llvm/mystl/castings.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/module.h>
namespace llvm {

std::any llvm::ModuleBuilder::visitModule(LLVMParser::ModuleContext *ctx) {
  llvmContext = std::make_unique<LLVMContext>();
  return {};
}
std::any ModuleBuilder::visitBasicType(LLVMParser::BasicTypeContext *ctx) {
  auto typeStr = ctx->getText();
  ctx->typeRef = llvmContext->stobt(typeStr);
  return {};
}
std::any ModuleBuilder::visitArrayType(LLVMParser::ArrayTypeContext *ctx) {
  auto elementTypeNode = ctx->type();
  visitType(ctx->type());
  size_t size = std::stoul(ctx->IntegerLiteral()->getText());
  auto elementType = elementTypeNode->typeRef;
  if (elementType == Type::voidType(*llvmContext)) {
    // ERROR
  }
  ctx->typeRef = llvmContext->arrayType(elementType, size);
  return {};
}
std::any ModuleBuilder::visitPointerType(LLVMParser::PointerTypeContext *ctx) {
  auto elementTypeNode = ctx->basicType();
  visitBasicType(elementTypeNode);
  auto elementType = elementTypeNode->typeRef;
  if (elementType == Type::voidType(*llvmContext)) {
    // ERROR
  }
  ctx->typeRef = llvmContext->pointerType(elementType);
  return {};
}
CRef<Value> ModuleBuilder::resolveValueUsage(LLVMParser::ValueContext *ctx) {
  visitValue(ctx);
  auto var = ctx->variable();
  if (ctx->isConstant) {

  } else if (ctx->isGlobal) {
    return module->globalVariable(var->name);
  }

  if (currentFunction->hasArgument(var->name))
    return currentFunction->arg(var->name);
  if (currentAllocatedVars.contains(var->name))
    return currentAllocatedVars[var->name];

}

}