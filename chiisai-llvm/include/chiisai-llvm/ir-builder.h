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

  [[nodiscard]] CRef<AllocaInst> createAllocaInst(const AllocaInstDetails& details) const {
    auto allocaInst = std::make_unique<AllocaInst>(basicBlock, details);
    auto instRef = makeRef(*allocaInst);
    basicBlock.addInstructionBack(std::move(allocaInst));
    return instRef;
  }

  [[nodiscard]] CRef<BinaryInst> createBinaryInst(uint8_t op, const BinaryInstDetails &details) const {
    auto binaryInst = std::make_unique<BinaryInst>(op, basicBlock, details);
    auto instRef = makeRef(*binaryInst);
    basicBlock.addInstructionBack(std::move(binaryInst));
    addUse(instRef, instRef->lhs);
    addUse(instRef, instRef->rhs);
    return instRef;
  }

  [[nodiscard]] CRef<PhiInst>
  createPhiInst(const PhiInstDetails &details) const;

  [[nodiscard]] CRef<CmpInst> createCmpInst(uint8_t op, const CmpInstDetails &details) const {
    auto cmpInst = std::make_unique<CmpInst>(op, basicBlock, details);
    auto instRef = makeRef(*cmpInst);
    basicBlock.addInstructionBack(std::move(cmpInst));
    addUse(instRef, instRef->lhs);
    addUse(instRef, instRef->rhs);
    return instRef;
  }

  [[nodiscard]] CRef<CallInst> createCallInst(const CallInstDetails &details) const {
    auto callInst = std::make_unique<CallInst>(basicBlock, details);
    auto instRef = makeRef(*callInst);
    basicBlock.addInstructionBack(std::move(callInst));
    for (const auto &arg : instRef->realArgs)
      addUse(instRef, arg);
    addUse(instRef, makeRef(instRef->function));
    return instRef;
  }

  [[nodiscard]] CRef<GepInst> createGepInst(const GepInstDetails &details) const {
    auto gepInst = std::make_unique<GepInst>(basicBlock, details);
    auto instRef = makeRef(*gepInst);
    basicBlock.addInstructionBack(std::move(gepInst));
    addUse(instRef, instRef->pointer);
    addUse(instRef, instRef->index);
    return instRef;
  }

  [[nodiscard]] CRef<LoadInst> createLoadInst(const LoadInstDetails &details) const {
    auto loadInst = std::make_unique<LoadInst>(basicBlock, details);
    auto instRef = makeRef(*loadInst);
    basicBlock.addInstructionBack(std::move(loadInst));
    addUse(instRef, instRef->pointer);
    return instRef;
  }

  [[nodiscard]] CRef<RetInst> createRetInst(Ref<Value> value) const {
    auto retInst = std::make_unique<RetInst>(basicBlock, value);
    auto instRef = makeRef(*retInst);
    basicBlock.addInstructionBack(std::move(retInst));
    return instRef;
  }

  CRef<BrInst> createBrInst(BasicBlock &dest) const;

  [[nodiscard]] CRef<BrInst> createBrInst(const BrInstDetails &cond) const;

  [[nodiscard]] CRef<StoreInst> createStoreInst(const StoreInstDetails &details) const {
    auto storeInst = std::make_unique<StoreInst>(basicBlock, details);
    auto instRef = makeRef(*storeInst);
    basicBlock.addInstructionBack(std::move(storeInst));
    addUse(instRef, instRef->pointer);
    addUse(instRef, instRef->value);
    return instRef;
  }
private:
  BasicBlock &basicBlock;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_IR_BUILDER_H
