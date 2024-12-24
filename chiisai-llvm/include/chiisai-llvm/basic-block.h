//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/properties.h>
#include <chiisai-llvm/inst-transformer.h>
namespace llvm {

struct Module;
struct Instruction;
struct Function;
struct BasicBlock final : Value {
  explicit BasicBlock(const std::string &name, CRef<Type> type) : Value(name, type) {
    assert(type->type == Type::TypeEnum::Label);
  }

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
  bool hasIdentifier(const std::string &name) const {
    return m_identifierMap.contains(name);
  }
  const auto& identifiers() const {
    return m_identifierMap;
  }

  BasicBlock &addInstruction(std::unique_ptr<Instruction> &&instruction);

  mystl::poly_list<Instruction> instructions{};
  std::list<Ref<BasicBlock>> predecessors{};
  std::list<Ref<BasicBlock>> successors{};
  void accept(Executor &executor) override;
  void removeInstruction(CRef<Instruction> inst);
  const InstTransformer& instTransformer();

  private:
  friend struct Function;
  std::unordered_map<std::string, Ref<Value>> m_identifierMap{};
  std::unique_ptr<InstTransformer> m_instTransformer{};
  Ref<Function> m_function{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
