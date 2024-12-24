//
// Created by creeper on 12/17/24.
//
#include <unordered_set>
#include <mystl/bit_vector.h>
#include <mystl/zip.h>
#include <chiisai-llvm/passes/mem2reg-pass.h>
#include <chiisai-llvm/dominator-tree.h>
#include <chiisai-llvm/inst-transformer.h>

namespace llvm {
bool PromoteMemToRegPass::isPromotable(CRef<AllocaInst> ai) {
  // no volatile, so we only need to check if ai is only used in load or store
  for (auto user : ai->users()) {
    assert(isa<Instruction>(user));
    if (isa<LoadInst>(user) || isa<StoreInst>(user)) continue;
    logger.info("user {} is not a load or store, {} is not promotable", user->name(), ai->name());
    return false;
  }
  logger.info("alloca inst {} is promotable", ai->name());
  return true;
}

void PromoteMemToRegPass::renameAllocaInBlock(Ref<BasicBlock> block,
                                              std::unordered_map<CRef<AllocaInst>, Ref<Value>>&mostRecentValue) {
  std::vector<Ref<Instruction>> instToRemove{};
  for (auto inst : block->instructions) {
    if (isa<StoreInst>(inst)) {
      auto si = cast<StoreInst>(inst);
      if (!isa<AllocaInst>(si->pointer)) continue;
      auto ai = cast<AllocaInst>(si->pointer);
      if (!mostRecentValue.contains(ai)) continue;
      mostRecentValue[ai] = si->value;
      logger.info("update most recent value for alloca inst {} to {}", ai->name(), si->value->name());
      instToRemove.emplace_back(si);
    }
    if (isa<LoadInst>(inst)) {
      auto li = cast<LoadInst>(inst);
      if (!isa<AllocaInst>(li->pointer)) continue;
      auto ai = cast<AllocaInst>(li->pointer);
      if (!mostRecentValue.contains(ai)) continue;
      logger.info("replace load inst {} with most recent value for alloca inst {}: {}", li->name(), ai->name(), mostRecentValue[ai]->name());
      li->replaceAllUsesWith(mostRecentValue[ai]);
      instToRemove.emplace_back(li);
    }
  }
  for (auto inst : instToRemove)
    block->removeInstruction(inst);
}

void PromoteMemToRegPass::fillPhiInst(
  Ref<BasicBlock> current,
  Ref<BasicBlock> succ,
  const std::unordered_map<std::string, Ref<AllocaInst>>&toBePromote,
  const std::unordered_map<CRef<AllocaInst>, Ref<Value>>&mostRecentValue) {
  logger.info("fill phi inst for block {} from block {}", succ->name(), current->name());
  for (auto inst : succ->instructions) {
    if (!isa<PhiInst>(inst)) break; // phi inst must be at the beginning of the block and continuous
    auto phi = cast<PhiInst>(inst);
    if (!isInsertedPhiInstForBlock(phi, succ)) continue;
    auto ai = toBePromote.at(extractAllocaNameFromPhiInst(phi));
    for (auto&[basicBlock, value] : phi->incomingValues) {
      if (basicBlock->name() != current->name()) continue;
      logger.info("fill phi inst {} with most recent value for alloca inst {}", phi->name(), ai->name());
      value = mostRecentValue.at(ai);
      break;
    }
  }
}
void PromoteMemToRegPass::runOnFunction(Function&function) {
  DominatorTree domTree{};
  domTree.buildFromCFG(function);
  logger.info("<<<<<<<< running mem2reg on function {} >>>>>>>>", function.name());
  auto&entryBlock = function.basicBlock("entry");
  std::unordered_map<CRef<AllocaInst>, Ref<Value>> mostRecentValue{};
  std::unordered_map<std::string, Ref<AllocaInst>> toBePromote{};
  for (auto inst : entryBlock.instructions) {
    if (!isa<AllocaInst>(inst))
      continue;
    auto ai = cast<AllocaInst>(inst);
    assert(ai->type()->isPointer());
    auto holderType = cast<PointerType>(ai->type())->elementType();
    logger.info("--------------mem2reg for alloca inst: {}--------------",
                ai->name());
    if (!isPromotable(ai)) continue;

    if (ai->users().empty()) {
      logger.info("alloca inst {} has no users, remove it", ai->name());
      entryBlock.removeInstruction(ai);
      continue;
    }

    std::unordered_set<Ref<BasicBlock>> useBlock{};
    std::unordered_set<Ref<BasicBlock>> defBlock{};
    for (auto user : ai->users()) {
      auto userInst = cast<Instruction>(user);
      if (isa<LoadInst>(userInst))
        useBlock.insert(makeRef(userInst->basicBlock));
      if (isa<StoreInst>(userInst))
        defBlock.insert(makeRef(userInst->basicBlock));
    }

    auto dominanceLevelGreater = [&domTree](Ref<BasicBlock> a, Ref<BasicBlock> b) {
      return domTree.dominanceLevel(a) > domTree.dominanceLevel(b);
    };

    std::priority_queue<Ref<BasicBlock>, std::vector<Ref<BasicBlock>>, decltype(dominanceLevelGreater)> liveInBlocks(
      dominanceLevelGreater);

    for (auto block : useBlock) {
      if (defBlock.contains(block)) continue;
      liveInBlocks.push(block);
    }

    while (!liveInBlocks.empty()) {
      auto block = liveInBlocks.top();
      liveInBlocks.pop();
      logger.info("processing dominance frontier of live-in block {}", block->name());
      for (auto dfBlock : domTree.dominanceFrontier(block)) {
        const auto&instTransformer = dfBlock->instTransformer();
        std::vector<PhiValue> phiValues(dfBlock->predecessors.size());
        for (auto [pred, phiVal] : zip(dfBlock->predecessors, phiValues)) {
          phiVal.basicBlock = pred;
          phiVal.value = {};
        }
        auto phi = std::make_unique<PhiInst>(*dfBlock,
                                             PhiInstDetails{
                                               nameInsertedPhiInst(ai, dfBlock),
                                               holderType,
                                               std::move(phiValues)
                                             });
        logger.info("insert phi inst {} to block {} with {} phi values",
                    phi->name(),
                    dfBlock->name(),
                    phi->incomingValues.size());
        instTransformer.insertInstructionFront(std::move(phi));
      }
    }
    mostRecentValue.insert({ai, {}});
    toBePromote.insert({ai->name(), ai});
  }

  logger.info("------------------renaming phase start------------------");
  std::queue<Ref<BasicBlock>> workList{};
  std::unordered_set<CRef<BasicBlock>> visited{};
  workList.push(makeRef(entryBlock));
  visited.insert(makeCRef(entryBlock));
  while (!workList.empty()) {
    auto currentBlock = workList.front();
    workList.pop();
    logger.info("###############processing block {}###############", currentBlock->name());
    renameAllocaInBlock(currentBlock, mostRecentValue);
    for (auto succ : currentBlock->successors) {
      fillPhiInst(currentBlock, succ, toBePromote, mostRecentValue);
      if (visited.contains(succ)) continue;
      workList.push(succ);
      visited.insert(succ);
    }
  }
  logger.info("<<<<<<<< mem2reg on function {} finished >>>>>>>>", function.name());
}
}
