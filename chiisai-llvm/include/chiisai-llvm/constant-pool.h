//
// Created by creeper on 10/4/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_POOL_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_POOL_H

#include <concepts>
#include <mystl/poly_vector.h>
#include <mystl/castings.h>
#include <chiisai-llvm/properties.h>
#include <chiisai-llvm/constant.h>

namespace llvm {

struct ConstantPool : RAII {
  Ref<Constant> constant(CRef<Type> type, const std::string& str) {
    if (m_constants.contains({type, str}))
      return mystl::make_observer(m_constants.at({type, str}).get());
    m_constants.insert({std::pair{type, str}, std::make_unique<Constant>(str, type)});
    return mystl::make_observer(m_constants.at({type, str}).get());
  }
private:
  using ConstantKey = std::pair<CRef<Type>, std::string>;
  std::unordered_map<ConstantKey, std::unique_ptr<Constant>> m_constants{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_POOL_H
