//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/function.h>
namespace llvm {

struct Module;
struct Instruction;
struct BasicBlock : Value {
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

  [[nodiscard]] CRef<Function> function() const {
    return m_function;
  }

  [[nodiscard]] CRef<Module> module() const {
    return function()->module();
  }

  [[nodiscard]] const std::string &name() const {
    return m_name;
  }
  
  [[nodiscard]] Ref<Value> localResult(const std::string& name) {
    return m_localResultMap[name];
  }

  mystl::poly_list<Instruction> instructions;
private:
  std::string m_name;
  std::unordered_map<std::string, Ref<Value>> m_localResultMap{};
  CRef<Function> m_function{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
