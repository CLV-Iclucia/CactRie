//
// Created by creeper on 10/14/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_IR_BUILDER_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_IR_BUILDER_H
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
namespace llvm {

struct IRBuilder {
  explicit IRBuilder(BasicBlock &basicBlock) : basicBlock(basicBlock) {}

  CRef<AllocaInst> createAllocaInst(const AllocaInstDetails& details) {
    auto &function = basicBlock.function();
    auto allocaInst = std::make_unique<AllocaInst>(basicBlock, details);
    auto instRef = ref(*allocaInst);
    function.addLocalVar(instRef);
    basicBlock.addInstruction(std::move(allocaInst));
    return instRef;
  }

  CRef<BinaryInst> createBinaryInst(uint8_t op, const BinaryInstDetails &details) {
    auto binaryInst = std::make_unique<BinaryInst>(op, basicBlock, details);
    auto instRef = ref(*binaryInst);
    basicBlock.addInstruction(std::move(binaryInst));
    addUse(instRef, instRef->lhs);
    addUse(instRef, instRef->rhs);
    return instRef;
  }

  CRef<PhiInst> createPhiInst(const PhiInstDetails &details) {
    auto phiInst = std::make_unique<PhiInst>(basicBlock, details);
    auto instRef = ref(*phiInst);
    basicBlock.addInstruction(std::move(phiInst));
    for (auto &[bb, value] : details.incomingValues)
      addUse(instRef, value);
    return instRef;
  }

  CRef<CmpInst> createCmpInst(uint8_t op, const CmpInstDetails &details) {
    auto cmpInst = std::make_unique<CmpInst>(op, basicBlock, details);
    auto instRef = ref(*cmpInst);
    basicBlock.addInstruction(std::move(cmpInst));
    addUse(instRef, instRef->lhs);
    addUse(instRef, instRef->rhs);
    return instRef;
  }

  CRef<CallInst> createCallInst(const CallInstDetails &details) {
    auto callInst = std::make_unique<CallInst>(basicBlock, details);
    auto instRef = ref(*callInst);
    basicBlock.addInstruction(std::move(callInst));
    for (const auto &arg : instRef->realArgs)
      addUse(instRef, basicBlock.function().arg(arg));
    return instRef;
  }

  CRef<GepInst> createGepInst(const GepInstDetails &details) {
    auto gepInst = std::make_unique<GepInst>(basicBlock, details);
    auto instRef = ref(*gepInst);
    basicBlock.addInstruction(std::move(gepInst));
    addUse(instRef, instRef->pointer);
    for (auto &index : instRef->indices)
      addUse(instRef, index);
    return instRef;
  }

  CRef<LoadInst> createLoadInst(const MemInstDetails &details) {
    auto loadInst = std::make_unique<LoadInst>(basicBlock, details);
    auto instRef = ref(*loadInst);
    basicBlock.addInstruction(std::move(loadInst));
    addUse(instRef, instRef->pointer);
    return instRef;
  }

  CRef<RetInst> createRetInst(CRef<Value> value) {
    auto retInst = std::make_unique<RetInst>(basicBlock, value);
    auto instRef = ref(*retInst);
    basicBlock.addInstruction(std::move(retInst));
    return instRef;
  }

private:
  BasicBlock &basicBlock;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_IR_BUILDER_H
