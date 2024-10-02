//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/instruction.h>
namespace llvm {

struct BasicBlock : Value {
  explicit BasicBlock(std::string name) : m_name(std::move(name)) {}

  mystl::poly_list<Instruction> instructions;
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
private:
  std::string m_name;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
