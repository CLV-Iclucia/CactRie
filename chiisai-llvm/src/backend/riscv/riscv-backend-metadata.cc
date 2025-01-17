//
// Created by creeper on 1/11/25.
//
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/type.h>
namespace llvm {
uint32_t sizeOfType(CRef<Type> type) {
  if (type->isInteger())
    return cast<IntegerType>(type)->bitWidth() / 8;
  if (type->isFloatingPoint()) {
    if (type->type == Type::TypeEnum::Float)
      return 4;
    if (type->type == Type::TypeEnum::Double)
      return 8;
    throw std::runtime_error("unsupported floating point type");
  }
  if (type->isPointer())
    return 8;
  if (type->isArray()) {
    auto arrayType = cast<ArrayType>(type);
    return sizeOfType(arrayType->elementType()) * arrayType->size;
  }
  throw std::runtime_error("unsupported type");
}
} // namespace llvm