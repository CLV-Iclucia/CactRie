//
// Created by creeper on 1/12/25.
//

#ifndef ASSEMBLY_GENERATOR_H
#define ASSEMBLY_GENERATOR_H

#include "passes/func-abi-info.h"
#include "pseudo-inst-translator.h"
#include "stack-frame.h"

namespace llvm {

struct RiscvAssemblyCodeGenerator {
  RiscvAssemblyCodeGenerator(
      RegAllocResult regAllocInfo,
      PseudoInstructionSequence pseudoInstSeq,
      std::unordered_map<std::string, RegModifier> vRegModifier,
      const FunctionABIInfo &abiInfo,
      const LivenessAnalysisPass &livenessAnalysisPass)
      : regAllocInfo(std::move(regAllocInfo)),
        vRegModifier(std::move(vRegModifier)),
        pseudoInstSeq(std::move(pseudoInstSeq)),
        abiInfo(abiInfo), livenessAnalysisPass(livenessAnalysisPass) {}

  void prepareArgsForCall(const RiscvPseudoCall &inst) const;
  std::string saveCalleeContext() const;
  std::string restoreCalleeContext() const;
  std::string generate(const Function &func);
  void saveCallerContext(const std::vector<std::string> &callerRegs) const;
  void restoreCallerContext(const std::vector<std::string> &callerRegs) const;
  void finalizeCall(const std::string& func) const;
  void setOnEqualZero(const std::string & dest, const std::string & src, bool isEqz) const;

  RegAllocResult regAllocInfo;
  std::unordered_map<std::string, RegModifier> vRegModifier{};
  PseudoInstructionSequence pseudoInstSeq{};
  std::unique_ptr<StackFrame> stackFrame{};
  const FunctionABIInfo &abiInfo;
  const LivenessAnalysisPass &livenessAnalysisPass;
  mutable std::string assembly{};
  mutable std::set<std::string> modifiedCalleeSavedRegs{};

private:
  void loadFromStack(const std::string &reg, uint32_t offset,
                     RegModifier modifier) const;
  void load(const std::string &dest, const std::string &base, uint32_t offset,
            RegModifier modifier) const;
  void store(const std::string &src, const std::string &base, uint32_t offset,
             RegModifier modifier) const;
  void storeToStack(const std::string &reg, uint32_t offset,
                    RegModifier modifier) const;
  void regMove(const std::string &dest, const std::string &src,
               RegModifier modifier) const;
  void binaryOp(const std::string &result, const std::string &lhs,
                const std::string &rhs, RiscvBinaryOps op, RegModifier modifier) const;
  void comparisonOp(const std::string &result, const std::string &lhs,
                    const std::string &rhs, RegModifier modifier) const;
  void returnFromFunction() const;
  void returnFromFunction(const std::string &vReg) const;
  void loadGlobalAddress(const std::string &dest,
                         const std::string &global) const;
  void branchTo(const std::string &string) const;
  void branchWhenNotZero(const std::string &cond,
                         const std::string &label) const;
  void callFunction(const std::string &Func) const;
  void growStack(uint32_t size) const;
  void shrinkStack(uint32_t size) const;
  bool isSpilled(const std::string &vReg) const {
    if (isConstant(vReg))
      return false;
    return !regAllocInfo.regMap.contains(vReg);
  }
  bool isFloatingPoint(const std::string &vReg) const {
    return vRegModifier.contains(vReg);
  }
  RegModifier getRegModifier(const std::string &vReg) const {
    if (vRegModifier.contains(vReg))
      return vRegModifier.at(vReg);
    return RegModifier::None;
  }
  std::string decideReturnReg(const std::string &vReg) const;
  void loadImmediate(const std::string & pReg, const std::string & imm) const;
  std::string prepareImmediatelyUsableRegs(const std::string &vReg, bool isDest) const;
  std::unordered_map<std::string, std::string>
  prepareImmediatelyUsableRegs(const std::string &vReg,
                               const std::string &vReg2,
                               const std::string &destReg) const;
  std::unordered_map<std::string, std::string> prepareImmediatelyUsableRegs(
      const std::string &vReg, const std::string &vReg2,
      const std::string &vReg3, const std::string &destReg) const;
  std::unordered_map<std::string, std::string>
  prepareImmediatelyUsableRegsForCmp(const std::string &vReg,
                                     const std::string &vReg2,
                                     const std::string &vReg3,
                                     const std::string &destReg) const;
  // finalize, store to stack if spilled, and record use of callee-saved
  // registers
  void finalizeInstruction(
      const std::unordered_map<std::string, std::string> &regs) const;
  void finalizeInstruction(const std::string &vReg,
                           const std::string &pReg) const;
};

} // namespace llvm
#endif // ASSEMBLY_GENERATOR_H
