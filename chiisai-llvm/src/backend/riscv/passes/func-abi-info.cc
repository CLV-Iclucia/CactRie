//
// Created by creeper on 1/12/25.
//
#include <chiisai-llvm/backend/riscv/passes/func-abi-info.h>
#include <chiisai-llvm/instructions.h>
namespace llvm {

void FunctionABIInfo::runOnFunction(const Function &func) {
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

  const auto &entryBlock = func.basicBlock("entry");
  int32_t stackPointer = 0;
  int32_t totalSize = 0;
  for (auto inst : entryBlock.instructions) {
    if (!isa<AllocaInst>(inst))
      continue;
    auto alloca = cast<AllocaInst>(inst);
    auto size = alloca->size * sizeOfType(alloca->holdType());
    localIdSizes[alloca->name().substr(1)] = size;
    totalSize += size;
  }
  localSize = totalSize;
}
} // namespace llvm