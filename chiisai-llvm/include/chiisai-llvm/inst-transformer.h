//
// Created by creeper on 11/7/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INST_EDITOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INST_EDITOR_H
#include <chiisai-llvm/mystl/poly_list.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/instruction.h>
namespace llvm {
struct BasicBlock;
struct Instruction;

using InstPosition = mystl::poly_list<Instruction>::iterator;
struct InstTransformer {
  explicit InstTransformer(BasicBlock &basicBlock) : basicBlock(basicBlock), instructions(basicBlock.instructions) {}
  InstPosition instPos(Instruction& inst) const {
    return instPosMap.at(inst.hash());
  }

private:
  BasicBlock & basicBlock;
  mystl::poly_list<Instruction>& instructions;
  std::unordered_map<uint64_t, InstPosition> instPosMap{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INST_EDITOR_H
