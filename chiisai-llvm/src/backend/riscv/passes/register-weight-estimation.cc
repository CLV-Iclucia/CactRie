//
// Created by creeper on 1/11/25.
//
#include <chiisai-llvm/backend/riscv/passes/register-weight-estimation.h>
#include <chiisai-llvm/backend/riscv/utils.h>
#include <valarray>

namespace llvm {

constexpr double kLoopWeightEstimation = 4000.0;

void RegisterWeightEstimationPass::runOnLoop(const Loop &loop) {
  occurInLoop[loop.header]++;
  for (auto block : loop.body)
    occurInLoop[block]++;
}

void RegisterWeightEstimationPass::runOnFunction(const Function &func) {
  loopAnalysisPass.runOnFunction(func);
  for (const auto &loop : loopAnalysisPass.loops)
    runOnLoop(loop);
  for (auto bb : func.basicBlockRefs()) {
    for (const auto &inst : pseudoInsts.at(bb)) {
      forRegs(inst, [&](const std::string &reg) {
        regWeight[reg] += std::pow(kLoopWeightEstimation, occurInLoop.at(bb));
      });
    }
  }
  for (auto &[reg, weight] : regWeight) {
    auto [l, r] = livenessAnalysisPass.livenessInfo.at(reg);
    weight /= r - l;
  }
}

} // namespace llvm