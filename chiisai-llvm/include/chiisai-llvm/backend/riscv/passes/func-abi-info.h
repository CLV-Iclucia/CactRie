//
// Created by creeper on 12/26/24.
//

#ifndef FUNC_ABI_INFO_H
#define FUNC_ABI_INFO_H

#include <chiisai-llvm/backend/riscv/riscv-backend-metadata.h>
#include <chiisai-llvm/function.h>

namespace llvm {

struct FunctionABIInfo {

  void runOnFunction(const Function &func) {
    integerArgReg[makeCRef(func)] = {};
    integerArgReg[makeCRef(func)] = {};
    for (auto arg : func.args()) {
      if (arg->type()->isInteger() || arg->type()->isConvertibleToPointer()) {
        if (numIntArgRegUsed(func) < kMaximumIntegerArgumentRegisters)
          integerArgReg[makeCRef(func)][numIntArgRegUsed(func)] = arg->name();
      } else if (arg->type()->isFloatingPoint()) {
        if (numFloatArgRegUsed(func) < kMaximumFloatArgumentRegisters)
          floatArgReg[makeCRef(func)][numFloatArgRegUsed(func)] = arg->name();
      } else
        throw std::runtime_error("unsupported type of argument " + arg->name());
    }

  }

  uint32_t numIntArgRegUsed(const Function &func) const {
    const auto &intArgRegs = integerArgReg.at(makeCRef(func));
    return std::count_if(intArgRegs.begin(), intArgRegs.end(),
                         [](const std::string &reg) { return !reg.empty(); });
  }

  uint32_t numFloatArgRegUsed(const Function &func) const {
    const auto &floatArgRegs = floatArgReg.at(makeCRef(func));
    return std::count_if(floatArgRegs.begin(), floatArgRegs.end(),
                         [](const std::string &reg) { return !reg.empty(); });
  }

  bool isArgumentPassedByReg(const Function &func,
                             const std::string &argName) const {
    if (auto &arg = func.arg(argName);
        arg.type()->isInteger() || arg.type()->isConvertibleToPointer()) {
      return std::ranges::find(integerArgReg.at(makeCRef(func)),
                       argName) != integerArgReg.at(makeCRef(func)).end();
    } else if (arg.type()->isFloatingPoint()) {
      return std::ranges::find(floatArgReg.at(makeCRef(func)),
                       argName) != floatArgReg.at(makeCRef(func)).end();
    }
    throw std::runtime_error("unsupported type of argument " + argName);
  }

  std::unordered_map<CRef<Function>,
                     std::array<std::string, kMaximumIntegerArgumentRegisters>>
      integerArgReg;
  std::unordered_map<CRef<Function>,
                     std::array<std::string, kMaximumFloatArgumentRegisters>>
      floatArgReg;
  std::unordered_map<CRef<Function>,
                    uint32_t> frameSize;
  std::unordered_map<CRef<Function>,
                      uint32_t> offset;
};

} // namespace llvm
#endif // FUNC_ABI_INFO_H
