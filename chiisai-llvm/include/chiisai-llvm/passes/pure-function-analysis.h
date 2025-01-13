//
// Created by creeper on 1/5/25.
//

#ifndef PURE_FUNCTION_ANALYSIS_H
#define PURE_FUNCTION_ANALYSIS_H
#include <chiisai-llvm/function.h>
#include <minilog/logger.h>
namespace llvm {

struct PureFunctionAnalysis {
  PureFunctionAnalysis() : logger(minilog::createFileLogger("pure-function-analysis.log")) {}
  void runOnModule(const Module &func);
  std::unique_ptr<minilog::Logger> logger{};
};

}
#endif //PURE_FUNCTION_ANALYSIS_H
