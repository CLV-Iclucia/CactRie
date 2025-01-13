//
// Created by creeper on 1/11/25.
//

#ifndef LIVENESS_ANALYSIS_H
#define LIVENESS_ANALYSIS_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <set>
#include <chiisai-llvm/backend/riscv/pseudo-inst.h>
#include <chiisai-llvm/function.h>

namespace llvm {
struct LivenessAnalysisPass {
  explicit LivenessAnalysisPass(const std::vector<RiscvPseudoInstruction> &pseudoInsts, const Function &func)
      : func(func), pseudoInsts(pseudoInsts) {}
  void recordUseAt(const std::string& reg, uint32_t instIdx);
  void runOnInstSequence();
  const Function& func;
  const std::vector<RiscvPseudoInstruction>& pseudoInsts;
  std::vector<std::vector<uint32_t>> instLevelRevCFG{};
  std::vector<std::set<std::string>> liveSets{};
  std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> livenessInfo{};
};

}
#endif //LIVENESS_ANALYSIS_H
