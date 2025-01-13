//
// Created by creeper on 1/13/25.
//

#ifndef USELESS_ARITH_ELIMINATION_H
#define USELESS_ARITH_ELIMINATION_H

#include <chiisai-llvm/instruction.h>
#include <minilog/logger.h>
namespace llvm {

// mainly handle: mul 0, add 0, sub 0, div 1, rem 1
struct UselessArithEliminationPass {
  explicit UselessArithEliminationPass(const LLVMContext& ctx)
      : logger(minilog::createFileLogger("useless-arith-elimination.log")), ctx(ctx) {}
  void runOnFunction(Function &func);
  std::unique_ptr<minilog::Logger> logger;
  const LLVMContext& ctx;
};

} // namespace llvm
#endif // USELESS_ARITH_ELIMINATION_H
