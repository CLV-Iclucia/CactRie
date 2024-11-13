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

struct Module : Executable {
  [[nodiscard]] const std::string &name() const {
    return m_name;
  }
  mystl::manager_vector<GlobalVariable> globalVariables;
  mystl::manager_vector<Function> functions;
  Ref<GlobalVariable> globalVariable(const std::string& name) {
    return m_globalVariableMap.at(name);
  }
  Ref<Function> function(const std::string& name) {
    return m_functionMap.at(name);
  }
  bool hasFunction(const std::string& name) {
    return m_functionMap.contains(name);
  }
  bool hasGlobalVar(const std::string& name) {
    return m_globalVariableMap.contains(name);
  }
  Module& addFunction(std::unique_ptr<Function>&& function);
  void accept(Executor &executor) override;
private:
  std::unordered_map<std::string, Ref<GlobalVariable>> m_globalVariableMap;
  std::unordered_map<std::string, Ref<Function>> m_functionMap;
  std::string m_name;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MODULE_H
