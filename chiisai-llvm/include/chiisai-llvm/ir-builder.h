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
  explicit IRBuilder(Ref<BasicBlock> basicBlock) : basicBlock(basicBlock) {}

  CRef<AllocaInst> createAllocaInst(const std::string& name, CRef<Type> type) {
    auto& function = basicBlock->function();
    auto allocaInst = std::make_unique<AllocaInst>(name, type, basicBlock);
    auto instRef = mystl::make_observer(allocaInst.get());
    function.addLocalVar(instRef);
    basicBlock->addInstruction(std::move(allocaInst));
    return instRef;
  }

  CRef<BinaryInst> createBinaryInst(uint8_t op, const BinaryInstDetails& details) {
    auto binaryInst = std::make_unique<BinaryInst>(op, basicBlock, details);
    auto instRef = mystl::make_observer(binaryInst.get());
    basicBlock->addInstruction(std::move(binaryInst));
    addUse(instRef, instRef->lhs);
    addUse(instRef, instRef->rhs);
    return instRef;
  }

  CRef<PhiInst> createPhiInst(const PhiInstDetails& details) {
    auto phiInst = std::make_unique<PhiInst>(basicBlock, details);
    auto instRef = mystl::make_observer(phiInst.get());
    basicBlock->addInstruction(std::move(phiInst));
    for (auto& [bb, value] : details.incomingValues)
      addUse(instRef, value);
    return instRef;
  }

  CRef<CmpInst> createCmpInst(uint8_t op, const CmpInstDetails& details) {
    auto cmpInst = std::make_unique<CmpInst>(op, basicBlock, details);
    auto instRef = mystl::make_observer(cmpInst.get());
    basicBlock->addInstruction(std::move(cmpInst));
    addUse(instRef, instRef->lhs);
    addUse(instRef, instRef->rhs);
    return instRef;
  }

  CRef<CallInst> createCallInst(const CallInstDetails& details) {

  }
private:
  Ref<BasicBlock> basicBlock;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_IR_BUILDER_H
