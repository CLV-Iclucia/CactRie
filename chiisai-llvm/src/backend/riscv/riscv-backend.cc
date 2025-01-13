//
// Created by creeper on 12/19/24.
//
#include <chiisai-llvm/backend/riscv/assembly-generator.h>
#include <chiisai-llvm/backend/riscv/passes/liveness-analysis.h>
#include <chiisai-llvm/backend/riscv/passes/register-weight-estimation.h>
#include <chiisai-llvm/backend/riscv/riscv-backend-metadata.h>
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/backend/riscv/riscv-reg-alloc.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/passes/floating-use-analysis.h>
#include <queue>
#include <unordered_set>

namespace llvm {

static int id = 0;

RiscvPseudoBinary
PseudoInstTranslator::toPseudoBinary(CRef<BinaryInst> inst) const {
  // return RiscvPseudoBinary{
  // .result = inst->name(),
  // .lhs = inst->lhs()->name(),
  // .rhs = inst->rhs()->name(),
  // .modifier = typeToModifier.at(inst->type()),
  // .op = static_cast<Instruction::BinaryOps>(inst->opCode)
  // };
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

RiscvPseudoCmp PseudoInstTranslator::toPseudoCmp(CRef<CmpInst> inst) {
  return RiscvPseudoCmp{
      .lhs = inst->lhs()->name(),
      .rhs = inst->rhs()->name(),
      .dest = inst->name(),
      .predicate = toRiscvPredicate(inst->predicate),
  };
}

void PseudoInstTranslator::translateLoad(CRef<BasicBlock> bb,
                                         CRef<LoadInst> load) {
  if (isa<GlobalVariable>(load->pointer())) {
    auto tmpName = "__tmp_" + load->pointer()->name() + "." + std::to_string(id) + "_address__";
    pseudoInsts.at(bb).emplace_back(RiscvLoadGlobal{
        .dest = tmpName,
        .global = cast<GlobalVariable>(load->pointer())->name(),
    });
    pseudoInsts.at(bb).emplace_back(RiscvPseudoLoad{
        .base = tmpName,
        .offset = 0,
        .dest = load->name(),
        .modifier = typeToModifier.at(load->type()),
    });
    return;
  }
  pseudoInsts.at(bb).emplace_back(RiscvPseudoLoad{
      .base = load->pointer()->name(),
      .offset = 0,
      .dest = load->name(),
      .modifier = typeToModifier.at(load->type()),
  });
}

RiscvPseudoInstruction PseudoInstTranslator::toPseudoRet(CRef<RetInst> ret) {
  if (ret->ret())
    return RiscvPseudoRet{.value = ret->ret()->name()};
  return RiscvPseudoRet{};
}

void PseudoInstTranslator::translateCall(CRef<BasicBlock> bb,
                                         CRef<CallInst> call) {
  std::vector<std::string> args{};
  for (auto arg : call->realArgs())
    args.push_back(arg->name());
  pseudoInsts.at(bb).emplace_back(RiscvPseudoCall{
      .result = call->name(),
      .func = call->function()->name(),
      .args = args,
  });
}

RiscvPseudoInstruction
PseudoInstTranslator::toSimplePseudoInstruction(CRef<Instruction> inst) const {
  if (inst->isBinary())
    return toPseudoBinary(cast<BinaryInst>(inst));
  if (isa<RetInst>(inst))
    return toPseudoRet(cast<RetInst>(inst));
  throw std::runtime_error(
      "cannot be trivially translated to single pseudo instruction");
}

void PseudoInstTranslator::translateStore(CRef<BasicBlock> bb,
                                          CRef<StoreInst> store) {
  if (isa<GlobalVariable>(store->pointer())) {
    pseudoInsts.at(bb).emplace_back(RiscvLoadGlobal{
        .dest = "__tmp_" + store->pointer()->name() + "_address__",
        .global = cast<GlobalVariable>(store->pointer())->name(),
    });
    pseudoInsts.at(bb).emplace_back(RiscvPseudoStore{
        .base = "__tmp_" + store->pointer()->name() + "_address__",
        .offset = 0,
        .value = store->value()->name(),
        .modifier = typeToModifier.at(store->value()->type()),
    });
    return;
  }
  pseudoInsts.at(bb).emplace_back(RiscvPseudoStore{
      .base = store->pointer()->name(),
      .offset = 0,
      .value = store->value()->name(),
      .modifier = typeToModifier.at(store->value()->type()),
  });
}
void PseudoInstTranslator::translateJump(CRef<BasicBlock> bb, CRef<BrInst> br) {
  if (br->isConditional()) {
    pseudoInsts.at(bb).emplace_back(RiscvPseudoJump{
        .cond = br->cond().name().substr(1),
        .trueLabel = br->thenBranch().name(),
    });
    // if go beyond above, the cond must be false
    pseudoInsts.at(bb).emplace_back(RiscvPseudoJump{
        .trueLabel = br->elseBranch().name(),
    });
  } else {
    pseudoInsts.at(bb).emplace_back(RiscvPseudoJump{
        .trueLabel = br->thenBranch().name(),
    });
  }
}
void PseudoInstTranslator::translateCmp(CRef<BasicBlock> bb,
                                        CRef<CmpInst> cmp) {
  static std::unordered_map<Predicate, Predicate> negPred{
      {Predicate::UGT, Predicate::ULE},
      {Predicate::ULT, Predicate::UGE},
      {Predicate::SGT, Predicate::SLE},
      {Predicate::SLT, Predicate::SGE},
  };
  if (!negPred.contains(cmp->predicate))
    pseudoInsts.at(bb).emplace_back(toPseudoCmp(cmp));
  else {
    pseudoInsts.at(bb).emplace_back(RiscvPseudoCmp{
        .lhs = cmp->lhs()->name(),
        .rhs = cmp->rhs()->name(),
        .dest = cmp->name(),
        .predicate = toRiscvPredicate(negPred.at(cmp->predicate)),
        .modifier = InstModifier::None,
    });
    pseudoInsts.at(bb).emplace_back(RiscvPseudoBinary{
        .result = cmp->name(),
        .lhs = cmp->name(),
        .rhs = "1",
        .op = Instruction::BinaryOps::Xor,
        .modifier = InstModifier::None,
    });
  }
}

std::string RiscvBackend::generateAssembly(const Module &module) const {
  FloatingUseAnalysis floatingUseAnalysis{};
  floatingUseAnalysis.runOnModule(module);
  std::string assembly{};
  assembly += ".data\n";
  for (auto globalVar : module.globalVariables)
    assembly += ".global " + globalVar->name() + "\n";

  assembly += ".text\n";
  for (auto func : module.functions)
    assembly += generateAssembly(
        *func, floatingUseAnalysis.functionsUsingFloatingPoint.contains(func));
}

PseudoInstTranslator::PseudoInstTranslator(const LLVMContext &ctx,
                                           const Function &func)
    : func(func) {
  typeToModifier.insert({ctx.intType(), InstModifier::Word});
  typeToModifier.insert({ctx.floatType(), InstModifier::Float});
  typeToModifier.insert({ctx.doubleType(), InstModifier::Double});
  typeToModifier.insert({ctx.boolType(), InstModifier::Byte});
  typeToModifier.insert({ctx.floatType(), InstModifier::Float});
  typeToModifier.insert({ctx.longType(), InstModifier::Double});
}

static void toBitShift(RiscvPseudoBinary &inst) {
  static std::unordered_map<uint32_t, uint32_t> logTable{
      {1, 0}, {2, 1}, {4, 2}, {8, 3}, {16, 4}, {32, 5}, {64, 6}, {128, 7},
  };
  switch (inst.op) {
  case Instruction::BinaryOps::Mul:
    auto rhsVal = std::stoi(inst.rhs);
    assert(rhsVal >= 0);
    if (!logTable.contains(rhsVal))
      break;
    inst.op = Instruction::BinaryOps::Shl;
    inst.rhs = std::to_string(logTable.at(rhsVal));
    break;
  }
}

void PseudoInstTranslator::translateGep(CRef<BasicBlock> bb,
                                        CRef<GepInst> gep) {
  if (!gep->index()) {

    return;
  }
  auto baseType = gep->pointer()->type();
  CRef<Type> elementType{};
  if (baseType->isPointer())
    elementType = cast<PointerType>(baseType)->elementType();
  else if (baseType->isArray())
    elementType = cast<ArrayType>(baseType)->elementType();
  else
    throw std::runtime_error("unsupported type in GEP");
  std::string baseName{};
  if (isa<GlobalVariable>(gep->pointer())) {
    baseName = "__tmp_" + gep->pointer()->name() + "." + std::to_string(++id) + "_address__";
    pseudoInsts.at(bb).emplace_back(RiscvLoadGlobal{
        .dest = baseName,
        .global = cast<GlobalVariable>(gep->pointer())->name(),
    });
  } else
    baseName = gep->pointer()->name();
  if (isa<Constant>(gep->index())) {
    assert(isa<ConstantScalar>(gep->index()));
    auto index = cast<ConstantScalar>(gep->index());
    assert(index->type()->isInteger());
    auto offsetVal = std::stoi(index->name()) * sizeOfType(elementType);
    return;
  }
  assert(gep->index()->type()->isInteger());
  auto offsetComputeInst = RiscvPseudoBinary{
      .result = "__" + gep->name() + "_offset_byte__",
      .lhs = gep->index()->name(),
      .rhs = std::to_string(sizeOfType(elementType)),
      .op = Instruction::BinaryOps::Mul,
      .modifier = InstModifier::None,
  };
  toBitShift(offsetComputeInst);
  pseudoInsts.at(bb).emplace_back(offsetComputeInst);
  pseudoInsts.at(bb).emplace_back(RiscvPseudoBinary{
      .result = gep->name(),
      .lhs = baseName,
      .rhs = offsetComputeInst.result,
      .op = Instruction::BinaryOps::Add,
      .modifier = InstModifier::None,
  });
}

void PseudoInstTranslator::translate() {
  std::unordered_map<CRef<BasicBlock>, std::vector<RiscvPseudoInstruction>> phiAppended{};
  auto eliminatePhi = [&](CRef<PhiInst> phi) {
    const auto &phiName = phi->name().substr(1);
    for (auto i = 0; i < phi->incomingValues.size(); i++) {
      auto reg = phi->incomingValues[i];
      auto pred = cast<BasicBlock>(phi->incomingBlocks[i]);
      phiAppended[pred].emplace_back(RiscvPseudoMove{
          .dest = phiName,
          .src = reg->name(),
      });
    }
  };
  for (auto bb : func.basicBlockRefs())
    for (auto inst : bb->instructions)
      if (isa<PhiInst>(inst))
        eliminatePhi(cast<PhiInst>(inst));

  for (auto bb : func.basicBlockRefs()) {
    for (auto inst : bb->instructions) {
      if (isa<PhiInst>(inst))
        eliminatePhi(cast<PhiInst>(inst));
      else if (isa<GepInst>(inst)) {
        translateGep(bb, cast<GepInst>(inst));
      } else if (isa<BrInst>(inst)) {
        pseudoInsts.at(bb).insert(pseudoInsts.at(bb).end(),
                                  phiAppended.at(bb).begin(),
                                  phiAppended.at(bb).end());
        translateJump(bb, cast<BrInst>(inst));
      } else if (isa<CmpInst>(inst)) {
        translateCmp(bb, cast<CmpInst>(inst));
      } else if (isa<LoadInst>(inst)) {
        translateLoad(bb, cast<LoadInst>(inst));
      } else if (isa<StoreInst>(inst)) {
        translateStore(bb, cast<StoreInst>(inst));
      } else if (isa<CallInst>(inst)) {
        translateCall(bb, cast<CallInst>(inst));
      } else if (isa<AllocaInst>(inst)) {

      } else
        pseudoInsts.at(bb).emplace_back(toSimplePseudoInstruction(inst));
    }
  }
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
      q.emplace(succ);
    }
  }
  return result;
}

