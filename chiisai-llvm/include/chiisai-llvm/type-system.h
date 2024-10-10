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
#include <chiisai-llvm/mystl/manager_vector.h>
namespace llvm {
struct Type;
struct TypeSystem : NonMovable {
  TypeSystem() : basicTypeMap({{"void", cref(voidInstance)},
                               {"float", cref(floatInstance)},
                               {"double", cref(doubleInstance)},
                               {"bool", cref(boolInstance)},
                               {"int", cref(intInstance)},
                               {"long", cref(longInstance)}}) {}
private:
  friend struct LLVMContext;
  // String to Basic Type
  CRef<Type> stobt(std::string_view str) {
    return basicTypeMap[str];
  }

  CRef<ArrayType> arrayType(CRef<Type> elementType, size_t size) {
    auto it = arrayTypeMap.find({elementType, size});
    if (it != arrayTypeMap.end())
      return it->second;
    return createArrayType(elementType, size).arrayTypes.back();
  }

  CRef<PointerType> pointerType(CRef<Type> elementType) {
    auto it = pointerTypeMap.find(elementType);
    if (it != pointerTypeMap.end())
      return it->second;
    return createPointerType(elementType).pointerTypes.back();
  }

  Type voidInstance{Type::TypeEnum::Void}, floatInstance{Type::TypeEnum::Float},
      doubleInstance{Type::TypeEnum::Double};

  IntegerType boolInstance{1}, intInstance{32}, longInstance{64};

  mystl::manager_vector<ArrayType> arrayTypes{};

  mystl::manager_vector<PointerType> pointerTypes{};

  std::unordered_map<std::string_view, CRef<Type>> basicTypeMap{};

  using ArrayTypeKey = std::pair<CRef<Type>, size_t>;
  using PointerTypeKey = CRef<Type>;

  std::unordered_map<ArrayTypeKey, CRef<ArrayType>> arrayTypeMap{};

  std::unordered_map<PointerTypeKey, CRef<PointerType>> pointerTypeMap{};

  TypeSystem& createArrayType(CRef<Type> elementType, size_t size) {
    arrayTypes.emplace_back(elementType, size);
    return *this;
  }

  TypeSystem& createPointerType(CRef<Type> elementType) {
    pointerTypes.emplace_back(elementType);
    return *this;
  }

};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_TYPE_SYSTEM_H
