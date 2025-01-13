//
// Created by creeper on 1/11/25.
//
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/integer-type.h>
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
    return 4;
  throw std::runtime_error("unsupported type");
}
}