//
// Created by creeper on 10/4/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_POOL_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_POOL_H

#include <chiisai-llvm/constant-array.h>
#include <chiisai-llvm/constant.h>
#include <chiisai-llvm/properties.h>
#include <concepts>
#include <mystl/castings.h>
#include <mystl/poly_vector.h>
namespace llvm {

struct ConstantPool : RAII {
  Ref<Constant> constant(CRef<Type> type, const std::string &str) {
    if (m_constants.contains({type, str}))
      return mystl::make_observer(m_constants.at({type, str}).get());
    m_constants.insert(
        {std::pair{type, str}, std::make_unique<Constant>(str, type)});
    return mystl::make_observer(m_constants.at({type, str}).get());
  }
  Ref<Constant> createConstantArray(const std::string &name,
                                    CRef<ArrayType> arrayType,
                                    std::vector<CRef<Constant>> &&constants) {
    m_constants.insert({std::pair{arrayType, name},
                        std::make_unique<ConstantArray>(name, arrayType,
                                                        std::move(constants))});
    return mystl::make_observer(m_constants.at({arrayType, name}).get());
  }

private:
  using ConstantKey = std::pair<CRef<Type>, std::string>;
  std::unordered_map<ConstantKey, std::unique_ptr<Constant>> m_constants{};
};

} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_POOL_H
