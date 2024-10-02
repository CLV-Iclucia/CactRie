//
// Created by creeper on 9/29/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARRAY_TYPE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARRAY_TYPE_H
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/ref.h>
namespace llvm {
struct ArrayType : Type {

  explicit ArrayType(CRef<Type> elementType, size_t size) : Type(TypeEnum::Array, {elementType}), size(size) {}
  size_t size{};
  [[nodiscard]] CRef<Type> elementType() const {
    return containedTypes[0];
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARRAY_TYPE_H
