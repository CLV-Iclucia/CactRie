//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H

#include <string>
#include <variant>
#include "pseudo-inst-translator.h"
#include <chiisai-llvm/module.h>
#include "passes/func-abi-info.h"

namespace llvm {
struct BasicBlock;
struct PhiInst;

struct RiscvBackend {
  explicit RiscvBackend(const LLVMContext &ctx) : ctx(ctx) {}
  [[nodiscard]] std::string generateAssembly(const Module &module) const;
  [[nodiscard]] std::string generateAssembly(const Function &function) const;

private:
  mutable std::unique_ptr<FunctionABIInfo> abiInfo{};
  const LLVMContext &ctx;
};
} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_BACKEND_RISCV_BACKEND_H
