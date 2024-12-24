//
// Created by creeper on 11/7/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INST_EDITOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INST_EDITOR_H
#include <mystl/poly_list.h>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/instruction.h>
namespace llvm {
struct BasicBlock;
struct Instruction;

using InstPosition = mystl::poly_list<Instruction>::iterator;
struct InstTransformer {
  explicit InstTransformer(BasicBlock &basicBlock);
  InstPosition instPos(const Instruction& inst) const {
    return instPosMap.at(makeCRef(inst));
  }
  void removeInstruction(CRef<Instruction> inst) const;
  CRef<Instruction> firstInstruction() const {
    return *instructions.begin();
  }
  void insertInstructionFront(std::unique_ptr<Instruction> &&inst) const;

private:
  mystl::poly_list<Instruction>& instructions;
  mutable std::unordered_map<CRef<Instruction>, InstPosition> instPosMap{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INST_EDITOR_H
