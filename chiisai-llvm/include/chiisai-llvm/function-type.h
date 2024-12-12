//
// Created by creeper on 10/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_TYPE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_TYPE_H
#include <span>
#include <chiisai-llvm/type.h>
namespace llvm {

struct FunctionType final : Type {
  FunctionType(CRef<Type> returnType, std::span<const CRef<Type>> argTypes)
      : Type(TypeEnum::Function) {
    containedTypes.emplace_back(returnType);
    for (const auto& argType : argTypes)
      containedTypes.emplace_back(argType);
  }
  [[nodiscard]] CRef<Type> returnValueType() const { return containedTypes[0]; }
  [[nodiscard]] std::span<const CRef<Type>> argTypes() const { return std::span(containedTypes).subspan<1>(); }
  [[nodiscard]] CRef<Type> argType(size_t index) const { return containedTypes[index + 1]; }
  [[nodiscard]] size_t argCount() const { return containedTypes.size() - 1; }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_TYPE_H
