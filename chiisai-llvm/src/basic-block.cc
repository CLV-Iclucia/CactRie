//
// Created by creeper on 10/13/24.
//
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/instruction.h>
namespace llvm {

BasicBlock &
BasicBlock::addInstructionBack(std::unique_ptr<Instruction> &&instruction) {
  auto instRef = makeRef(*instruction);
  m_identifierMap[instruction->name()] = instRef;
  instructions.emplace_back(std::move(instruction));
  instPosMap.insert({instRef, std::prev(instructions.end())});
  return *this;
}

BasicBlock &
BasicBlock::addInstructionFront(std::unique_ptr<Instruction> &&instruction) {
  m_identifierMap[instruction->name()] =
      mystl::make_observer(instruction.get());
  instructions.emplace_front(std::move(instruction));
  instPosMap.insert({firstInstruction(), instructions.begin()});
  return *this;
}

void BasicBlock::accept(Executor &executor) {
  for (auto inst : instructions)
    executor.execute(inst);
}

void BasicBlock::moveInstAfter(CRef<Instruction> inst, CRef<Instruction> pre) {
  auto pos = instPosMap.at(pre);
  auto instPos = instPosMap.at(inst);
  instructions.splice(std::next(pos), instructions, instPos);
}

void BasicBlock::removeInstruction(CRef<Instruction> inst) {
  if (!inst->name().empty())
    m_identifierMap.erase(inst->name());
  auto pos = instPosMap.at(inst);
  instPosMap.erase(inst);
  instructions.erase(pos);
}

Module &BasicBlock::module() { return function().module(); }

const Module &BasicBlock::module() const { return function().module(); }

} // namespace llvm