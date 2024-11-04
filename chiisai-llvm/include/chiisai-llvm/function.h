//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#include <chiisai-llvm/argument.h>
#include <chiisai-llvm/function-type.h>
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/mystl/poly_vector.h>
#include <chiisai-llvm/mystl/manager_vector.h>
namespace llvm {

struct Module;
struct FunctionInfo {
  std::string name;
  CRef<FunctionType> functionType;
  std::vector<std::string>&& argNames;
  const Module& module;
};

struct BasicBlock;
struct Function : Value {
  explicit Function(const FunctionInfo& info) : Value(info.name, info.functionType), m_module(info.module) {
    for (size_t i = 0; i < info.argNames.size(); ++i)
      addArgument(info.argNames[i], info.functionType->argType(i));
  }
  Function& addArgument(const std::string& name, CRef<Type> type) {
    m_args.emplace_back(name, type);
    m_argMap[name] = m_args.back();
    return *this;
  }
  Function& addLocalVar(Ref<AllocaInst> allocaInst) {
    m_localVars.emplace_back(allocaInst);
    m_localVarMap[allocaInst->name()] = allocaInst;
    return *this;
  }
  Ref<AllocaInst> localVar(const std::string& name) {
    if (m_localVarMap.contains(name))
      return m_localVarMap[name];
    return nullptr;
  }
  [[nodiscard]]
  Ref<Argument> arg(const std::string& name) {
    if (m_argMap.contains(name))
      return m_argMap[name];
    return nullptr;
  }
  const mystl::manager_vector<Argument>& args() const { return m_args; }
  std::list<BasicBlock> basicBlocks{};
  [[nodiscard]] const Module& module() const { return m_module; }
  void accept(Executor& executor) override;
private:
  mystl::manager_vector<Argument> m_args{};
  std::vector<Ref<AllocaInst>> m_localVars{};
  const Module& m_module;
  std::unordered_map<std::string, Ref<Argument>> m_argMap{};
  std::unordered_map<std::string, Ref<AllocaInst>> m_localVarMap{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
