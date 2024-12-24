//
// Created by creeper on 12/24/24.
//
#include <chiisai-llvm/inst-transformer.h>
#include <chiisai-llvm/basic-block.h>
namespace llvm {

InstTransformer::InstTransformer(BasicBlock &basicBlock)
    : instructions(basicBlock.instructions) {}
void InstTransformer::removeInstruction(CRef<Instruction> inst) const {
  auto pos = instPosMap.at(inst);
  instPosMap.erase(inst);
  instructions.erase(pos);
}
void InstTransformer::insertInstructionFront(
    std::unique_ptr<Instruction> &&inst) const {
  instructions.emplace_front(std::move(inst));
  instPosMap.insert({firstInstruction(), instructions.begin()});
}
} // namespace llvm