std::string RiscvBackend::generateAssembly(const Function &function,
                                           bool useFloatingPoint) const {
  const auto &linearizedBlockSeq = linearizeBlocks(function);
  std::vector<RiscvPseudoInstruction> pseudoInstSeq{};

  auto translator = PseudoInstTranslator(ctx, function);
  translator.translate();
  for (auto bb : linearizedBlockSeq) {
    pseudoInstSeq.emplace_back("." + bb->name() + ":");
    pseudoInstSeq.insert(pseudoInstSeq.end(),
                         translator.pseudoInsts.at(bb).begin(),
                         translator.pseudoInsts.at(bb).end());
  }

  LivenessAnalysisPass livenessAnalysisPass(pseudoInstSeq, function);
  livenessAnalysisPass.runOnInstSequence();
  LoopAnalysis loopAnalysisPass{};
  RegisterWeightEstimationPass registerWeightEstimationPass(
      livenessAnalysisPass, loopAnalysisPass, translator.pseudoInsts);
  registerWeightEstimationPass.runOnFunction(function);

  auto stdRegConfig = RegisterConfig::standardConfig();
  auto fpRegConfig = RegisterConfig::floatingPointConfig();

  std::vector regConfigs{stdRegConfig, fpRegConfig};

  std::unordered_map<std::string, bool> isFloatingUse{};
  std::unordered_map<std::string, size_t> sizeInBytes{};
  for (auto &inst : pseudoInstSeq) {
    forUsedRegs(inst, [&](const std::string &reg) {
      if (getModifier(inst) == InstModifier::Float) {
        isFloatingUse[reg] = true;
        sizeInBytes[reg] = 4;
        return;
      }
      if (getModifier(inst) == InstModifier::Double) {
        isFloatingUse[reg] = true;
        sizeInBytes[reg] = 8;
        return;
      }
      isFloatingUse[reg] = false;
      sizeInBytes[reg] = 4;
    });
    forDefinedRegs(inst, [&](const std::string &reg) {
      if (isCmp(inst)) {
        isFloatingUse[reg] = false;
        sizeInBytes[reg] = 4;
        return;
      }
      if (getModifier(inst) == InstModifier::Float) {
        isFloatingUse[reg] = true;
        sizeInBytes[reg] = 4;
      }
      if (getModifier(inst) == InstModifier::Double) {
        isFloatingUse[reg] = true;
        sizeInBytes[reg] = 8;
      }
    });
  }

}
} // namespace llvm