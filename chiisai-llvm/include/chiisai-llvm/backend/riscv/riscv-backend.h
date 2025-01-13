//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H

#include "pseudo-inst.h"
#include <chiisai-llvm/instructions.h>
#include <chiisai-llvm/module.h>
#include <string>
#include <variant>

namespace llvm {
struct BasicBlock;
struct PhiInst;

struct PseudoInstTranslator {
  PseudoInstTranslator(const LLVMContext &ctx, const Function &func);
  void translateGep(CRef<BasicBlock> bb, CRef<GepInst> gep);
  RiscvPseudoBinary toPseudoBinary(CRef<BinaryInst> inst) const;
  static RiscvPseudoCmp toPseudoCmp(CRef<CmpInst> inst);
  RiscvPseudoInstruction
  toSimplePseudoInstruction(CRef<Instruction> inst) const;
  static RiscvPseudoInstruction toPseudoRet(CRef<RetInst> inst);
  void translateJump(CRef<BasicBlock> bb, CRef<BrInst> br);
  void translateCmp(CRef<BasicBlock> bb, CRef<CmpInst> cmp);

  void
  translateLoad(CRef<BasicBlock> bb, CRef<LoadInst> load);
  void translateStore(CRef<BasicBlock> Bb, CRef<StoreInst> load);
  void translateCall(CRef<BasicBlock> bb, CRef<CallInst> call);
  void translate();
  const Function &func;

  std::unordered_map<CRef<BasicBlock>, std::vector<RiscvPseudoInstruction>>
      pseudoInsts{};
  std::unordered_map<CRef<Type>, InstModifier> typeToModifier{};
};

struct RiscvBackend {
  explicit RiscvBackend(const LLVMContext &ctx) : ctx(ctx) {}
  [[nodiscard]] std::string generateAssembly(const Module &module) const;
  [[nodiscard]] std::string generateAssembly(const Function &function,
                                             bool useFloatingPoint) const;

private:
  const LLVMContext &ctx;
};
} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
