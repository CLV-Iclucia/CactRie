//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#include <chiisai-llvm/argument.h>
#include <chiisai-llvm/function-type.h>
#include <chiisai-llvm/instruction.h>
#include <mystl/poly_vector.h>
#include <mystl/manager_vector.h>
namespace llvm {

struct Module;
struct FunctionInfo {
  std::string name;
  CRef<FunctionType> functionType;
  std::vector<std::string>&& argNames;
  const Module& module;
};

struct BasicBlock;
struct Function final : Value {
  explicit Function(const FunctionInfo& info) : Value(info.name, info.functionType), m_module(info.module) {
    for (size_t i = 0; i < info.argNames.size(); ++i)
      addArgument(info.argNames[i], info.functionType->argType(i));
  }
  Function& addArgument(const std::string& name, CRef<Type> type) {
    m_args.emplace_back(name, type);
    m_argMap[name] = m_args.back();
    return *this;
  }
  [[nodiscard]] CRef<Type> returnType() const {
    assert(isa<FunctionType>(type()));
    return cast<FunctionType>(type())->returnValueType();
  }
  [[nodiscard]]
  Argument& arg(const std::string& name) {
    if (m_argMap.contains(name))
      return *m_argMap[name];
    throw std::runtime_error("argument not found");
  }
  [[nodiscard]] bool hasArg(const std::string& name) const {
    return m_argMap.contains(name);
  }
  [[nodiscard]] bool hasBasicBlock(const std::string& name) const {
    return m_basicBlockMap.contains(name);
  }
  [[nodiscard]] bool hasIdentifier(const std::string& name) const {
    return m_idBlockMap.contains(name);
  }

  BasicBlock& basicBlock(const std::string& name) {
    if (m_basicBlockMap.contains(name))
      return *m_basicBlockMap[name];
    throw std::runtime_error("basic block not found");
  }

  [[nodiscard]] Value& identifier(const std::string& name) const;
  [[nodiscard]] const mystl::manager_vector<Argument>& args() const { return m_args; }
  std::list<BasicBlock> basicBlocks{};
  Module& module() {return const_cast<Module&>(m_module);}
  [[nodiscard]] const Module& module() const { return m_module; }
  void accept(Executor& executor) override;

private:
  mystl::manager_vector<Argument> m_args{};
  const Module& m_module;
  std::unordered_map<std::string, Ref<Argument>> m_argMap{};
  std::unordered_map<std::string, Ref<BasicBlock>> m_basicBlockMap{};
  // design tips:
  // first find the basic block where the identifier is defined
  // then forward the query to the block
  // this design makes sure that function doesn't reference the identifiers directly
  // so that we can safely make modifications in basic blocks
  std::unordered_map<std::string, Ref<BasicBlock>> m_idBlockMap{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
