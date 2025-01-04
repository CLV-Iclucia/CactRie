//
// Created by creeper on 12/19/24.
//
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <queue>
#include <unordered_set>
namespace llvm {

RiscvPseudoBinary RiscvBackend::toPseudoBinary(CRef<BinaryInst> inst) const {
  // return RiscvPseudoBinary{
  //     .result = inst->name(),
  //     .lhs = inst->lhs->name(),
  //     .rhs = inst->rhs->name(),
  //     .modifier = typeToModifier.at(inst->type()),
  //     .op = static_cast<Instruction::BinaryOps>(inst->opCode)};
}

static RiscvPredicate toRiscvPredicate(Predicate pred) {
  static std::unordered_map<Predicate, RiscvPredicate> predMap{
      {Predicate::EQ, RiscvPredicate::EQ},
      {Predicate::NE, RiscvPredicate::NE},
      {Predicate::UGT, RiscvPredicate::GT},
      {Predicate::UGE, RiscvPredicate::GE},
      {Predicate::ULT, RiscvPredicate::LT},
      {Predicate::ULE, RiscvPredicate::LE},
      {Predicate::SGT, RiscvPredicate::GT},
      {Predicate::SGE, RiscvPredicate::GE},
      {Predicate::SLT, RiscvPredicate::LT},
      {Predicate::SLE, RiscvPredicate::LE},
  };
  return predMap.at(pred);
}

RiscvPseudoCmp RiscvBackend::toPseudoCmp(CRef<CmpInst> inst) {
  return RiscvPseudoCmp{
      .lhs = inst->lhs()->name(),
      .rhs = inst->rhs()->name(),
      .dest = inst->name(),
      .predicate = toRiscvPredicate(inst->predicate),
  };
}

PseudoInstruction
RiscvBackend::toSimplePseudoInstruction(CRef<Instruction> inst) const {
  if (inst->isBinary())
    return toPseudoBinary(cast<BinaryInst>(inst));
  if (inst->isComparison())
    return toPseudoCmp(cast<CmpInst>(inst));
}

RiscvBackend::RiscvBackend(const LLVMContext &ctx) {
  typeToModifier.insert({ctx.intType(), InstModifier::Word});
  typeToModifier.insert({ctx.floatType(), InstModifier::Float});
  typeToModifier.insert({ctx.doubleType(), InstModifier::Double});
  typeToModifier.insert({ctx.boolType(), InstModifier::Byte});
  typeToModifier.insert({ctx.floatType(), InstModifier::Float});
  typeToModifier.insert({ctx.longType(), InstModifier::Double});
}

static std::vector<CRef<BasicBlock>> linearizeBlocks(const Function &func) {
  std::queue<CRef<BasicBlock>> q;
  std::unordered_set<CRef<BasicBlock>> visited;
  std::vector<CRef<BasicBlock>> result{};
  q.push(makeCRef(func.basicBlock("entry")));
  visited.insert(makeCRef(func.basicBlock("entry")));
  while (!q.empty()) {
    auto bb = q.front();
    result.push_back(bb);
    q.pop();
    for (auto succ : bb->successors) {
      if (visited.contains(succ))
        continue;
      visited.insert(succ);
      q.push(succ);
    }
  }
  return result;
}

std::string RiscvBackend::generateAssembly(const Function &function) const {
  const auto& linearizedBlockSeq = linearizeBlocks(function);
  std::unordered_map<CRef<BasicBlock>, std::vector<PseudoInstruction>> pseudoInsts{};
  std::vector<PseudoInstruction> pseudoInstSeq{};
  auto eliminatePhi = [&](CRef<PhiInst> phi) {
    const auto &phiName = phi->name();
    for (auto i = 0; i < phi->incomingValues.size(); i++) {
      auto reg = phi->incomingValues[i];
      auto pred = cast<BasicBlock>(phi->incomingBlocks[i]);
      pseudoInsts.at(pred).emplace_back(PseudoMove{
          .dest = phiName,
          .src = reg->name(),
      });
    }
  };

  for (auto bb : linearizedBlockSeq) {
    for (auto inst : bb->instructions) {

    }
  }

  for (auto bb : linearizedBlockSeq)
    pseudoInstSeq.insert(pseudoInstSeq.end(), pseudoInsts.at(bb).begin(), pseudoInsts.at(bb).end());

  return "";
}
void RiscvBackend::buildPseudoInstructions(const Module &module) {
  for (auto func : module.functions) {
  }
}
} // namespace llvm