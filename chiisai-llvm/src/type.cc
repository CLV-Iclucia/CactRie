//
// Created by creeper on 9/23/24.
//
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/llvm-context.h>
namespace llvm {

CRef<Type> Type::voidType(const LLVMContext &ctx) {
  return cref(ctx.voidInstance);
}
CRef<Type> Type::floatType(const LLVMContext &ctx) {
  return cref(ctx.floatInstance);
}
CRef<Type> Type::doubleType(const LLVMContext &ctx) {
  return cref(ctx.doubleInstance);
}
CRef<IntegerType> Type::boolType(const LLVMContext &ctx) {
  return cref(ctx.boolInstance);
}
CRef<IntegerType> Type::intType(const llvm::LLVMContext &ctx) {
  return cref(ctx.intInstance);
}
CRef<IntegerType> Type::longType(const llvm::LLVMContext &ctx) {
  return cref(ctx.longInstance);
}
}