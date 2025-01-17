//
// Created by creeper on 12/26/24.
//

#ifndef FUNC_ABI_INFO_H
#define FUNC_ABI_INFO_H

#include "chiisai-llvm/module.h"

#include <chiisai-llvm/backend/riscv/riscv-backend-metadata.h>
#include <chiisai-llvm/function.h>

namespace llvm {

struct FunctionABIInfo {
  explicit FunctionABIInfo(const Module &module) : module(module) {}
  void runOnFunction(const Function &func);

  uint32_t numIntArgRegUsed(const std::string &func) const {
    const auto &intArgRegs = integerArgReg.at(func);
    return std::count_if(intArgRegs.begin(), intArgRegs.end(),
                         [](const std::string &reg) { return !reg.empty(); });
  }

  uint32_t numFloatArgRegUsed(const std::string &func) const {
    const auto &floatArgRegs = floatArgReg.at(func);
    return std::count_if(floatArgRegs.begin(), floatArgRegs.end(),
                         [](const std::string &reg) { return !reg.empty(); });
  }

  std::optional<uint32_t> getIntArgRegIdx(const std::string &func,
                                          uint32_t argIdx) const {
    const auto &intArgRegs = integerArgReg.at(func);
    auto function = module.function(func);
    const auto &argName = function->args()[argIdx]->name();
    auto it = std::ranges::find(intArgRegs, argName);
    if (it == intArgRegs.end())
      return std::nullopt;
    auto idx = std::distance(intArgRegs.begin(), it);
    if (integerArgReg.at(func)[idx].empty())
      return std::nullopt;
    return idx;
  }

  std::optional<uint32_t> getFloatArgRegIdx(const std::string &func,
                                            uint32_t argIdx) const {
    const auto &floatArgRegs = floatArgReg.at(func);
    auto function = module.function(func);
    const auto &argName = function->args()[argIdx]->name();
    auto it = std::ranges::find(floatArgRegs, argName);

    if (it == floatArgRegs.end())
      return std::nullopt;
    auto idx = std::distance(floatArgRegs.begin(), it);
        if (floatArgReg.at(func)[idx].empty())
          return std::nullopt;
    return idx;
  }

  const Module &module;
  std::unordered_map<std::string,
                     std::array<std::string, kMaximumIntegerArgumentRegisters>>
      integerArgReg;
  std::unordered_map<std::string,
                     std::array<std::string, kMaximumFloatArgumentRegisters>>
      floatArgReg;
  std::unordered_map<std::string, std::vector<uint32_t>> argsInRegs;
  std::unordered_map<std::string, std::vector<uint32_t>> argsOnStack;
  std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>
      localIdSizes{};
  std::unordered_map<std::string, uint32_t> localSize{};
};

} // namespace llvm
#endif // FUNC_ABI_INFO_H
