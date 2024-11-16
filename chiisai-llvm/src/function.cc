//
// Created by creeper on 11/3/24.
//
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/executor.h>

namespace llvm {

void Function::accept(Executor &executor) {
  auto &entry = basicBlocks.front();
  executor.execute(entry);
  while (!executor.returnFlag) {
    const auto& nxt = executor.nxtBasicBlock;
    executor.execute(basicBlock(nxt));
  }
}
Value& Function::identifier(const std::string &name) const {
  if (!m_idBlockMap.contains(name))
    throw std::runtime_error("identifier not found");
  auto block = m_idBlockMap.at(name);
  return block->identifier(name);
}
}