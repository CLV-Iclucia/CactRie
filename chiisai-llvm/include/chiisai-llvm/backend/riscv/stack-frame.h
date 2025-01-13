//
// Created by creeper on 1/13/25.
//

#ifndef STACK_FRAME_H
#define STACK_FRAME_H
#include <chiisai-llvm/backend/riscv/passes/func-abi-info.h>
#include <chiisai-llvm/backend/riscv/riscv-reg-alloc.h>
#include <string>
#include <unordered_map>

namespace llvm {
// for simplicity, we just put each spilled register in a separate stack slot
struct StackFrame {
  StackFrame(const RegAllocResult &regAllocInfo, const FunctionABIInfo &abiInfo,
             bool useFloating)
      : regAllocInfo(regAllocInfo), spilledOffset(regAllocInfo.spillSlots) {
    auto stdCfg = RegisterConfig::standardConfig();
    auto fpCfg = RegisterConfig::floatingPointConfig();
    for (const auto &calleeSavedReg : stdCfg.calleeSavedRegs)
      allocateCalleeRegSlot(calleeSavedReg, 4);
    if (useFloating)
      for (const auto &calleeSavedReg : fpCfg.calleeSavedRegs)
        allocateCalleeRegSlot(calleeSavedReg, 8);
    for (const auto &[fst, snd] : abiInfo.localIdSizes)
      allocateLocal(fst, snd);
    for (const auto &callerSavedReg : stdCfg.callerSavedRegs)
      allocateCallerRegSlot(callerSavedReg, 4);
    if (useFloating)
      for (const auto &callerSavedReg : fpCfg.callerSavedRegs)
        allocateCallerRegSlot(callerSavedReg, 8);
    padToAlign();
    finalizeStackAllocation();
  }
  uint32_t calleeSaveRegOffset(const std::string &pReg) const {
    return offsetOfCalleeSavedRegs.at(pReg);
  }
  uint32_t spilledRegOffset(const std::string &vReg) const {
    // return spilledOffset.at(regAllocInfo.spillSlots(vReg));
  }
  std::string saveCallerContext() const;
  std::string restoreCallerContext() const;
  std::string saveCalleeContext(const std::set<std::string> &pRegs) const;
  std::string restoreCalleeContext(const std::set<std::string> &pRegs) const;
  uint32_t size{};
  const RegAllocResult &regAllocInfo;
  std::vector<int32_t> spilledOffset{};
  std::vector<RegisterConfig> regConfigs{};
  std::unordered_map<std::string, int32_t> offsetOfLocals{};
  std::unordered_map<std::string, int32_t> offsetOfCalleeSavedRegs{};
  std::unordered_map<std::string, int32_t> offsetOfCallerSavedRegs{};

private:
  mutable int32_t stackPointer{};
  void allocateCalleeRegSlot(const std::string &name, int32_t slotSize) {
    stackPointer -= slotSize;
    offsetOfCalleeSavedRegs[name] = stackPointer;
    size += slotSize;
  }
  void allocateLocal(const std::string &name, int32_t slotSize) {
    stackPointer -= slotSize;
    offsetOfLocals[name] = stackPointer;
    size += slotSize;
  }
  void allocateSpilledSlot(uint32_t index) {
    stackPointer -= 8;
    spilledOffset[index] = stackPointer;
    size += 8;
  }
  void allocateCallerRegSlot(const std::string &name, int32_t slotSize) {
    stackPointer -= slotSize;
    offsetOfCallerSavedRegs[name] = stackPointer;
    size += slotSize;
  }
  void padToAlign() {
    if (size % 16 != 0)
      size = (size + 15) / 16 * 16;
  }
  void finalizeStackAllocation() {
    // add all offsets with size
    for (auto &val : offsetOfLocals | std::views::values)
      val += size;
    for (auto &val : offsetOfCalleeSavedRegs | std::views::values)
      val += size;
    for (auto &val : offsetOfCallerSavedRegs | std::views::values)
      val += size;
    for (auto& offset : spilledOffset)
      offset += size;
  }
};
} // namespace llvm
#endif // STACK_FRAME_H
