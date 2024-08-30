//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INTEPRETER_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INTEPRETER_H
#include <mini-llvm/llvm-ir.h>
#include <mini-llvm/virtual-memory.h>
namespace llvm {
struct VirtualMachine {
  void runBasicBlock(BasicBlock& basicBlock) {
    for (auto& instruction : basicBlock.instructions()) {

    }
  }
  void runFunction(Function& function) {
    for (auto& block : function.basicBlocks)
      runBasicBlock(block);
  }
  void runModule(Module& module) {
    if (!module.findFunction("main"))
      throw std::runtime_error("main function not found");
    runFunction(module.function("main"));
  }
private:
  std::unique_ptr<VirtualMemory> memory{};
};
}
#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INTEPRETER_H
