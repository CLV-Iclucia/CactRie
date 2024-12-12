//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/properties.h>
namespace llvm {

struct Module;
struct Instruction;
struct Function;
struct InstTransformer;
struct BasicBlock final : Value {
  explicit BasicBlock(const std::string &name, CRef<Type> type) : Value(name, type) {
    assert(type->type == Type::TypeEnum::Label);
  }

//  template<typename Func> requires std::invocable<Func, Ref<Instruction>>
//  void forEachInstruction(Func &&func) const {
//    for (auto inst : instructions)
//      func(inst);
//  }
//
//  template<typename Derived, typename Func>
//  requires std::invocable<Func, Ref<Derived>> && std::is_base_of_v<Instruction, Derived>
//  void forEachInstruction(Func &&func) const {
//    for (auto inst : instructions)
//      if (auto derived = dynCast<Derived>(inst))
//        func(derived);
//  }

  [[nodiscard]] const Function &function() const {
    if (m_function == nullptr)
      throw std::runtime_error("accessing null function in basic block");
    return *m_function;
  }

  Function &function() {
    if (m_function == nullptr)
      throw std::runtime_error("accessing null function in basic block");
    return *m_function;
  }

  Module &module();

  [[nodiscard]] const Module &module() const;

  [[nodiscard]] Value &identifier(const std::string &name) const {
    if (!m_identifierMap.contains(name))
      throw std::runtime_error("identifier not found");
    return *m_identifierMap.at(name);
  }

  BasicBlock &addInstruction(std::unique_ptr<Instruction> &&instruction);

  mystl::poly_list<Instruction> instructions{};
  void accept(Executor &executor) override;
private:
  std::unordered_map<std::string, Ref<Value>> m_identifierMap{};
  Ref<Function> m_function{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
