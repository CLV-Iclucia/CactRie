//
// Created by creeper on 12/24/24.
//
#include <chiisai-llvm/module-builder.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/passes/dot-cfg-pass.h>
#include <iostream>
using namespace llvm;

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << std::format("Usage: {} <input-file> <function> <output-file>",
                             argv[0])
              << std::endl;
    return 1;
  }
  std::filesystem::path input(argv[1]);
  auto [module, llvmContext] = buildModule(input);
  if (!module->hasFunction(argv[2])) {
    std::cerr << std::format("Function {} not found in module", argv[2])
              << std::endl;
    return 1;
  }
  auto function = module->function(argv[2]);
  DotCFGPass pass(argv[3]);
  pass.runOnFunction(*function);
  std::cout << "CFG dot file for function " << argv[2] << " saved to "
            << argv[3] << std::endl;
  return 0;
}