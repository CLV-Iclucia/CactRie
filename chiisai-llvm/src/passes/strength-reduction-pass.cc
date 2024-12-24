//
// Created by creeper on 12/18/24.
//
#include <fstream>
#include <chiisai-llvm/passes/strength-reduction-pass.h>

namespace llvm {

bool StrengthReductionPass::runOnBasicBlock(BasicBlock &block) {
  for (auto inst : block.instructions) {

  }
}
} // namespace llvm