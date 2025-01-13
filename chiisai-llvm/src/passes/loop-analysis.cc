//
// Created by creeper on 1/5/25.
//
#include <chiisai-llvm/dominator-tree.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/passes/loop-analysis.h>
#include <iostream>
#include <queue>
namespace llvm {

void LoopAnalysis::runOnFunction(const Function &func) {
  logger->info(
      "<<<<<<<<<<<<<<<<<<<<<< Loop Analysis For {} >>>>>>>>>>>>>>>>>>>>>>",
      func.name());
  loops.clear();
  loopHeaders.clear();
  DominatorTree domTree{};
  domTree.buildFromCFG(func);

  auto isBackEdge = [&](CRef<BasicBlock> from, CRef<BasicBlock> to) {
    return domTree.dominates(to, from);
  };

  std::queue<CRef<BasicBlock>> workList{};
  std::unordered_set<CRef<BasicBlock>> visited{};
  auto findLoopBody = [&](Loop &loop, CRef<BasicBlock> header,
                          CRef<BasicBlock> back) {
    while (!workList.empty())
      workList.pop();
    visited.clear();

    workList.push(back);
    visited.insert(back);
    while (!workList.empty()) {
      auto x = workList.front();
      workList.pop();
      if (domTree.dominates(header, x)) {
        if (!loop.contains(x)) {
          logger->info("block {} is dominated by loop header {}, and can reach "
                       "{}, add to loop body",
                       x->name(), header->name(), back->name());
          loop.addBlock(x);
        }
      }
      for (auto pred : x->predecessors) {
        if (pred == header || visited.contains(pred))
          continue;
        workList.emplace(pred);
        visited.insert(pred);
      }
    }
  };

  for (const auto &bb : func.basicBlocks()) {
    auto block = makeCRef(bb);
    bool isLoopHeader = false;
    logger->info("checking block: {}", block->name());
    for (auto pred : bb.predecessors) {
      if (!isBackEdge(pred, block))
        continue;
      logger->info("found loop header: {}, back edge : {} -> {}", block->name(),
                   pred->name(), block->name());
      isLoopHeader = true;
      break;
    }
    if (!isLoopHeader)
      continue;

    Loop loop{block};
    for (auto pred : bb.predecessors) {
      if (!isBackEdge(pred, block))
        continue;
      findLoopBody(loop, block, pred);
    }
    loops.emplace_back(std::move(loop));
  }

  for (const auto &loop : loops) {
    std::stringstream ss;
    for (const auto &block : loop.body)
      ss << block->name() << " ";
    logger->info("loop header: {}, body: {}", loop.header->name(), ss.str());
  }
  logger->info(
      "<<<<<<<<<<<<<<<<<<<<<< End Loop Analysis For {} >>>>>>>>>>>>>>>>>>>>>>",
      func.name());
  logger->info("");
  logger->outStream().flush();
}
} // namespace llvm