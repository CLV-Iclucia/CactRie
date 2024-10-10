//
// Created by creeper on 9/23/24.
//
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/llvm-context.h>
namespace llvm {

CRef<Type> Type::voidType(const LLVMContext &ctx) {
  return ctx.voidType();
}
CRef<Type> Type::floatType(const LLVMContext &ctx) {
  return ctx.floatType();
}
CRef<Type> Type::doubleType(const LLVMContext &ctx) {
  return ctx.doubleType();
}
CRef<IntegerType> Type::boolType(const LLVMContext &ctx) {
  return ctx.boolType();
}
CRef<IntegerType> Type::intType(const llvm::LLVMContext &ctx) {
  return ctx.intType();
}
CRef<IntegerType> Type::longType(const llvm::LLVMContext &ctx) {
  return ctx.longType();
}
}