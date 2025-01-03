//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/ir-builder.h>
namespace llvm {

CRef<PhiInst> IRBuilder::createPhiInst(const PhiInstDetails &details) const {
  auto phiInst = std::make_unique<PhiInst>(basicBlock, details);
  auto instRef = makeRef(*phiInst);
  basicBlock.addInstructionBack(std::move(phiInst));
  return instRef;
}
CRef<BrInst> IRBuilder::createBrInst(BasicBlock &dest) const {
  auto brInst = std::make_unique<BrInst>(basicBlock, makeRef(dest));
  auto instRef = makeRef(*brInst);
  basicBlock.addInstructionBack(std::move(brInst));
  basicBlock.successors.emplace_back(makeRef(dest));
  dest.predecessors.emplace_back(makeRef(basicBlock));
  return instRef;
}
CRef<BrInst> IRBuilder::createBrInst(const BrInstDetails &cond) const {
  auto brInst = std::make_unique<BrInst>(basicBlock, cond);
  auto instRef = makeRef(*brInst);
  basicBlock.addInstructionBack(std::move(brInst));
  basicBlock.successors.emplace_back(cond.thenBranch);
  basicBlock.successors.emplace_back(cond.elseBranch);
  cond.thenBranch->predecessors.emplace_back(makeRef(basicBlock));
  cond.elseBranch->predecessors.emplace_back(makeRef(basicBlock));
  return instRef;
}
} // namespace llvm