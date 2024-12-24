//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/ir-builder.h>
#include <chiisai-llvm/basic-block.h>
namespace llvm {

CRef<PhiInst> IRBuilder::createPhiInst(const PhiInstDetails &details) const {
  auto phiInst = std::make_unique<PhiInst>(basicBlock, details);
  auto instRef = makeRef(*phiInst);
  basicBlock.addInstruction(std::move(phiInst));
  for (auto [bb, value] : details.incomingValues) {
    static_assert(std::is_base_of_v<Value, BasicBlock>);
    static_assert(std::is_convertible_v<BasicBlock*, Value*>);
    addUse(instRef, value);
    addUse(instRef, bb);
  }
  return instRef;
}
CRef<BrInst> IRBuilder::createBrInst(BasicBlock &dest) const {
  auto brInst = std::make_unique<BrInst>(basicBlock, makeRef(dest));
  auto instRef = makeRef(*brInst);
  basicBlock.addInstruction(std::move(brInst));
  addUse(instRef, makeRef(dest));
  return instRef;
}
CRef<BrInst> IRBuilder::createBrInst(const BrInstDetails &cond) const {
  auto brInst = std::make_unique<BrInst>(basicBlock, cond);
  auto instRef = makeRef(*brInst);
  basicBlock.addInstruction(std::move(brInst));
  addUse(instRef, cond.cond);
  addUse(instRef, cond.thenBranch);
  addUse(instRef, cond.elseBranch);
  return instRef;
}
} // namespace llvm