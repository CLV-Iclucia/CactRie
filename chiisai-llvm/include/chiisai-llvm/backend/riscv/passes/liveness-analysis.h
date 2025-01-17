//
// Created by creeper on 1/11/25.
//

#ifndef LIVENESS_ANALYSIS_H
#define LIVENESS_ANALYSIS_H

#include <minilog/logger.h>
#include <chiisai-llvm/backend/riscv/pseudo-inst.h>
#include <chiisai-llvm/function.h>
#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>

namespace llvm {
struct LivenessAnalysisPass {
  explicit LivenessAnalysisPass(const PseudoInstructionSequence &pseudoInsts, const Function &func)
      : func(func), pseudoInsts(pseudoInsts), logger(minilog::createFileLogger("liveness-analysis.log")) {}
  void recordUseAt(const std::string& reg, uint32_t instIdx);
  void runOnInstSequence();
  const Function& func;
  const PseudoInstructionSequence& pseudoInsts;
  std::vector<std::vector<uint32_t>> instLevelRevCFG{};
  std::vector<std::set<std::string>> liveSets{};
  std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> livenessInfo{};
  std::unique_ptr<minilog::Logger> logger{};
};

}
#endif //LIVENESS_ANALYSIS_H
