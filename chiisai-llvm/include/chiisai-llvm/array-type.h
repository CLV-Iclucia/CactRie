//
// Created by creeper on 9/29/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARRAY_TYPE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARRAY_TYPE_H
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/ref.h>
namespace llvm {
struct ArrayType final : Type {
  explicit ArrayType(CRef<Type> elementType, size_t size) : Type(TypeEnum::Array, {elementType}), size(size) {}
  size_t size{};
  [[nodiscard]] CRef<Type> elementType() const {
    return containedTypes[0];
  }
  [[nodiscard]] size_t dim() const {
    return elementType()->isArray() ? 1 + dyn_cast_ref<ArrayType>(elementType())->dim() : 1;
  }

  [[nodiscard]] std::string toString() const override {
    return "[" + std::to_string(size) + " x " + containedTypes[0]->toString() + "]";
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARRAY_TYPE_H
