//
// Created by creeper on 10/4/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_SYSTEM_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_SYSTEM_H
#include <unordered_map>
#include <string_view>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/function-type.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/properties.h>
#include <mystl/manager_vector.h>
namespace llvm {
struct Type;
struct TypeSystem : RAII {
  TypeSystem() : basicTypeMap({{"void", makeCRef(voidInstance)},
                               {"float", makeCRef(floatInstance)},
                               {"double", makeCRef(doubleInstance)},
                               {"bool", makeCRef(boolInstance)},
                               {"int", makeCRef(intInstance)},
                               {"long", makeCRef(longInstance)}}) {}
private:
  friend struct LLVMContext;
  // String to Basic Type
  CRef<Type> stobt(const std::string &str) {
    return basicTypeMap[str];
  }

  CRef<ArrayType> arrayType(CRef<Type> elementType, size_t size) {
    auto it = arrayTypeMap.find({elementType, size});
    if (it != arrayTypeMap.end())
      return it->second;
    auto ref = createArrayType(elementType, size).arrayTypes.back();
    arrayTypeMap.insert({{elementType, size}, ref});
    return ref;
  }

  CRef<PointerType> pointerType(CRef<Type> elementType) {
    auto it = pointerTypeMap.find(elementType);
    if (it != pointerTypeMap.end())
      return it->second;
    auto ref = createPointerType(elementType).pointerTypes.back();
    pointerTypeMap.insert({elementType, ref});
    return ref;
  }

  CRef<FunctionType> functionType(const std::vector<CRef<Type>> &containedTypes) {
    auto it = functionTypeMap.find(containedTypes);
    if (it != functionTypeMap.end())
      return it->second;
    auto ref = createFunctionType(containedTypes[0], std::span(containedTypes).subspan(1)).functionTypes.back();
    functionTypeMap.insert({containedTypes, ref});
    return ref;
  }



  Type voidInstance{Type::TypeEnum::Void}, floatInstance{Type::TypeEnum::Float},
      doubleInstance{Type::TypeEnum::Double}, labelInstance{Type::TypeEnum::Label};

  IntegerType boolInstance{1}, intInstance{32}, longInstance{64};

  mystl::manager_vector<ArrayType> arrayTypes{};

  mystl::manager_vector<PointerType> pointerTypes{};

  mystl::manager_vector<FunctionType> functionTypes{};

  std::unordered_map<std::string, CRef<Type>> basicTypeMap{};

  using ArrayTypeKey = std::pair<CRef<Type>, size_t>;
  std::unordered_map<ArrayTypeKey, CRef<ArrayType>> arrayTypeMap{};

  using PointerTypeKey = CRef<Type>;
  std::unordered_map<PointerTypeKey, CRef<PointerType>> pointerTypeMap{};

  using FunctionTypeKey = std::vector<CRef<Type>>;
  std::unordered_map<FunctionTypeKey, CRef<FunctionType>> functionTypeMap{};

  TypeSystem &createArrayType(CRef<Type> elementType, size_t size) {
    arrayTypes.emplace_back(elementType, size);
    return *this;
  }

  TypeSystem &createPointerType(CRef<Type> elementType) {
    pointerTypes.emplace_back(elementType);
    return *this;
  }

  TypeSystem &createFunctionType(CRef<Type> returnType, std::span<const CRef<Type>> argTypes) {
    functionTypes.emplace_back(returnType, argTypes);
    return *this;
  }

};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_SYSTEM_H
