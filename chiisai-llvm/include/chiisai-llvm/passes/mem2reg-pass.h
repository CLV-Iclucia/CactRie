//
// Created by creeper on 12/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PASSES_MEM2REG_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PASSES_MEM2REG_H
#include <chiisai-llvm/instruction.h>
#include <memory>
#include <minilog/logger.h>
#include <ostream>

namespace llvm {
struct Function;
struct DominatorTree;
struct PromoteMemToRegPass {
  explicit PromoteMemToRegPass()
      : logStream(std::make_unique<std::ofstream>("mem2reg.log")),
        logger(*logStream) {}
  void runOnFunction(Function &function);

private:
  bool isPromotable(CRef<AllocaInst> ai);
  void renameAllocaInBlock(
      Ref<BasicBlock> block,
      std::unordered_map<CRef<AllocaInst>, Ref<Value>> &mostRecentValue);
  void fillPhiInst(
      Ref<BasicBlock> current, Ref<BasicBlock> succ,
      const std::unordered_map<std::string, Ref<AllocaInst>> &toBePromote,
      const std::unordered_map<CRef<AllocaInst>, Ref<Value>> &mostRecentValue);
  static std::string nameInsertedPhiInst(CRef<AllocaInst> ai,
                                         CRef<BasicBlock> block) {
    return "__reg_for_" + ai->name() + "_entering_" + block->name();
  }
  static bool isInsertedPhiInstForBlock(CRef<PhiInst> phi,
                                        CRef<BasicBlock> block) {
    return phi->name().starts_with("__reg_for_") &&
           phi->name().ends_with("_entering_" + block->name());
  }
  static std::string extractAllocaNameFromPhiInst(CRef<PhiInst> phi) {
    return phi->name().substr(10, phi->name().find("_entering_") - 10);
  }
  std::unique_ptr<std::ostream> logStream{};
  minilog::Logger logger{};
};
} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PASSES_MEM2REG_H
