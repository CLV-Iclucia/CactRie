//
// Created by creeper on 9/29/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H

#include <string>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/mystl/manager_vector.h>
#include <chiisai-llvm/global-variable.h>
namespace llvm {
struct GlobalVariable;
struct Function;

struct Module {
  [[nodiscard]] const std::string &name() const {
    return m_name;
  }
  mystl::manager_vector<GlobalVariable> globalVariables;
  mystl::manager_vector<Function> functions;
  Ref<GlobalVariable> globalVariable(std::string_view name) {
    return m_globalVariableMap[name];
  }
  Ref<Function> function(std::string_view name) {
    return m_functionMap[name];
  }
  Module& addFunction(std::unique_ptr<Function>&& function);
private:
  std::unordered_map<std::string_view, Ref<GlobalVariable>> m_globalVariableMap;
  std::unordered_map<std::string_view, Ref<Function>> m_functionMap;
  std::string m_name;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H
