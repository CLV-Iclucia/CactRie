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
#include <chiisai-llvm/constant-scalar.h>
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
  // for constant scalar, str should be the corresponding string of the number
  // for constant array, str should be the name of the array
  // all global array that are marked const should be stored in the constant pool
  [[nodiscard]] Ref<Constant> constant(CRef<Type> type, const std::string& str);
  [[nodiscard]] CRef<PointerType> castFromArrayType(CRef<ArrayType> arrayType) const;
  [[nodiscard]] CRef<ConstantScalar> constantZero(CRef<Type> type) const;
  [[nodiscard]] Scalar evalConstScalar(CRef<ConstantScalar> constScalar) const;
  [[nodiscard]] CRef<Constant> builtinVoidValue() const;
private:
  std::unique_ptr<TypeSystem> typeSystem{};
  std::unique_ptr<ConstantPool> constantPool{};
};

}  // namespace llvm
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LLVM_CONTEXT_H
