//
// Created by creeper on 1/12/25.
//
#include <chiisai-llvm/backend/riscv/assembly-generator.h>
#include <chiisai-llvm/function.h>
#include <gtest/internal/gtest-internal.h>
#include <stack>

namespace llvm {

static RegisterConfig stdCfg = RegisterConfig::standardConfig();
static RegisterConfig fpCfg = RegisterConfig::floatingPointConfig();

void RiscvAssemblyCodeGenerator::growStack(uint32_t size) const {
  if (!size)
    return;
  assembly += "  addi sp, sp, -" + std::to_string(size) + "\n";
}

void RiscvAssemblyCodeGenerator::shrinkStack(uint32_t size) const {
  if (!size)
    return;
  assembly += "  addi sp, sp, " + std::to_string(size) + "\n";
}

std::string
RiscvAssemblyCodeGenerator::decideReturnReg(const std::string &vReg) const {
  if (isConstant(vReg)) {
    if (isConstantInt(vReg))
      return "a0";
    if (isConstantHex(vReg))
      return "fa0";
  }
  if (vRegModifier.contains(vReg))
    return "fa0";
  return "a0";
}

void RiscvAssemblyCodeGenerator::loadImmediate(const std::string &pReg,
                                               const std::string &imm) const {
  if (isFloatingPointReg(pReg))
    assembly += "  lfi " + pReg + ", " + imm + "\n";
  else
    assembly += "  li " + pReg + ", " + imm + "\n";
}

// for immediate values and spilled values, we first need to load them into
// temporary registers
std::string RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegs(
    const std::string &vReg, bool isDest) const {
  std::string tmpReg{};
  if (isFloatingPoint(vReg))
    tmpReg = fpCfg.tmpReg(0);
  else
    tmpReg = stdCfg.tmpReg(0);
  if (isSpilled(vReg)) {
    if (!isDest)
      loadFromStack(tmpReg, stackFrame->spilledRegOffset(vReg),
                    getRegModifier(vReg));
    return tmpReg;
  }
  if (isConstant(vReg))
    return vReg;
  return regAllocInfo.regMap.at(vReg);
}

std::string RiscvAssemblyCodeGenerator::restoreCalleeContext() const {
  std::string code{};
  for (const auto &[pReg, offset] : stackFrame->offsetOfCalleeSavedRegs) {
    if (isFloatingPointReg(pReg))
      code += "  fld " + pReg + ", " + std::to_string(offset) + "(sp)\n";
    else
      code += "  ld " + pReg + ", " + std::to_string(offset) + "(sp)\n";
  }
  return code;
}

std::string RiscvAssemblyCodeGenerator::saveCalleeContext() const {
  std::string code{};
  for (const auto &[pReg, offset] : stackFrame->offsetOfCalleeSavedRegs) {
    if (isFloatingPointReg(pReg))
      code += "  fsd " + pReg + ", " + std::to_string(offset) + "(sp)\n";
    else
      code += "  sd " + pReg + ", " + std::to_string(offset) + "(sp)\n";
  }
  return code;
}

std::unordered_map<std::string, std::string>
RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegs(
    const std::string &vReg, const std::string &vReg2,
    const std::string &destReg) const {
  int idleStdRegIdx = 0;
  int idleFpRegIdx = 0;
  std::unordered_map<std::string, std::string> regs{};
  for (const auto &reg : {vReg, vReg2}) {
    if (isSpilled(reg)) {
      std::string tmpReg{};
      if (isFloatingPoint(reg)) {
        tmpReg = fpCfg.tmpReg(idleFpRegIdx);
        idleFpRegIdx++;
      } else {
        tmpReg = stdCfg.tmpReg(idleStdRegIdx);
        idleStdRegIdx++;
      }
      if (reg != destReg) {
        auto offset = stackFrame->spilledRegOffset(reg);
        loadFromStack(tmpReg, offset, getRegModifier(reg));
      }
      regs[reg] = tmpReg;
    } else {
      if (isConstant(reg))
        regs[reg] = reg;
      else
        regs[reg] = regAllocInfo.regMap.at(reg);
    }
  }
  return regs;
}

std::unordered_map<std::string, std::string>
RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegs(
    const std::string &vReg, const std::string &vReg2, const std::string &vReg3,
    const std::string &destReg) const {
  int idleFpRegIdx = 0;
  int idleStdRegIdx = 0;
  std::unordered_map<std::string, std::string> regs{};
  for (const auto &reg : {vReg, vReg2, vReg3}) {
    if (isSpilled(reg)) {
      std::string tmpReg{};
      if (isFloatingPoint(reg)) {
        tmpReg = fpCfg.tmpReg(idleFpRegIdx);
        idleFpRegIdx++;
      } else {
        tmpReg = stdCfg.tmpReg(idleStdRegIdx);
        idleStdRegIdx++;
      }
      if (reg != destReg) {
        auto offset = stackFrame->spilledRegOffset(reg);
        loadFromStack(tmpReg, offset, getRegModifier(reg));
      }
      regs[reg] = tmpReg;
    } else {
      if (isConstant(reg))
        regs[reg] = reg;
      else regs[reg] = regAllocInfo.regMap.at(reg);
    }
  }
  return regs;
}

// because cmp cannot exchange
std::unordered_map<std::string, std::string>
RiscvAssemblyCodeGenerator::prepareImmediatelyUsableRegsForCmp(
    const std::string &vReg, const std::string &vReg2, const std::string &vReg3,
    const std::string &destReg) const {
  int idleFpRegIdx = 0;
  int idleStdRegIdx = 0;
  std::unordered_map<std::string, std::string> regs{};
  for (const auto &reg : {vReg, vReg2, vReg3}) {
    if (isSpilled(reg) || isConstant(reg)) {
      std::string tmpReg{};
      if (isFloatingPoint(reg) || isConstantHex(reg)) {
        tmpReg = fpCfg.tmpReg(idleFpRegIdx);
        idleFpRegIdx++;
      } else {
        tmpReg = stdCfg.tmpReg(idleStdRegIdx);
        idleStdRegIdx++;
      }
      if (isSpilled(reg) && reg != destReg) {
        auto offset = stackFrame->spilledRegOffset(reg);
        loadFromStack(tmpReg, offset, getRegModifier(reg));
      } else
        loadImmediate(tmpReg, reg);
      regs[reg] = tmpReg;
    } else
      regs[reg] = regAllocInfo.regMap.at(reg);
  }
  return regs;
}

void RiscvAssemblyCodeGenerator::finalizeInstruction(
    const std::unordered_map<std::string, std::string> &regs) const {
  for (const auto &[vReg, physReg] : regs) {
    if (isSpilled(vReg))
      storeToStack(physReg, stackFrame->spilledRegOffset(vReg),
                   getRegModifier(vReg));
  }
}

void RiscvAssemblyCodeGenerator::finalizeInstruction(
    const std::string &vReg, const std::string &pReg) const {
  if (isSpilled(vReg))
    storeToStack(pReg, stackFrame->spilledRegOffset(vReg),
                 getRegModifier(vReg));
}

static std::string loadCode(RegModifier modifier) {
  if (modifier == RegModifier::None)
    return "lw";
  if (modifier == RegModifier::DoubleWord)
    return "ld";
  if (modifier == RegModifier::Float)
    return "flw";
  return "fld";
}

static std::string storeCode(RegModifier modifier) {
  if (modifier == RegModifier::None)
    return "sw";
  if (modifier == RegModifier::DoubleWord)
    return "sd";
  if (modifier == RegModifier::Float)
    return "fsw";
  return "fsd";
}

static std::string moveCode(RegModifier modifier) {
  if (modifier == RegModifier::None)
    return "mv";
  if (modifier == RegModifier::DoubleWord)
    return "mv";
  if (modifier == RegModifier::Float)
    return "fmv.w.x";
  return "fmv.d.x";
}

static std::string binaryCode(RiscvBinaryOps op, RegModifier modifier) {
  static std::unordered_map<RiscvBinaryOps, std::string> opToString = {
      {RiscvBinaryOps::Add, "add"}, {RiscvBinaryOps::Sub, "sub"},
      {RiscvBinaryOps::Mul, "mul"}, {RiscvBinaryOps::Div, "div"},
      {RiscvBinaryOps::Rem, "rem"}, {RiscvBinaryOps::And, "and"},
      {RiscvBinaryOps::Or, "or"},   {RiscvBinaryOps::Xor, "xor"},
      {RiscvBinaryOps::Shl, "sll"}, {RiscvBinaryOps::Shr, "srl"},
  };
  if (modifier != RegModifier::Float && modifier != RegModifier::Double)
    return opToString[op];
  return std::format("f{}{}", opToString[op],
                     modifier == RegModifier::Float ? ".s" : ".d");
}

static std::string cmpCode(RiscvPredicate pred, RegModifier modifier) {
  if (pred == RiscvPredicate::FEQ)
    return std::format("feq{}", modifier == RegModifier::Float ? ".s" : ".d");
  if (pred == RiscvPredicate::LT)
    return "slt";
  if (pred == RiscvPredicate::FLE)
    return std::format("fle{}", modifier == RegModifier::Float ? ".s" : ".d");
  if (pred == RiscvPredicate::FLT)
    return std::format("flt{}", modifier == RegModifier::Float ? ".s" : ".d");

  throw std::runtime_error("unsupported riscv predicate");
}

void RiscvAssemblyCodeGenerator::setOnEqualZero(const std::string &dest,
                                                const std::string &src,
                                                bool isEqz) const {
  if (isEqz)
    assembly += "  seqz " + dest + ", " + src + "\n";
  else
    assembly += "  snez " + dest + ", " + src + "\n";
}

void RiscvAssemblyCodeGenerator::loadFromStack(const std::string &reg,
                                               uint32_t offset,
                                               RegModifier modifier) const {
  assembly += "  " + loadCode(modifier) + " " + reg + ", " +
              std::to_string(offset) + "(sp)\n";
}

void RiscvAssemblyCodeGenerator::load(const std::string &dest,
                                      const std::string &base, uint32_t offset,
                                      RegModifier modifier) const {
  assembly += "  " + loadCode(modifier) + " " + dest + ", " +
              std::to_string(offset) + "(" + base + ")\n";
}

void RiscvAssemblyCodeGenerator::store(const std::string &src,
                                       const std::string &base, uint32_t offset,
                                       RegModifier modifier) const {
  assembly += "  " + storeCode(modifier) + " " + src + ", " +
              std::to_string(offset) + "(" + base + ")\n";
}

void RiscvAssemblyCodeGenerator::storeToStack(const std::string &reg,
                                              uint32_t offset,
                                              RegModifier modifier) const {
  assembly += "  " + storeCode(modifier) + " " + reg + ", " +
              std::to_string(offset) + "(sp)\n";
}

void RiscvAssemblyCodeGenerator::regMove(const std::string &dest,
                                         const std::string &src,
                                         RegModifier modifier) const {
  assembly += "  " + moveCode(modifier) + " " + dest + ", " + src + "\n";
}

void RiscvAssemblyCodeGenerator::binaryOp(const std::string &result,
                                          const std::string &lhs,
                                          const std::string &rhs,
                                          RiscvBinaryOps op,
                                          RegModifier modifier) const {
  if (isConstant(lhs) || isConstant(rhs))
    assembly += std::format("  {}i {}, {}, {}\n", binaryCode(op, modifier),
                            result, lhs, rhs);
  else assembly += std::format("  {} {}, {}, {}\n", binaryCode(op, modifier),
                               result, lhs, rhs);
}

void RiscvAssemblyCodeGenerator::comparisonOp(const std::string &result,
                                              const std::string &lhs,
                                              const std::string &rhs,
                                              RegModifier modifier) const {
  assembly += "  " + cmpCode(RiscvPredicate::LT, modifier) + " " + result +
              ", " + lhs + ", " + rhs + "\n";
}

void RiscvAssemblyCodeGenerator::returnFromFunction() const {
  shrinkStack(stackFrame->size);
  assembly += "  ret\n";
}

void RiscvAssemblyCodeGenerator::returnFromFunction(
    const std::string &vReg) const {
  if (isConstant(vReg)) {
    loadImmediate(decideReturnReg(vReg), vReg);
    returnFromFunction();
    return;
  }
  if (isSpilled(vReg))
    loadFromStack(decideReturnReg(vReg), stackFrame->spilledRegOffset(vReg),
                  getRegModifier(vReg));
  else if (regAllocInfo.regMap.at(vReg) != decideReturnReg(vReg))
    regMove(decideReturnReg(vReg), regAllocInfo.regMap.at(vReg),
            getRegModifier(vReg));
  returnFromFunction();
}

void RiscvAssemblyCodeGenerator::prepareArgsForCall(
    const RiscvPseudoCall &inst) const {
  for (auto i = 0; i < inst.args.size(); i++) {
    auto intArgIdx = abiInfo.getIntArgRegIdx(inst.func, i);
    auto floatArgIdx = abiInfo.getFloatArgRegIdx(inst.func, i);
    std::string argReg{};
    if (intArgIdx)
      argReg = stdCfg.argRegs[*intArgIdx];
    else if (floatArgIdx)
      argReg = fpCfg.argRegs[*floatArgIdx];
    else
      continue;

    if (isSpilled(inst.args[i]))
      loadFromStack(argReg, stackFrame->spilledRegOffset(inst.args[i]),
                    getRegModifier(inst.args[i]));
    else
      regMove(argReg, regAllocInfo.regMap.at(inst.args[i]),
              getRegModifier(inst.args[i]));
  }
  auto stackArgSpaceSize = abiInfo.argsOnStack.at(inst.func).size() * 8;
  auto alignedArgSpaceSize = (stackArgSpaceSize + 15) / 16 * 16;
  growStack(alignedArgSpaceSize);
  for (auto i = 0; i < abiInfo.argsOnStack.at(inst.func).size(); i++) {
    auto argIdx = abiInfo.argsOnStack.at(inst.func)[i];
    if (const auto &arg = inst.args[argIdx]; !isSpilled(arg))
      storeToStack(regAllocInfo.regMap.at(arg), stackArgSpaceSize - 8 - 8 * i,
                   getRegModifier(arg));
    else {
      auto tempReg = isFloatingPoint(arg) ? fpCfg.tmpReg(0) : stdCfg.tmpReg(0);
      loadFromStack(tempReg, stackFrame->spilledRegOffset(arg),
                    getRegModifier(arg));
      storeToStack(tempReg, stackArgSpaceSize - 8 - 8 * i, getRegModifier(arg));
    }
  }
}

void RiscvAssemblyCodeGenerator::loadGlobalAddress(
    const std::string &dest, const std::string &global) const {
  assembly += "  la " + dest + ", " + global + "\n";
}

void RiscvAssemblyCodeGenerator::branchTo(const std::string &string) const {
  assembly += "  j " + string + "\n";
}

void RiscvAssemblyCodeGenerator::branchWhenNotZero(
    const std::string &cond, const std::string &label) const {
  assembly += "  bnez " + cond + ", " + label + "\n";
}

void RiscvAssemblyCodeGenerator::callFunction(const std::string &Func) const {
  assembly += "  call " + Func + "\n";
}

std::string RiscvAssemblyCodeGenerator::generate(const Function &func) {
  assembly.clear();
  assembly += ".globl " + func.name() + "\n";
  assembly += func.name() + ":\n";
  std::set<std::string> calleeRegsToSave{};
  uint32_t maxCallerSavedContextSize = 0;
  for (auto i = 0; i < pseudoInstSeq.insts.size(); i++) {
    forDefinedRegs(pseudoInstSeq.insts[i], [&](const std::string &vReg) {
      if (isSpilled(vReg))
        return;
      if (isCalleeSavedReg(regAllocInfo.regMap.at(vReg)))
        calleeRegsToSave.insert(regAllocInfo.regMap.at(vReg));
    });
    const auto &liveSet = livenessAnalysisPass.liveSets[i];
    if (!isCall(pseudoInstSeq.insts[i]))
      continue;
    uint32_t callerSavedContextSize = 0;
    for (const auto &reg : liveSet) {
      if (isSpilled(reg))
        continue;
      if (!isCallerSavedReg(regAllocInfo.regMap.at(reg)))
        continue;
      callerSavedContextSize += 8;
    }
    maxCallerSavedContextSize =
        std::max(maxCallerSavedContextSize, callerSavedContextSize);
  }

  stackFrame = std::make_unique<StackFrame>(
      regAllocInfo, abiInfo, calleeRegsToSave, maxCallerSavedContextSize, func);
  growStack(stackFrame->size);
  assembly += saveCalleeContext();

  for (auto i = 0; i < abiInfo.numIntArgRegUsed(func.name()); i++) {
    if (const auto &arg = abiInfo.integerArgReg.at(func.name())[i];
        isSpilled(arg)) {
      storeToStack(stdCfg.argRegs[i], stackFrame->spilledRegOffset(arg),
                   getRegModifier(arg));
    } else
      assert(regAllocInfo.regMap.at(arg) == stdCfg.argRegs[i]);
  }

  for (auto i = 0; i < abiInfo.numFloatArgRegUsed(func.name()); i++) {
    if (const auto &arg = abiInfo.floatArgReg.at(func.name())[i];
        isSpilled(arg)) {
      storeToStack(fpCfg.argRegs[i], stackFrame->spilledRegOffset(arg),
                   getRegModifier(arg));
    } else
      assert(regAllocInfo.regMap.at(arg) == fpCfg.argRegs[i]);
  }

  uint32_t stackArgSpaceSize = abiInfo.argsOnStack.size() * 8;
  for (auto i = 0; i < abiInfo.argsOnStack.at(func.name()).size(); i++) {
    const auto &arg =
        func.args()[abiInfo.argsOnStack.at(func.name())[i]]->name();
    if (isSpilled(arg)) {
      auto tempReg = isFloatingPoint(arg) ? fpCfg.tmpReg(0) : stdCfg.tmpReg(0);
      load(tempReg, "sp", stackFrame->size + stackArgSpaceSize - 8 - 8 * i,
           getRegModifier(arg));
      storeToStack(tempReg, stackFrame->spilledRegOffset(arg),
                   getRegModifier(arg));
    } else
      loadFromStack(regAllocInfo.regMap.at(arg),
                    stackFrame->size + stackArgSpaceSize - 8 - 8 * i,
                    getRegModifier(arg));
  }

  auto restoreCalleeContextCode = restoreCalleeContext();
  for (auto i = 0; i < pseudoInstSeq.insts.size(); i++) {
    const auto &instruction = pseudoInstSeq.insts[i];
    if (pseudoInstSeq.labels.contains(i))
      assembly += "." + pseudoInstSeq.labels.at(i) + ":\n";
    std::visit(
        Overload{
            [&](const RiscvPseudoBinary &inst) {
              auto regs = prepareImmediatelyUsableRegs(
                  inst.lhs, inst.rhs, inst.result, inst.result);
              binaryOp(regs.at(inst.result), regs.at(inst.lhs),
                       regs.at(inst.rhs), inst.op, getRegModifier(inst.result));
              finalizeInstruction(inst.result, regs.at(inst.result));
            },
            [&](const RiscvPseudoCmp &inst) {
              auto regs = prepareImmediatelyUsableRegs(inst.lhs, inst.rhs,
                                                       inst.dest, inst.dest);
              comparisonOp(regs.at(inst.dest), regs.at(inst.lhs),
                           regs.at(inst.rhs), getRegModifier(inst.dest));
              finalizeInstruction(inst.dest, regs.at(inst.dest));
            },
            [&](const RiscvPseudoLoad &inst) {
              auto regs =
                  prepareImmediatelyUsableRegs(inst.base, inst.dest, inst.dest);
              load(regs.at(inst.dest), regs.at(inst.base), inst.offset,
                   getRegModifier(inst.dest));
              finalizeInstruction(inst.dest, regs.at(inst.dest));
            },
            [&](const RiscvPseudoStore &inst) {
              auto regs =
                  prepareImmediatelyUsableRegs(inst.base, inst.value, {});
              store(regs.at(inst.value), regs.at(inst.base), inst.offset,
                    getRegModifier(inst.value));
            },
            [&](const RiscvPseudoMove &inst) {
              if (isConstant(inst.src)) {
                auto reg = prepareImmediatelyUsableRegs(inst.dest, true);
                loadImmediate(reg, inst.src);
                finalizeInstruction(inst.dest, reg);
                return;
              }
              auto regs =
                  prepareImmediatelyUsableRegs(inst.src, inst.dest, inst.dest);
              regMove(regs.at(inst.dest), regs.at(inst.src),
                      getRegModifier(inst.dest));
              finalizeInstruction(inst.dest, regs.at(inst.dest));
            },
            [&](const RiscvPseudoRet &inst) {
              if (inst.value.empty()) {
                assembly += restoreCalleeContext();

                returnFromFunction();
              } else {
                assembly += restoreCalleeContext();
                returnFromFunction(inst.value);
              }
            },
            [&](const RiscvPseudoJump &inst) {
              if (inst.cond.empty())
                branchTo(inst.trueLabel);
              else {
                const auto &reg =
                    prepareImmediatelyUsableRegs(inst.cond, false);
                branchWhenNotZero(reg, inst.trueLabel);
              }
            },
            [&](const RiscvPseudoCall &inst) {
              const auto &liveSet = livenessAnalysisPass.liveSets[i];
              std::vector<std::string> callerRegsToSave{};
              for (const auto &reg : liveSet) {
                if (isSpilled(reg))
                  continue;
                if (!isCallerSavedReg(regAllocInfo.regMap.at(reg)))
                  continue;
                callerRegsToSave.emplace_back(regAllocInfo.regMap.at(reg));
              }
              saveCallerContext(callerRegsToSave);
              prepareArgsForCall(inst);
              callFunction(inst.func);
              finalizeCall(inst.func);
              if (!inst.result.empty()) {
                auto retReg = decideReturnReg(inst.result);
                if (isSpilled(inst.result))
                  storeToStack(retReg,
                               stackFrame->spilledRegOffset(inst.result),
                               getRegModifier(inst.result));
                else if (retReg != regAllocInfo.regMap.at(inst.result))
                  regMove(regAllocInfo.regMap.at(inst.result), retReg,
                          getRegModifier(inst.result));
              }
              restoreCallerContext(callerRegsToSave);
            },
            [&](const RiscvLoadGlobal &la) {
              const auto &reg = prepareImmediatelyUsableRegs(la.dest, true);
              loadGlobalAddress(reg, la.global);
              finalizeInstruction(la.dest, reg);
            },
            [&](const RiscvPseudoEqz &inst) {
              auto regs =
                  prepareImmediatelyUsableRegs(inst.src, inst.dest, inst.dest);
              setOnEqualZero(regs.at(inst.dest), regs.at(inst.src), inst.isEqz);
              finalizeInstruction(inst.dest, regs.at(inst.dest));
            },
            [&](const RiscvPseudoAlloca &inst) {
              auto reg = prepareImmediatelyUsableRegs(inst.result, true);
              binaryOp(reg, "sp",
                       std::to_string(stackFrame->offsetOfLocals[inst.result]),
                       RiscvBinaryOps::Add, RegModifier::DoubleWord);
              finalizeInstruction(inst.result, reg);
            },
        },
        instruction);
  }
  assembly += "\n";
  return assembly;
}

void RiscvAssemblyCodeGenerator::saveCallerContext(
    const std::vector<std::string> &callerRegs) const {
  auto offset = 0;
  for (const auto &reg : callerRegs) {
    if (isFloatingPointReg(reg))
      storeToStack(reg, offset, RegModifier::Double);
    else
      storeToStack(reg, offset, RegModifier::DoubleWord);
    offset += 8;
  }
}

void RiscvAssemblyCodeGenerator::restoreCallerContext(
    const std::vector<std::string> &callerRegs) const {
  auto offset = 0;
  for (const auto &reg : callerRegs) {
    if (isFloatingPointReg(reg))
      loadFromStack(reg, offset, RegModifier::Double);
    else
      loadFromStack(reg, offset, RegModifier::DoubleWord);
    offset += 8;
  }
}

void RiscvAssemblyCodeGenerator::finalizeCall(const std::string &func) const {
  auto stackArgSpaceSize = abiInfo.argsOnStack.at(func).size() * 8;
  auto alignedArgSpaceSize = (stackArgSpaceSize + 15) / 16 * 16;
  shrinkStack(alignedArgSpaceSize);
}

} // namespace llvm