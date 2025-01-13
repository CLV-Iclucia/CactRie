//
// Created by creeper on 1/11/25.
//

#ifndef FLOATING_USE_ANALYSIS_H
#define FLOATING_USE_ANALYSIS_H
#include <chiisai-llvm/function.h>
#include <unordered_set>

namespace llvm {
// if a function uses floating point, then the functions that calls it needs to
// save context for floating point registers
struct FloatingUseAnalysis {
  void runOnModule(const Module &module);
  std::unordered_map<CRef<Function>, std::vector<CRef<Function>>> callGraphRev;
  std::unordered_set<CRef<Function>> functionsUsingFloatingPoint;
};

} // namespace llvm
#endif // FLOATING_USE_ANALYSIS_H
