//
// Created by creeper on 9/23/24.
//
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/array-type.h>
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
CRef<Type> Type::labelType(const LLVMContext &ctx) {
  return ctx.labelType();
}
std::string Type::toString() const {
  switch (type) {
  case TypeEnum::Void:return "void";
  case TypeEnum::Integer:return "i32";
  case TypeEnum::Float:return "float";
  case TypeEnum::Double:return "double";
  case TypeEnum::Pointer:return containedTypes[0]->toString() + "*";
  case TypeEnum::Array: {
    auto arrayType = cast<ArrayType>(makeCRef(*this));
    return containedTypes[0]->toString() + "[" + std::to_string(arrayType->dim()) + "]";
  }
  case TypeEnum::Label:return "label";
  case TypeEnum::Function:return "function";
  }
  return "unknown";
}
}