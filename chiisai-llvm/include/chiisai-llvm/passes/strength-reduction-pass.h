//
// Created by creeper on 12/17/24.
//

#ifndef STRENGTH_REDUCTION_PASS_H
#define STRENGTH_REDUCTION_PASS_H
#include <chiisai-llvm/basic-block.h>
#include <minilog/logger.h>
namespace llvm {
struct StrengthReductionPass {
  explicit StrengthReductionPass(const std::filesystem::path &path) : logger(minilog::createFileLogger(path)) {
  }
  bool runOnBasicBlock(BasicBlock &block);
  std::unique_ptr<minilog::Logger> logger{};
};

} // namespace llvm
#endif // STRENGTH_REDUCTION_PASS_H
