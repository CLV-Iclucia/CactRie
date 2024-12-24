//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
#include <string>
#include <chiisai-llvm/module.h>
#include "pseudo-inst.h"

namespace llvm {
struct RiscvBackend {
  [[nodiscard]] std::string generateAssembly(const Module &module) const {}
  void eliminatePhi(CRef<BasicBlock> block, CRef<PhiInst> phi);
  void buildPseudoInstructions(const Module &module);
  std::unordered_map<CRef<BasicBlock>, std::list<PseudoInstruction>> pseudoInstructions{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
