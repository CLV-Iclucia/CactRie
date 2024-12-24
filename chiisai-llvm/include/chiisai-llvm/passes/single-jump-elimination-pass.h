//
// Created by creeper on 12/15/24.
//
#ifndef SINGLE_JUMP_ELIMINATION_PASS_H
#define SINGLE_JUMP_ELIMINATION_PASS_H
#include <queue>
#include <ostream>
#include <minilog/logger.h>
#include <chiisai-llvm/function.h>
namespace llvm {

// for those basic blocks with only one unconditional jump, we remove them
struct SingleJumpEliminationPass {
  explicit SingleJumpEliminationPass() : logStream(std::make_unique<std::ofstream>("single-jump-elimination.log")),
                                         logger(*logStream) {}
  void runOnFunction(Function& func) {
    bool isChanged = false;
    std::vector<Ref<BasicBlock>> toBeRemoved{};
    do {
      isChanged = false;
      toBeRemoved.clear();
      for (auto bb : func.basicBlockRefs()) {
        assert(!bb->instructions.empty());
        if (bb->instructions.size() > 1) continue;
        bool canBeEliminated = false;
        Ref<BasicBlock> jumpDest{};
        if (auto onlyInst = makeRef(bb->instructions.front()); isa<BrInst>(onlyInst)) {
          if (auto brInst = cast<BrInst>(onlyInst); !brInst->isConditional()) {
            jumpDest = makeRef(brInst->thenBranch());
            canBeEliminated = true;
          }
        }
        if (!canBeEliminated) continue;
        bb->replaceAllUsesWith(jumpDest);
        toBeRemoved.emplace_back(bb);
        logger.info("SingleJumpEliminationPass: "
                    "basic block {} has been replaced by basic block {}", bb->name(), jumpDest->name());
        isChanged = true;
      }
      for (auto bb : toBeRemoved)
        func.removeBasicBlock(bb);
    } while (isChanged);
  }
  std::unique_ptr<std::ostream> logStream{};
  minilog::Logger logger{};
};
}
#endif //SINGLE_JUMP_ELIMINATION_PASS_H
