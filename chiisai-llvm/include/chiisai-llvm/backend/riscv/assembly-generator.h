//
// Created by creeper on 1/12/25.
//

#ifndef ASSEMBLY_GENERATOR_H
#define ASSEMBLY_GENERATOR_H

#include "passes/func-abi-info.h"
#include "stack-frame.h"


namespace llvm {

struct RiscvAssemblyCodeGenerator {
  RiscvAssemblyCodeGenerator(
      RegAllocResult regAllocInfo,
      std::unordered_map<std::string, size_t> sizeInBytes,
      std::vector<RiscvPseudoInstruction> pseudoInstSeq,
      std::unordered_map<std::string, CRef<Type>> typeInfo,
      bool useFloating,
      const FunctionABIInfo &abiInfo)
      : regAllocInfo(std::move(regAllocInfo)),
        sizeInBytes(std::move(sizeInBytes)), typeInfo(std::move(typeInfo)),
        pseudoInstSeq(std::move(pseudoInstSeq)),
        stackFrame(this->regAllocInfo, abiInfo, useFloating) {}

  void prepareArgsForCall(const RiscvPseudoCall &inst) const;
  std::string generate(const Function &func) const;


  RegAllocResult regAllocInfo;
  std::unordered_map<std::string, size_t> sizeInBytes{};
  std::unordered_map<std::string, CRef<Type>> typeInfo{};
  std::vector<RiscvPseudoInstruction> pseudoInstSeq{};
  StackFrame stackFrame;
  mutable std::string assembly{};
  mutable std::set<std::string> modifiedCalleeSavedRegs{};

private:
  void loadFromStack(const std::string &reg, int offset) const;
  void storeToStack(const std::string &reg, int offset) const;
  void regMove(const std::string &dest, const std::string &src) const;
  void binaryOp(const std::string &result, const std::string &lhs,
                const std::string &rhs, InstModifier modifier) const;
  void returnFromFunction() const;
  void returnFromFunction(const std::string &vReg) const;
  void loadGlobalAddress(const std::string &dest,
                         const std::string &global) const;
  void branchTo(const std::string &string) const;
  void branchWhenNotZero(const std::string &Cond,
                         const std::string &String) const;
  void callFunction(const std::string & Func) const;
  void growStack(uint32_t size) const;
  void shrinkStack(uint32_t size) const;
  bool isSpilled(const std::string &vReg) const {
    if (isConstant(vReg))
      return false;
    return regAllocInfo.regMap.contains(vReg);
  }
  void saveCallerContext() const { assembly += stackFrame.saveCallerContext(); }
  void restoreCallerContext() const {
    assembly += stackFrame.restoreCallerContext();
  }
  std::string decideReturnReg(const std::string &vReg) const;
  std::string prepareImmediatelyUsableRegs(const std::string &vReg) const;
  std::unordered_map<std::string, std::string>
  prepareImmediatelyUsableRegs(const std::string &vReg,
                               const std::string &vReg2) const;
  std::unordered_map<std::string, std::string>
  prepareImmediatelyUsableRegs(const std::string &vReg,
                               const std::string &vReg2,
                               const std::string &vReg3) const;
  bool isCalleeSaved(const std::string &physReg) const {
    for (const auto &cfg : stackFrame.regConfigs)
      if (cfg.isCalleeSaved(physReg))
        return true;
    return false;
  }
  // finalize, store to stack if spilled, and record use of callee-saved
  // registers
  void finalizeInstruction(
      const std::unordered_map<std::string, std::string> &regs) const;
  void finalizeInstruction(const std::string &vReg,
                           const std::string &pReg) const;
};

} // namespace llvm
#endif // ASSEMBLY_GENERATOR_H
