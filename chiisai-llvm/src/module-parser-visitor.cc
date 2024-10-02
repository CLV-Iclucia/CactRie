//
// Created by creeper on 9/29/24.
//
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/module-parser.h>
#include <chiisai-llvm/mystl/castings.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/pointer-type.h>
namespace llvm {

std::any llvm::ModuleParser::visitModule(LLVMParser::ModuleContext *ctx) {
  llvmContext = std::make_unique<LLVMContext>();

  return {};
}
std::any ModuleParser::visitBasicType(LLVMParser::BasicTypeContext *ctx) {
  auto typeStr = ctx->getText();
  ctx->typeRef = llvmContext->stobt(typeStr);
  return {};
}
std::any ModuleParser::visitArrayType(LLVMParser::ArrayTypeContext *ctx) {
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
std::any ModuleParser::visitPointerType(LLVMParser::PointerTypeContext *ctx) {
  auto elementTypeNode = ctx->basicType();
  visitBasicType(elementTypeNode);
  auto elementType = elementTypeNode->typeRef;
  if (elementType == Type::voidType(*llvmContext)) {
    // ERROR
  }
  ctx->typeRef = llvmContext->pointerType(elementType);
  return {};
}

}