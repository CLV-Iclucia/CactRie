//
// Created by creeper on 10/13/24.
//
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/basic-block.h>
namespace llvm {

BasicBlock &BasicBlock::addInstruction(std::unique_ptr<Instruction> &&instruction) {
  m_localResultMap[instruction->name()] = mystl::make_observer(instruction.get());
  instructions.emplace_back(std::move(instruction));
  return *this;
}
}