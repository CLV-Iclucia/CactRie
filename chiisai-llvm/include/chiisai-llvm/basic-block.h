//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#include <chiisai-llvm/value.h>
namespace llvm {

struct Module;
struct Instruction;
struct Function;
struct BasicBlock {
  explicit BasicBlock(std::string name) : m_name(std::move(name)) {}

  template<typename Func> requires std::invocable<Func, Ref<Instruction>>
  void forEachInstruction(Func &&func) const {
    for (auto inst : instructions)
      func(inst);
  }

  template<typename Derived, typename Func> requires std::invocable<Func, Ref<Derived>>
  void forEachInstruction(Func &&func) const {
    for (auto inst : instructions)
      if (auto derived = dynCast<Derived>(inst))
        func(derived);
  }

  [[nodiscard]] const Function& function() const {
    if (m_function == nullptr)
      throw std::runtime_error("accessing null function in basic block");
    return *m_function;
  }

  Function& function() {
    if (m_function == nullptr)
      throw std::runtime_error("accessing null function in basic block");
    return *m_function;
  }

  [[nodiscard]] CRef<Module> module() const;

  [[nodiscard]] const std::string &name() const {
    return m_name;
  }

  [[nodiscard]] Ref<Value> localResult(const std::string& name) {
    return m_localResultMap[name];
  }

  BasicBlock& addInstruction(std::unique_ptr<Instruction>&& instruction);

  mystl::poly_list<Instruction> instructions;
private:
  std::string m_name;
  std::unordered_map<std::string, Ref<Value>> m_localResultMap{};
  Ref<Function> m_function{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
