//
// Created by creeper on 11/3/24.
//
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/module.h>
namespace llvm {

void BinaryInst::accept(llvm::Executor &executor) {
  executor.reg(name()) = executor.reg(lhs->name()) + executor.reg(rhs->name());
}

void StoreInst::accept(llvm::Executor &executor) {
  executor.reg(name()) = executor.reg(pointer->name());
}

void LoadInst::accept(llvm::Executor &executor) {
  executor.reg(name()) = executor.reg(pointer->name());
}

void CallInst::accept(llvm::Executor &executor) {
  auto func = executor.module.function(function->name());
  executor.pushFrame();
  for (auto arg : func->args()) {

    executor.reg(arg->name()) = executor.reg(arg->name());
  }
  executor.execute(func);
  executor.popFrame();
}
}