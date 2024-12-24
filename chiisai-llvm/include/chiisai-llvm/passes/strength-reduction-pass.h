//
// Created by creeper on 12/17/24.
//

#ifndef STRENGTH_REDUCTION_PASS_H
#define STRENGTH_REDUCTION_PASS_H
#include <chiisai-llvm/basic-block.h>
#include <fstream>
#include <minilog/logger.h>
namespace llvm {
struct StrengthReductionPass {
  explicit StrengthReductionPass(const std::filesystem::path &path)
      : logFile(path), logger(logFile) {
    if (!logFile.is_open())
      throw std::runtime_error("failed to open file");
  }
  bool runOnBasicBlock(BasicBlock &block);
  std::fstream logFile;
  minilog::Logger logger;
};

} // namespace llvm
#endif // STRENGTH_REDUCTION_PASS_H
