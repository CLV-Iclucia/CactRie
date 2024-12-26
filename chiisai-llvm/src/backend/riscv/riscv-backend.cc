//
// Created by creeper on 12/19/24.
//
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
namespace llvm {

RiscvPseudoBinary RiscvBackend::toPseudoBinary(CRef<BinaryInst> inst) const {
  return RiscvPseudoBinary{
      .result = inst->name(),
      .lhs = inst->lhs->name(),
      .rhs = inst->rhs->name(),
      .modifier = typeToModifier.at(inst->type()),
      .op = static_cast<Instruction::BinaryOps>(inst->opCode)};
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
      .lhs = inst->lhs->name(),
      .rhs = inst->rhs->name(),
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

void RiscvBackend::eliminatePhi(CRef<PhiInst> phi) {
  const auto &phiName = phi->name();
  for (const auto &[pred, reg] : phi->incomingValues) {
    pseudoInstructions.at(pred).emplace_back(PseudoMove{
        .dest = phiName,
        .src = reg->name(),
    });
  }
}

void RiscvBackend::buildPseudoInstructions(const Module &module) {
  for (auto func : module.functions) {
    for (const auto &bb : func->basicBlocks()) {
      for (auto block = makeCRef(bb); auto inst : block->instructions) {
        if (isa<PhiInst>(inst))
          eliminatePhi(cast<PhiInst>(inst));
        else if (isa<GepInst>(inst)) {

        }
        else
          pseudoInstructions.at(block).emplace_back(toSimplePseudoInstruction(inst));
      }
    }
  }
}
} // namespace llvm