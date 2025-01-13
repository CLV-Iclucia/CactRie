//
// Created by creeper on 1/13/25.
//
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/instructions.h>
#include <chiisai-llvm/passes/useless-arith-elimination.h>

namespace llvm {

static bool checkZero(Ref<Value> val) {
  if (!isa<Constant>(val))
    return false;
  auto constant = cast<Constant>(val);
  if (!constant->type()->isInteger())
    return false;
  if (constant->name() == "0")
    return true;
  return false;
}

static bool checkOne(Ref<Value> val) {
  if (!isa<Constant>(val))
    return false;
  auto constant = cast<Constant>(val);
  if (!constant->type()->isInteger())
    return false;
  if (constant->name() == "1")
    return true;
  return false;
}

void UselessArithEliminationPass::runOnFunction(Function &func) {
  std::vector<Ref<Instruction>> toRemove{};
  bool changed = false;
  do {
    changed = false;
    for (auto &block : func.basicBlocks()) {
      for (auto inst : block.instructions) {
        if (!inst->isIntBinary())
          continue;
        auto binary = cast<BinaryInst>(inst);
        if (binary->opCode == Instruction::BinaryOps::Mul) {
          if (bool isZero =
                  checkZero(binary->lhs()) || checkZero(binary->rhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(ctx.constant(Type::intType(ctx), "0"));
            logger->info("{} is useless, replaced with 0", binary->toString());
          }
          if (bool isLhs = checkOne(binary->rhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(binary->lhs());
            logger->info("{} is useless, replaced with {}", binary->toString(),
                         binary->lhs()->name());
          }
          if (bool isRhs = checkOne(binary->lhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(binary->rhs());
            logger->info("{} is useless, replaced with {}", binary->toString(),
                         binary->rhs()->name());
          }
        }
        if (binary->opCode == Instruction::BinaryOps::SDiv) {
          if (bool isOne = binary->lhs() == binary->rhs()) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(ctx.constant(Type::intType(ctx), "1"));
            logger->info("{} is useless, replaced with 1", binary->toString());
            continue;
          }
          if (bool isLhs = checkOne(binary->rhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(binary->lhs());
            logger->info("{} is useless, replaced with {}", binary->toString(),
                         binary->lhs()->name());
            continue;
          }
        }
        if (binary->opCode == Instruction::BinaryOps::SRem) {
          bool isZero =
              checkOne(binary->rhs()) || (binary->lhs() == binary->rhs());
          if (isZero) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(ctx.constant(Type::intType(ctx), "0"));
            logger->info("{} is useless, replaced with 0", binary->toString());
          }
        }
        if (binary->opCode == Instruction::BinaryOps::Sub) {
          if (bool isZero = binary->lhs() == binary->rhs()) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(ctx.constant(Type::intType(ctx), "0"));
            logger->info("{} is useless, replaced with 0", binary->toString());
          }
          if (bool isLhs = checkZero(binary->rhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(binary->lhs());
            logger->info("{} is useless, replaced with {}", binary->toString(),
                         binary->lhs()->name());
          }
        }
        if (binary->opCode == Instruction::BinaryOps::Add) {
          if (bool isLhs = checkZero(binary->rhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(binary->lhs());
            logger->info("{} is useless, replaced with {}", binary->toString(),
                         binary->lhs()->name());
          }
          if (bool isRhs = checkZero(binary->lhs())) {
            toRemove.emplace_back(binary);
            changed = true;
            binary->replaceAllUsesWith(binary->rhs());
            logger->info("{} is useless, replaced with {}", binary->toString(),
                         binary->rhs()->name());
          }
        }
      }
      for (auto inst : toRemove)
        block.removeInstruction(inst);
      toRemove.clear();
    }
  } while (changed);
}
} // namespace llvm