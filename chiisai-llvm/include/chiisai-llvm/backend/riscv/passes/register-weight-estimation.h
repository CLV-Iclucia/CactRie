//
// Created by creeper on 1/11/25.
//

#ifndef REGISTER_WEIGHT_ESTIMATION_H
#define REGISTER_WEIGHT_ESTIMATION_H
#include "liveness-analysis.h"
#include <chiisai-llvm/passes/loop-analysis.h>
#include <string>
#include <unordered_map>
namespace llvm {

struct RegisterWeightEstimationPass {
  explicit RegisterWeightEstimationPass(
      const LivenessAnalysisPass &livenessAnalysisPass,
      LoopAnalysis &loopAnalysisPass,
      const std::unordered_map<CRef<BasicBlock>, std::vector<RiscvPseudoInstruction>>
          &pseudoInsts)
      : livenessAnalysisPass(livenessAnalysisPass),
        loopAnalysisPass(loopAnalysisPass), pseudoInsts(pseudoInsts) {}
  void runOnFunction(const Function &func);
  void runOnLoop(const Loop &loop);
  const LivenessAnalysisPass &livenessAnalysisPass;
  LoopAnalysis &loopAnalysisPass;
  const std::unordered_map<CRef<BasicBlock>, std::vector<RiscvPseudoInstruction>>
      &pseudoInsts{};
  std::unordered_map<std::string, double> regWeight{};
  std::unordered_map<CRef<BasicBlock>, int> occurInLoop{};
};

} // namespace llvm
#endif // REGISTER_WEIGHT_ESTIMATION_H
