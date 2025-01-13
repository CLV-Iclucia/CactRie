//
// Created by creeper on 1/11/25.
//
#include <queue>
#include <unordered_set>
#include <chiisai-llvm/instructions.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/passes/floating-use-analysis.h>

namespace llvm {

void FloatingUseAnalysis::runOnModule(const Module &module) {
  std::queue<CRef<Function>> workList{};
  std::unordered_set<CRef<Function>> visited{};
  for (auto func : module.functions) {
    for (auto block : func->basicBlockRefs()) {
      for (auto inst : block->instructions) {
        if (inst->type() && inst->type()->isFloatingPoint()) {
          workList.emplace(func);
          visited.emplace(func);
          functionsUsingFloatingPoint.emplace(func);
        }
        if (!isa<CallInst>(inst))
          continue;
        auto callInst = cast<CallInst>(inst);
        auto callee = callInst->function();
        callGraphRev[callee].emplace_back(func);
      }
    }
  }
  while (!workList.empty()) {
    auto func = workList.front();
    workList.pop();
    for (auto caller : callGraphRev[func]) {
      if (visited.contains(caller))
        continue;
      workList.emplace(caller);
      visited.emplace(caller);
      functionsUsingFloatingPoint.emplace(caller);
    }
  }
}
} // namespace llvm