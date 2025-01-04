//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
#include <chiisai-llvm/instructions.h>
#include "pseudo-inst.h"
#include <chiisai-llvm/module.h>
#include <string>

namespace llvm {
struct BasicBlock;
struct PhiInst;
struct RiscvBackend {
  explicit RiscvBackend(const LLVMContext &ctx);
  [[nodiscard]] std::string generateAssembly(const Module &module) const {}
  [[nodiscard]] std::string generateAssembly(const Function& function) const;
  void buildPseudoInstructions(const Module &module);
private:

  RiscvPseudoBinary toPseudoBinary(CRef<BinaryInst> inst) const;

  static RiscvPseudoCmp toPseudoCmp(CRef<CmpInst> inst);

  RiscvPseudoLoad toPseudoLoad(CRef<LoadInst> inst) const;

  PseudoInstruction toSimplePseudoInstruction(CRef<Instruction> inst) const;

  PseudoInstruction toPseudoStore(CRef<StoreInst> inst) const;

  std::unordered_map<CRef<Type>, InstModifier> typeToModifier{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
