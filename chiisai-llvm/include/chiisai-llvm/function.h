//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#include <string>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/function-type.h>
#include <chiisai-llvm/mystl/poly_vector.h>
namespace llvm {

struct Module;
struct FunctionInfo {
  std::string name;
  CRef<FunctionType> functionType;
  CRef<Module> module;
};

struct BasicBlock;
struct Function : Value {
  explicit Function(const FunctionInfo& info) : m_name(info.name), m_functionType(info.functionType), m_module(info.module) {}
  [[nodiscard]] const std::string &name() const { return m_name; }
  [[nodiscard]] CRef<FunctionType> functionType() const {
    return m_functionType;
  }
  [[nodiscard]] std::span<const std::string> argNames() const {
    return {m_argNames};
  }
  Function& addArgument(const std::string& name, CRef<Type> type) {
    m_argNames.push_back(name);
    m_args.emplace_back<Value>(type);
    m_argMap[name] = m_args.back();
    return *this;
  }
  [[nodiscard]]
  Ref<Value> arg(const std::string& name) {
    return m_argMap[name];
  }
  bool hasArgument(const std::string& name) {
    return m_argMap.contains(name);
  }
  std::list<BasicBlock> basicBlocks{};
  [[nodiscard]] CRef<Module> module() const { return m_module; }
private:
  std::string m_name;
  CRef<FunctionType> m_functionType{};
  std::vector<std::string> m_argNames{};
  mystl::poly_vector<Value> m_args{};
  CRef<Module> m_module{};
  std::unordered_map<std::string, Ref<Value>> m_argMap{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
