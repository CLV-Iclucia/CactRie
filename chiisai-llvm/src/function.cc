//
// Created by creeper on 11/3/24.
//
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/executor.h>

namespace llvm {

void Function::accept(Executor &executor) {
  auto &entry = *impl->m_basicBlocks.front();
  executor.execute(entry);
  while (!executor.returnFlag) {
    const auto& nxt = executor.nxtBasicBlock;
    executor.execute(basicBlock(nxt));
  }
}
void Function::removeBasicBlock(Ref<BasicBlock> bb) {
  assert(impl);
  impl->basicBlockMap.erase(bb->name());
  auto it = impl->basicBlockIterMap[bb];
  impl->basicBlockIterMap.erase(bb);
  impl->m_basicBlocks.erase(it);
}

Value &Function::identifier(const std::string &name) {
  for (const auto &arg : m_args)
    if (arg->name() == name)
      return *arg;
  for (const auto &bb : basicBlocks())
    if (bb.hasIdentifier(name))
      return bb.identifier(name);
  throw std::runtime_error("identifier not found");
}

const Value &Function::identifier(const std::string &name) const {
  for (const auto &arg : m_args)
    if (arg->name() == name)
      return *arg;
  for (const auto &bb : basicBlocks())
    if (bb.hasIdentifier(name))
      return bb.identifier(name);
  throw std::runtime_error("identifier not found");
}
} // namespace llvm