//
// Created by creeper on 9/29/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H

#include <string>
#include <chiisai-llvm/mystl/manager_vector.h>
namespace llvm {
struct GlobalVariable;
struct Module {
  [[nodiscard]] const std::string& name() const {
    return m_name;
  }
  mystl::manager_vector<GlobalVariable> globalVariables;
private:
  std::string m_name;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H
