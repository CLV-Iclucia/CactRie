//
// Created by creeper on 12/18/24.
//

#ifndef RISCV_REG_ALLOC_H
#define RISCV_REG_ALLOC_H

#include "passes/register-weight-estimation.h"
#include "pseudo-inst.h"
#include <string>
#include <utility>
namespace llvm {

struct RegisterConfig {
  std::string_view operator()(uint32_t i) const { return regNames[i]; }
  std::string_view operator[](uint32_t i) const { return regNames[i]; }

  std::vector<std::string> regNames{};
  uint32_t maxRegsForArgs{};
  uint32_t numCalleeSavedRegs{};
  uint32_t numCallerSavedRegs{};
  std::vector<std::string> calleeSavedRegs{};
  std::vector<std::string> callerSavedRegs{};
  std::function<bool(std::string_view pReg)> isCalleeSaved{};
  std::function<std::string(uint32_t i)> tmpReg{};
  static RegisterConfig standardConfig();
  static RegisterConfig floatingPointConfig();
};

struct RegAllocResult {
  std::unordered_map<std::string, std::string> regMap{};
  std::unordered_map<std::string, uint32_t> spillSlotMap{};
  uint32_t spillSlots{};
};

struct RiscvRegAllocator {
  explicit RiscvRegAllocator(
      std::vector<RegisterConfig> regConfigs,
      const RegisterWeightEstimationPass &regWeightInfo,
      std::function<uint32_t(const std::string &)> &&dispatcher,
      const Function &func)
      : regWeightInfo(regWeightInfo), dispatcher(std::move(dispatcher)),
        func(func), regConfigs(std::move(regConfigs)) {}

  RegAllocResult allocate();
  [[nodiscard]]
  const RegisterWeightEstimationPass &regWeightInfo;
  std::function<uint32_t(const std::string &)> dispatcher;
  const Function &func;

private:
  std::vector<RegisterConfig> regConfigs{};
};

} // namespace llvm
#endif // RISCV_REG_ALLOC_H
