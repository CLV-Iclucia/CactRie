//
// Created by creeper on 10/13/24.
//
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/inst-transformer.h>
namespace llvm {

BasicBlock &BasicBlock::addInstruction(std::unique_ptr<Instruction> &&instruction) {
  m_identifierMap[instruction->name()] = mystl::make_observer(instruction.get());
  instructions.emplace_back(std::move(instruction));
  return *this;
}

void BasicBlock::accept(Executor &executor) {
  for (auto inst : instructions)
    executor.execute(inst);
}
void BasicBlock::removeInstruction(CRef<Instruction> inst) {
  if (inst->name() != "")
    m_identifierMap.erase(inst->name());
  instTransformer().removeInstruction(inst);
}
const InstTransformer& BasicBlock::instTransformer() {
  if (!m_instTransformer)
    m_instTransformer = std::make_unique<InstTransformer>(*this);
  return *m_instTransformer;
}

Module &BasicBlock::module() {
  return function().module();
}

const Module &BasicBlock::module() const {
  return function().module();
}
}