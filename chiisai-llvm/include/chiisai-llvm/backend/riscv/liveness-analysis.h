//
// Created by creeper on 12/18/24.
//

#ifndef LIVENESS_ANALYSIS_H
#define LIVENESS_ANALYSIS_H

#include <unordered_map>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/basic-block.h>
#include "pseudo-inst.h"

namespace llvm {
struct LivenessAnalysis {

  const std::unordered_map<CRef<BasicBlock>, std::list<PseudoInstruction>>& pseudoInsts{};
};
}
#endif //LIVENESS_ANALYSIS_H
