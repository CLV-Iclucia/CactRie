//
// Created by creeper on 10/13/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_ARRAY_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_ARRAY_H

#include <mystl/castings.h>
#include <chiisai-llvm/constant.h>
#include <chiisai-llvm/array-type.h>
namespace llvm {

struct ConstantArray final : Constant {
  ConstantArray(const std::string& name, CRef<Type> type) : Constant(name, type) {
    assert(type->isArray());
  }
  ConstantArray(const std::string &name, CRef<Type> type, std::vector<CRef<Constant>>&& elements_) :
      Constant(name, type),
      elements(std::move(elements_)) {
    assert(type->isArray());
    if (elements.empty()) return ;
    CRef<Type> eleType = elements[0]->type();
    for (const auto &ele : elements)
      if (ele->type() != eleType)
        throw std::runtime_error("Array elements must have the same type");
    assert(dyn_cast_ref<ArrayType>(type)->elementType() == eleType);
  }
  std::vector<CRef<Constant>> elements{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_ARRAY_H
