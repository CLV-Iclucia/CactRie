//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/properties.h>
#include <chiisai-llvm/user.h>
#include <mystl/poly_list.h>
#include <ranges>
namespace llvm {

struct Module;
struct Instruction;
struct Function;
struct InstTransformer;
struct BasicBlock final : Value {
  explicit BasicBlock(const std::string &name, CRef<Type> type)
      : Value(name, type) {
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
  const auto &identifiers() const { return m_identifierMap; }

  BasicBlock &addInstructionBack(std::unique_ptr<Instruction> &&instruction);
  BasicBlock &addInstructionFront(std::unique_ptr<Instruction> &&instruction);

  mystl::poly_list<Instruction> instructions{};
  std::list<Ref<BasicBlock>> predecessors{};
  std::list<Ref<BasicBlock>> successors{};
  void accept(Executor &executor) override;
  void moveInstAfter(CRef<Instruction> inst, CRef<Instruction> pre);
  void removeInstruction(CRef<Instruction> inst);

  ~BasicBlock() override = default;

private:
  using InstPosition = mystl::poly_list<Instruction>::iterator;
  InstPosition instPos(const Instruction &inst) const {
    return instPosMap.at(makeCRef(inst));
  }
  CRef<Instruction> firstInstruction() const { return *instructions.begin(); }
  friend struct Function;
  std::unordered_map<std::string, Ref<Value>> m_identifierMap{};
  std::unordered_map<CRef<Instruction>, InstPosition> instPosMap{};
  Ref<Function> m_function{};
};

} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BASIC_BLOCK_H
