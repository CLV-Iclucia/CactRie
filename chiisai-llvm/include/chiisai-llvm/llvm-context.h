//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H

#include <string_view>
#include <memory>
#include <chiisai-llvm/ref.h>
namespace llvm {

class Type;
class ArrayType;
class PointerType;
class LLVMContextImpl;

uint8_t stoinst(std::string_view str);
class LLVMContext {
public:
  LLVMContext();
  ~LLVMContext();
  // String to Basic Type
  [[nodiscard]] CRef<Type> stobt(std::string_view str) const;
  [[nodiscard]] CRef<ArrayType> arrayType(CRef<Type> elementType, size_t size) const;
  [[nodiscard]] CRef<PointerType> pointerType(CRef<Type> elementType) const;
private:
  std::unique_ptr<LLVMContextImpl> impl{};
};

}  // namespace llvm
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H
