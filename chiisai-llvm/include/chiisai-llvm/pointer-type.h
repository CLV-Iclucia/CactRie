//
// Created by creeper on 9/29/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_POINTER_TYPE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_POINTER_TYPE_H
#include <chiisai-llvm/type.h>
namespace llvm {
struct PointerType final : Type {
  explicit PointerType(CRef<Type> elementType) : Type(TypeEnum::Pointer, {elementType}) {}
  [[nodiscard]] CRef<Type> elementType() const {
    return containedTypes[0];
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_POINTER_TYPE_H
