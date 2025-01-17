//
// Created by creeper on 1/12/25.
//
#include <chiisai-llvm/backend/riscv/passes/func-abi-info.h>
#include <chiisai-llvm/instructions.h>
namespace llvm {

void FunctionABIInfo::runOnFunction(const Function &func) {
  integerArgReg.emplace(
      func.name(), std::array<std::string, kMaximumIntegerArgumentRegisters>{});
  floatArgReg.emplace(
      func.name(), std::array<std::string, kMaximumFloatArgumentRegisters>{});
  argsInRegs.emplace(func.name(), std::vector<uint32_t>{});
  argsOnStack.emplace(func.name(), std::vector<uint32_t>{});
  localSize.emplace(func.name(), 0);
  localIdSizes.emplace(func.name(), std::unordered_map<std::string, int32_t>{});
  for (auto i = 0; i < func.args().size(); i++) {
    if (auto arg = func.args()[i];
        arg->type()->isInteger() || arg->type()->isConvertibleToPointer()) {
      if (numIntArgRegUsed(func.name()) < kMaximumIntegerArgumentRegisters) {
        integerArgReg[func.name()][numIntArgRegUsed(func.name())] = arg->name();
        argsInRegs[func.name()].emplace_back(i);
      } else
        argsOnStack[func.name()].emplace_back(i);
    } else if (arg->type()->isFloatingPoint()) {
      if (numFloatArgRegUsed(func.name()) < kMaximumFloatArgumentRegisters) {
        floatArgReg[func.name()][numFloatArgRegUsed(func.name())] = arg->name();
        argsInRegs[func.name()].emplace_back(i);
      } else
        argsOnStack[func.name()].emplace_back(i);
    } else
      throw std::runtime_error("unsupported type of argument " + arg->name());
  }

  if (!func.isImplemented()) return ;
  const auto &entryBlock = func.basicBlock("entry");
  int32_t totalSize = 0;
  for (auto inst : entryBlock.instructions) {
    if (!isa<AllocaInst>(inst))
      continue;
    auto alloca = cast<AllocaInst>(inst);
    auto size = alloca->size * sizeOfType(alloca->holdType());
    localIdSizes[func.name()][alloca->name()] = size;
    totalSize += size;
  }
  localSize[func.name()] = totalSize;
}
} // namespace llvm