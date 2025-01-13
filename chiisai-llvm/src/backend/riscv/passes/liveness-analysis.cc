//
// Created by creeper on 1/11/25.
//
#include <chiisai-llvm/backend/riscv/passes/liveness-analysis.h>
#include <chiisai-llvm/backend/riscv/utils.h>
#include <queue>
#include <unordered_set>

namespace llvm {

void LivenessAnalysisPass::recordUseAt(const std::string &reg,
                                       uint32_t instIdx) {
  // if reg is a constant, ignore it
  if (isConstant(reg))
    return;
  if (!livenessInfo.contains(reg))
    livenessInfo[reg] = {instIdx, instIdx + 1};
  livenessInfo[reg].first = std::min(livenessInfo[reg].first, instIdx);
  livenessInfo[reg].second = std::max(livenessInfo[reg].second, instIdx + 1);
}

void LivenessAnalysisPass::runOnInstSequence() {
  std::unordered_map<std::string, uint32_t> firstInstIndexOfLabel{};
  for (auto i = 0; i < pseudoInsts.size(); i++)
    if (isLabel(pseudoInsts[i]))
      firstInstIndexOfLabel[std::get<std::string>(pseudoInsts[i])] = i + 1;
  std::queue<uint32_t> workList{};
  std::unordered_set<uint32_t> inQueue{};

  liveSets.resize(pseudoInsts.size());

  for (auto i = 0; i < pseudoInsts.size(); i++) {
    if (isLabel(pseudoInsts[i]))
      continue;
    if (isJump(pseudoInsts[i])) {
      const auto &[cond, trueLabel] = std::get<RiscvPseudoJump>(pseudoInsts[i]);
      const auto &label = trueLabel;
      instLevelRevCFG[firstInstIndexOfLabel[label]].emplace_back(i);
    }
    if (isRet(pseudoInsts[i])) {
      workList.emplace(i);
      inQueue.emplace(i);
    }
    if (i < pseudoInsts.size() - 1)
      instLevelRevCFG[i + 1].emplace_back(i);
    forDefinedRegs(pseudoInsts[i], [&](const std::string &reg) {
      livenessInfo[reg] = {i, i + 1};
    });
  }

  while (!workList.empty()) {
    auto currIdx = workList.front();
    workList.pop();
    inQueue.erase(currIdx);

    auto &outSet = liveSets[currIdx];
    auto inSet = outSet;
    // in = use + (out - def)
    forDefinedRegs(pseudoInsts[currIdx],
                   [&](const std::string &reg) { inSet.erase(reg); });
    forUsedRegs(pseudoInsts[currIdx],
                [&](const std::string &reg) { inSet.insert(reg); });

    // out = union(in of all successors)
    // in backward CFG: out(pred) += inSet(curr)
    for (auto predIdx : instLevelRevCFG[currIdx]) {
      auto &predOutSet = liveSets[predIdx];
      bool changed = false;
      for (const auto &reg : inSet) {
        if (predOutSet.contains(reg))
          continue;
        changed = true;
        predOutSet.insert(reg);
      }
      if (!changed || inQueue.contains(predIdx))
        continue;
      workList.emplace(predIdx);
      inQueue.emplace(predIdx);
    }
  }

  for (const auto &arg : func.args())
    if (!livenessInfo.contains(arg->name()))
      livenessInfo[arg->name()] = {0, 0};
  for (auto i = 0; i < pseudoInsts.size(); i++) {
    forUsedRegs(pseudoInsts[i],
                [&](const std::string &reg) { recordUseAt(reg, i); });
    for (const auto &reg : liveSets[i])
      recordUseAt(reg, i);
  }
}

} // namespace llvm