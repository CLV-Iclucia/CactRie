//
// Created by creeper on 12/19/24.
//
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/basic-block.h>
namespace llvm {

static RiscvPseudoBinary toPseudoBinary(CRef<BinaryInst> inst) {
  return RiscvPseudoBinary{
    .result = inst->name(),
    .lhs = inst->lhs->name(),
    .rhs = inst->rhs->name(),
    .op = static_cast<Instruction::BinaryOps>(inst->opCode)
  };
}

static RiscvPseudoCmp toPseudoCmp(CRef<CmpInst> inst) {
  return RiscvPseudoCmp{
    .lhs = inst->lhs->name(),
    .rhs = inst->rhs->name(),
    .dest = inst->name(),
    .predicate = inst->predicate,
  };
}

static PseudoInstruction toPseudoInstruction(CRef<Instruction> inst) {
  if (inst->isBinary())
    return toPseudoBinary(cast<BinaryInst>(inst));
}

void RiscvBackend::eliminatePhi(CRef<BasicBlock> block, CRef<PhiInst> phi) {
  const auto& phiName = phi->name();
  for (const auto& [pred, reg] : phi->incomingValues) {
    pseudoInstructions[pred].emplace_back(PseudoMove{
      .dest = phiName,
      .src = reg->name(),
    });
  }
}

void RiscvBackend::buildPseudoInstructions(const Module &module) {
  for (auto func : module.functions) {
    for (const auto& bb : func->basicBlocks()) {
      for (auto block = makeCRef(bb); auto inst : block->instructions) {
        if (!isa<PhiInst>(inst))
          pseudoInstructions[block].emplace_back(toPseudoInstruction(inst));
        else
          eliminatePhi(block, cast<PhiInst>(inst));
      }
    }
  }
}
} // namespace llvm