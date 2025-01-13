//
// Created by creeper on 1/12/25.
//
#include <chiisai-llvm/backend/riscv/assembly-generator.h>
#include <chiisai-llvm/function.h>

namespace llvm {

void RiscvAssemblyCodeGenerator::growStack(uint32_t size) const {
  assembly += "  addi sp, sp, -" + std::to_string(size) + "\n";
}

void RiscvAssemblyCodeGenerator::shrinkStack(uint32_t size) const {
  assembly += "  addi sp, sp, " + std::to_string(size) + "\n";
}

std::string
RiscvAssemblyCodeGenerator::decideReturnReg(const std::string &vReg) const {
  if (typeInfo.at(vReg)->isFloatingPoint())
    return "fa0";
  return "a0";
}
std::string
RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegs(const std::string &vReg) const {
  if (isSpilled(vReg)) {
    loadFromStack("t0", stackFrame.spilledRegOffset(vReg));
    return "t0";
  }
  return vReg;
}

std::unordered_map<std::string, std::string>
RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegs(
    const std::string &vReg, const std::string &vReg2) const {
  int idleStdRegIdx = 0;
  int idleFpRegIdx = 0;
  std::unordered_map<std::string, std::string> regs{};
  for (const auto &reg : {vReg, vReg2}) {
    if (isSpilled(reg)) {
      auto offset = stackFrame.spilledRegOffset(reg);
      loadFromStack("t" + std::to_string(idleStdRegIdx), offset);
      regs[reg] = "t" + std::to_string(idleStdRegIdx);
    } else
      regs[reg] = regAllocInfo.regMap.at(reg);
    idleStdRegIdx++;
  }
}

std::unordered_map<std::string, std::string>
RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegs(
    const std::string &vReg, const std::string &vReg2,
    const std::string &vReg3) const {
  int idleIdx = 0;
  std::unordered_map<std::string, std::string> regs{};
  for (const auto &reg : {vReg, vReg2, vReg3}) {
    if (isSpilled(reg)) {
      auto offset = stackFrame.spilledRegOffset(reg);
      loadFromStack("t" + std::to_string(idleIdx), offset);
      regs[reg] = "t" + std::to_string(idleIdx);
    } else
      regs[reg] = regAllocInfo.regMap.at(reg);
    idleIdx++;
  }
  return regs;
}

void RiscvAssemblyCodeGenerator::finalizeInstruction(
    const std::unordered_map<std::string, std::string> &regs) const {
  for (const auto &[vReg, physReg] : regs) {
    if (isSpilled(vReg))
      storeToStack(physReg, stackFrame.spilledRegOffset(vReg));
    else if (isCalleeSaved(physReg))
      modifiedCalleeSavedRegs.insert(physReg);
  }
}

void RiscvAssemblyCodeGenerator::finalizeInstruction(const std::string &vReg,
                                            const std::string &pReg) const {
  if (isSpilled(vReg))
    storeToStack(pReg, stackFrame.spilledRegOffset(vReg));
  else if (isCalleeSaved(pReg))
    modifiedCalleeSavedRegs.insert(pReg);
}

void RiscvAssemblyCodeGenerator::loadFromStack(const std::string &reg,
                                                int offset) const {

}

void RiscvAssemblyCodeGenerator::storeToStack(const std::string &reg, int offset) const {
  auto size = sizeInBytes.at(reg);
}

void RiscvAssemblyCodeGenerator::regMove(const std::string &dest,
                                          const std::string &src) const {
  assembly += "  mv " + dest + ", " + src + "\n";
}

void RiscvAssemblyCodeGenerator::binaryOp(const std::string &result,
                                 const std::string &lhs, const std::string &rhs,
                                 InstModifier modifier) const {
  bool useImmediate = false;
  if (isConstant(lhs) || isConstant(rhs))
    useImmediate = true;

}

void RiscvAssemblyCodeGenerator::returnFromFunction() const { assembly += "  ret\n"; }

void RiscvAssemblyCodeGenerator::returnFromFunction(const std::string &vReg) const {
  if (isSpilled(vReg))
    loadFromStack(decideReturnReg(vReg), stackFrame.spilledRegOffset(vReg));
  else if (regAllocInfo.regMap.at(vReg) != decideReturnReg(vReg))
    regMove(decideReturnReg(vReg), regAllocInfo.regMap.at(vReg));
  returnFromFunction();
}

void RiscvAssemblyCodeGenerator::prepareArgsForCall(const RiscvPseudoCall &inst) const {
  std::vector<std::string> args{};
  for (const auto &arg : inst.args) {
    if (isSpilled(arg)) {
      auto offset = stackFrame.spilledRegOffset(arg);
      loadFromStack("t0", offset);
      args.emplace_back("t0");
    } else
      args.emplace_back(arg);
  }
  for (uint32_t i = 0; i < args.size(); i++)
    assembly += "  mv a" + std::to_string(i) + ", " + args.at(i) + "\n";
  assembly += "  call " + inst.func + "\n";
}
std::string RiscvAssemblyCodeGenerator::generate(const Function &func) const {
  assembly.clear();
  assembly += func.name() + ":\n";
  // if there are arguments passed by stack, we need to put them into correct
  // registers or spill slots now we need to record their offset
  std::vector<std::string> passedByStack{};
  growStack(stackFrame.size);
  // if there are arguments spilled to stack, also spill them

  for (auto &instruction : pseudoInstSeq) {
    std::visit(
        Overload{
            [&](const RiscvPseudoBinary &inst) {
              auto regs =
                  prepareImmediatelyUsableRegs(inst.lhs, inst.rhs, inst.result);
              binaryOp(regs.at(inst.result), regs.at(inst.lhs),
                       regs.at(inst.rhs), inst.modifier);
              finalizeInstruction(inst.result, regs.at(inst.result));
            },
            [&](const RiscvPseudoCmp &inst) {
              auto regs =
                  prepareImmediatelyUsableRegs(inst.lhs, inst.rhs, inst.dest);
              binaryOp(regs.at(inst.dest), regs.at(inst.lhs), regs.at(inst.rhs),
                       inst.modifier);
            },
            [&](const RiscvPseudoLoad &inst) {
              auto reg = prepareImmediatelyUsableRegs(inst.base);
            },
            [&](const RiscvPseudoStore &inst) {
              auto regs = prepareImmediatelyUsableRegs(inst.base, inst.value);
            },
            [&](const RiscvPseudoMove &inst) {
              auto regs = prepareImmediatelyUsableRegs(inst.src, inst.dest);
              regMove(regs.at(inst.dest), regs.at(inst.src));
              finalizeInstruction(inst.dest, {});
            },
            [&](const RiscvPseudoRet &inst) {
              if (inst.value.empty())
                returnFromFunction();
              else
                returnFromFunction(inst.value);
            },
            [&](const RiscvPseudoJump &inst) {
              if (inst.cond.empty())
                branchTo(inst.trueLabel);
              else
                branchWhenNotZero(inst.cond, inst.trueLabel);
            },
            [&](const RiscvPseudoCall &inst) {
              saveCallerContext();
              prepareArgsForCall(inst);
              callFunction(inst.func);
              if (!inst.result.empty()) {
                auto retReg = decideReturnReg(inst.result);
                if (isSpilled(inst.result))
                  storeToStack(retReg, stackFrame.spilledRegOffset(inst.result));
                else if (retReg != regAllocInfo.regMap.at(inst.result))
                  regMove(regAllocInfo.regMap.at(inst.result), retReg);
              }
              restoreCallerContext();
            },
            [&](const RiscvLoadGlobal &la) {
              const auto &reg = prepareImmediatelyUsableRegs(la.dest);
              loadGlobalAddress(reg, la.global);
            }, [&](const std::string &str) {},
        },
        instruction);
  }
  auto saveCalleeContextCode = stackFrame.saveCalleeContext(modifiedCalleeSavedRegs);
  auto restoreCalleeContextCode = stackFrame.restoreCalleeContext(modifiedCalleeSavedRegs);
  assembly = saveCalleeContextCode + assembly + restoreCalleeContextCode;
  shrinkStack(stackFrame.size);
  return assembly;
}

void RiscvAssemblyCodeGenerator::loadGlobalAddress(const std::string &dest,
                                          const std::string &global) const {
  assembly += "  la " + dest + ", " + global + "\n";
}

void RiscvAssemblyCodeGenerator::branchTo(const std::string &string) const {
  assembly += "  j " + string + "\n";
}

void RiscvAssemblyCodeGenerator::branchWhenNotZero(
    const std::string &cond, const std::string &string) const {
  const auto &reg = prepareImmediatelyUsableRegs(cond);
  assembly += "  bnez " + reg + ", " + string + "\n";
}
void RiscvAssemblyCodeGenerator::callFunction(const std::string &Func) const {
  assembly += "  call " + Func + "\n";
}

} // namespace llvm