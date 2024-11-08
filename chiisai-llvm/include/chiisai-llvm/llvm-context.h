//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H

#include <string_view>
#include <memory>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/function-type.h>
#include <chiisai-llvm/constant.h>
namespace llvm {

struct Type;
struct ArrayType;
struct PointerType;
struct TypeSystem;
struct ConstantPool;
struct IntegerType;
uint8_t stoinst(std::string_view str);
class LLVMContext {
public:
  LLVMContext();
  ~LLVMContext();
  // String to Basic Type
  [[nodiscard]] CRef<Type> stobt(const std::string& str) const;
  [[nodiscard]] CRef<ArrayType> arrayType(CRef<Type> elementType, size_t size) const;
  [[nodiscard]] CRef<PointerType> pointerType(CRef<Type> elementType) const;
  [[nodiscard]] CRef<FunctionType> functionType(const std::vector<CRef<Type>>& containedTypes) const;
  [[nodiscard]] CRef<Type> voidType() const;
  [[nodiscard]] CRef<Type> floatType() const;
  [[nodiscard]] CRef<Type> doubleType() const;
  [[nodiscard]] CRef<IntegerType> boolType() const;
  [[nodiscard]] CRef<IntegerType> intType() const;
  [[nodiscard]] CRef<IntegerType> longType() const;
  [[nodiscard]] Ref<Constant> constant(CRef<Type> type, const std::string& str);
private:
  std::unique_ptr<TypeSystem> typeSystem{};
  std::unique_ptr<ConstantPool> constantPool{};
};

}  // namespace llvm
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H
