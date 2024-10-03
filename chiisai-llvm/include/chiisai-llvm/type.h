//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_H
#include <vector>
#include <stdexcept>
#include <chiisai-llvm/properties.h>
#include <chiisai-llvm/ref.h>
namespace llvm {

struct LLVMContext;

struct IntegerType;
struct Type : NonMovable {
  enum class TypeEnum {
    Void,
    Integer,
    Float,
    Double,
    Pointer,
    Array,
    Function
  };

  Type() = default;
  explicit Type(TypeEnum type) : type(type) {}

  Type(TypeEnum type, std::vector<CRef<Type>> containedTypes) : type(type), containedTypes(std::move(containedTypes)) {}

  static CRef<Type> voidType(const LLVMContext& ctx);
  static CRef<IntegerType> boolType(const LLVMContext& ctx);
  static CRef<IntegerType> intType(const LLVMContext& ctx);
  static CRef<IntegerType> longType(const LLVMContext& ctx);
  static CRef<Type> floatType(const LLVMContext& ctx);
  static CRef<Type> doubleType(const LLVMContext& ctx);

  [[nodiscard]] bool isArray() const {
    if (type == TypeEnum::Array) {
      [[likely]] if (containedTypes.size() == 1)
        return true;
      throw std::runtime_error("Array type must have exactly one contained type");
    }
    return false;
  }

  [[nodiscard]] bool isPointer() const {
    if (type == TypeEnum::Pointer) {
      [[likely]] if (containedTypes.size() == 1)
        return true;
      throw std::runtime_error("Pointer type must have exactly one contained type");
    }
    return false;
  }

  [[nodiscard]] bool isFunction() const {
    return type == TypeEnum::Function;
  }

  TypeEnum type{TypeEnum::Void};
  std::vector<CRef<Type>> containedTypes{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_H
