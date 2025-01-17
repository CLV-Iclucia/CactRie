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

bool isCalleeSavedReg(const std::string &pReg);
bool isCallerSavedReg(const std::string &pReg);
bool isFloatingPointReg(const std::string &pReg);

// for simplicity, we just put each spilled register in a separate stack slot
struct StackFrame {
  StackFrame(const RegAllocResult &regAllocInfo, const FunctionABIInfo &abiInfo,
             const std::set<std::string> &calleeRegsToSave,
             uint32_t maxCallerContextSize, const Function& func)
      : maxCallerContextSize(maxCallerContextSize), regAllocInfo(regAllocInfo),
        spilledOffset(regAllocInfo.spillSlots) {
    for (const auto &reg : calleeRegsToSave)
      allocateCalleeRegSlot(reg, 8);
    for (const auto &[fst, snd] : abiInfo.localIdSizes.at(func.name()))
      allocateLocal(fst, snd);
    for (uint32_t i = 0; i < regAllocInfo.spillSlots; i++)
      allocateSpilledSlot(i);
    size += maxCallerContextSize;
    padToAlign();
    finalizeStackAllocation();
  }
  uint32_t calleeSaveRegOffset(const std::string &pReg) const {
    return offsetOfCalleeSavedRegs.at(pReg);
  }
  uint32_t spilledRegOffset(const std::string &vReg) const {
    return spilledOffset.at(regAllocInfo.spillSlotMap.at(vReg));
  }
  uint32_t size{};
  uint32_t maxCallerContextSize{};
  const RegAllocResult &regAllocInfo;
  std::vector<int32_t> spilledOffset{};
  std::vector<RegisterConfig> regConfigs{};
  std::unordered_map<std::string, int32_t> offsetOfLocals{};
  std::unordered_map<std::string, int32_t> offsetOfCalleeSavedRegs{};

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
  void padToAlign() {
    if (size % 16 != 0)
      size = (size + 15) / 16 * 16;
  }
  void finalizeStackAllocation() {
    for (auto& offset : spilledOffset)
      offset += size;
    for (auto &offset : offsetOfLocals | std::views::values)
      offset += size;
    for (auto &offset : offsetOfCalleeSavedRegs | std::views::values)
      offset += size;
  }

};
} // namespace llvm
#endif // STACK_FRAME_H
