//
// Created by creeper on 1/5/25.
//

#ifndef LOOP_ANALYSIS_H
#define LOOP_ANALYSIS_H
#include <set>
#include <unordered_set>
#include <chiisai-llvm/basic-block.h>
#include <minilog/logger.h>
namespace llvm {
struct DominatorTree;

// the natural loop of a back edge n->h
// is the set of nodes x that h dominates x, and there is a path from x to n, not passing through h
struct Loop : NonCopyable {

  explicit Loop(CRef<BasicBlock> header) : header(header) {}
  CRef<BasicBlock> header{};
  std::unordered_set<CRef<BasicBlock>> body{};

  void addBlock(CRef<BasicBlock> block) { body.insert(block); }
  [[nodiscard]] bool contains(CRef<BasicBlock> block) const {
    return block == header || body.contains(block);
  }

  [[nodiscard]] bool isNestedWithin(const Loop &other) const {
    if (header != other.header && other.contains(header))
      return true;
    return false;
  }
};

struct LoopAnalysis {
  LoopAnalysis() : logger(minilog::createFileLogger("loop-analysis.log")) {}
  void runOnFunction(const Function &func);
  std::unique_ptr<minilog::Logger> logger{};
  std::vector<Loop> loops{};
  std::unordered_map<CRef<Loop>, std::vector<CRef<Loop>>> loopNestedTree{};
  std::unordered_set<CRef<BasicBlock>> loopHeaders{};
};

} // namespace llvm
#endif // LOOP_ANALYSIS_H
