//
// Created by creeper on 12/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PASSES_MEM2REG_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PASSES_MEM2REG_H
namespace llvm {

struct Function;
struct DominatorTree;
struct PromoteMemToRegPass {
  void runOnFunction(Function &function, DominatorTree& domTree);
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PASSES_MEM2REG_H
