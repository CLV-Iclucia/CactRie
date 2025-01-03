//
// Created by creeper on 1/1/25.
//
#include "chiisai-llvm/passes/dot-cfg-pass.h"

#include <chiisai-llvm/module-builder.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/passes/single-jump-elimination-pass.h>
#include <iostream>
using namespace llvm;

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << std::format(
        "Usage: {} <input-file> <function> <output-file>\n", argv[0]);
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
  SingleJumpEliminationPass().runOnFunction(*function);
  DotCFGPass pass(argv[3]);
  pass.runOnFunction(*function);
  std::cout << "CFG dot file for optimized function " << argv[2] << " saved to "
            << argv[3] << std::endl;
  auto savePNGPath =
      std::format("{}.png", std::filesystem::path(argv[3]).stem().string());
  std::system(std::format("dot -Tpng -o {} {}", savePNGPath, argv[3]).c_str());
  std::cout << "CFG png file for function " << argv[2] << " saved to "
            << savePNGPath << std::endl;
  return 0;
}