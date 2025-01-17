//
// Created by creeper on 1/15/25.
//

#ifndef PSEUDO_INST_TRANSLATOR_H
#define PSEUDO_INST_TRANSLATOR_H

#include <map>
#include "pseudo-inst.h"
#include <chiisai-llvm/instructions.h>
#include <minilog/logger.h>
namespace llvm {

enum class RegModifier : uint8_t {
  None,
  DoubleWord,
  Float,
  Double,
};

struct PseudoInstTranslator {
  explicit PseudoInstTranslator(const LLVMContext& ctx, const Function &func) : func(func), logger(minilog::createFileLogger("pseudo-inst-translator.log")), ctx(ctx) {}
  void translate();
  PseudoInstructionSequence pseudoInstSequence() const;
  std::unordered_map<CRef<BasicBlock>, std::vector<RiscvPseudoInstruction>>
      pseudoInsts{};
  std::unordered_map<std::string, RegModifier> vRegModifier{};
  const LLVMContext& ctx;

private:
  void translateGep(CRef<BasicBlock> bb, CRef<GepInst> gep);
  static RiscvPseudoBinary toPseudoBinary(CRef<BinaryInst> inst);
  static RiscvPseudoCmp toPseudoCmp(CRef<CmpInst> inst);
  RiscvPseudoInstruction
  toSimplePseudoInstruction(CRef<Instruction> inst);
  static RiscvPseudoInstruction toPseudoRet(CRef<RetInst> inst);
  void translateJump(CRef<BasicBlock> bb, CRef<BrInst> br);
  void translateCmp(CRef<BasicBlock> bb, CRef<CmpInst> cmp);
  void translateLoad(CRef<BasicBlock> bb, CRef<LoadInst> load);
  void translateStore(CRef<BasicBlock> Bb, CRef<StoreInst> load);
  void translateCall(CRef<BasicBlock> bb, CRef<CallInst> call);

  const Function &func;
  std::unique_ptr<minilog::Logger> logger{};
};

} // namespace llvm
#endif // PSEUDO_INST_TRANSLATOR_H
