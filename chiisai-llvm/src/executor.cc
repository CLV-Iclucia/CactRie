//
// Created by creeper on 11/16/24.
//
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/constant.h>
#include <chiisai-llvm/constant-scalar.h>
namespace llvm {
llvm::Result &llvm::Executor::reg(CRef<Value> value) {
  if (auto constant = dyn_cast_ref<Constant>(value)) {
    if (auto constantScalar = dyn_cast_ref<ConstantScalar>(constant)) {

    } else
      throw std::runtime_error("constant pointer or array cannot be stored in a register");
  }
  return callFrames.top().regs.at(value->name());
}
}
