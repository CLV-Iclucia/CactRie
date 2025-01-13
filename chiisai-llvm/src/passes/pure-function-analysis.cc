//
// Created by creeper on 1/5/25.
//
#include <chiisai-llvm/passes/pure-function-analysis.h>
#include <chiisai-llvm/module.h>
namespace llvm {

void PureFunctionAnalysis::runOnModule(const Module &module) {
  auto callGraph = module.callGraph();


}

}