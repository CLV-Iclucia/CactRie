//
// Created by creeper on 1/4/25.
//

#ifndef FUNCTION_GLOBAL_ACCESS_ANALYSIS_H
#define FUNCTION_GLOBAL_ACCESS_ANALYSIS_H

#include <unordered_set>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/global-variable.h>
namespace llvm {

struct GlobalVarAccessInfo {
  CRef<GlobalVariable> globalVar{};
  bool isReadOnly = false;
};

struct FunctionGlobalAccessAnalysis {
  void runOnModule(const Module &module);
  std::unordered_map<CRef<Function>, std::unordered_set<GlobalVarAccessInfo>>
      safeGlobalAccess{};
};

} // namespace llvm
#endif //FUNCTION_GLOBAL_ACCESS_ANALYSIS_H
