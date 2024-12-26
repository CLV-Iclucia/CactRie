//
// Created by creeper on 12/24/24.
//
#include <chiisai-llvm/module-builder.h>

using namespace llvm;

int main() {
  auto [module, llvmContext] = buildModule("test.ll");
}