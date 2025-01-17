//
// Created by creeper on 12/19/24.
//
#include "chiisai-llvm/constant-array.h"

#include <chiisai-llvm/backend/riscv/assembly-generator.h>
#include <chiisai-llvm/backend/riscv/passes/liveness-analysis.h>
#include <chiisai-llvm/backend/riscv/passes/register-weight-estimation.h>
#include <chiisai-llvm/backend/riscv/riscv-backend.h>
#include <chiisai-llvm/backend/riscv/riscv-reg-alloc.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/passes/floating-use-analysis.h>
#include <queue>
#include <unordered_set>

namespace llvm {

std::string RiscvBackend::generateAssembly(const Module &module) const {
  abiInfo = std::make_unique<FunctionABIInfo>(module);
  std::string assembly{};

  assembly += ".text\n";
  for (auto func : module.functions)
    abiInfo->runOnFunction(*func);
  for (auto func : module.functions) {
    if (!func->isImplemented())
      assembly += ".addrsig_sym " + func->name() + "\n";
    else
      assembly += generateAssembly(*func);
  }

  assembly += ".data\n";
  for (auto globalVar : module.globalVariables) {
    assembly += ".globl " + globalVar->name() + "\n";
    assembly += globalVar->name() + ":\n";
    if (!globalVar->hasInitializer()) {
      assembly +=
          ".zero " + std::to_string(sizeOfType(globalVar->type())) + "\n";
      assembly += ".size " + globalVar->name() + ", " +
                  std::to_string(sizeOfType(globalVar->type())) + "\n";
    } else {
      auto initializer = globalVar->initializer();
      std::stringstream ss{};
      auto constToString = [&](CRef<Constant> constant) {
        auto size = sizeOfType(constant->type());
        if (size == 4) {
          ss << ".word ";
          if (!isConstantHex(constant->name()))
            ss << constant->name() << "\n";
          else {
            // bit cast 64-bit hex to double -> float -> 32-bit hex
            auto hex = constant->name();
            auto doubleHex = std::stoull(hex, nullptr, 16);
            auto doubleVal = std::bit_cast<double>(doubleHex);
            auto floatVal = static_cast<float>(doubleVal);
            auto floatHex = std::bit_cast<uint32_t>(floatVal);
            ss << "0x" << std::hex << floatHex << "\n";
          }
        }
        if (size == 8)
          ss << ".quad " + constant->name() + "\n";
      };
      if (isa<ConstantArray>(initializer)) {
        for (auto array = cast<ConstantArray>(initializer);
             auto elem : array->elements)
          constToString(elem);
      } else
        constToString(initializer);
      ss << ".size " << globalVar->name() << ", "
         << sizeOfType(globalVar->type()) << "\n";
      assembly += ss.str();
    }
  }
  return assembly;
}

std::string RiscvBackend::generateAssembly(const Function &function) const {
  PseudoInstTranslator translator(ctx, function);

  translator.translate();
  auto pseudoInstSeq = translator.pseudoInstSequence();
  LivenessAnalysisPass livenessAnalysisPass(pseudoInstSeq, function);
  livenessAnalysisPass.runOnInstSequence();
  LoopAnalysis loopAnalysisPass{};
  RegisterWeightEstimationPass regWeightEstPass(
      livenessAnalysisPass, loopAnalysisPass, translator.pseudoInsts);
  regWeightEstPass.runOnFunction(function);
  abiInfo = std::make_unique<FunctionABIInfo>(function.module());
  for (auto func : function.module().functions)
    abiInfo->runOnFunction(*func);

  auto stdRegConfig = RegisterConfig::standardConfig();
  auto fpRegConfig = RegisterConfig::floatingPointConfig();

  std::vector regConfigs{stdRegConfig, fpRegConfig};

  auto regAllocResult = RiscvRegAllocator(
                            regConfigs, regWeightEstPass,
                            [&](const std::string &reg) {
                              return translator.vRegModifier.contains(reg) &&
                                             (translator.vRegModifier.at(reg) ==
                                                  RegModifier::Float ||
                                              translator.vRegModifier.at(reg) ==
                                                  RegModifier::Double)
                                         ? 1
                                         : 0;
                            },
                            function)
                            .allocate();

  auto assemblyGenerator = RiscvAssemblyCodeGenerator(
      regAllocResult, pseudoInstSeq, translator.vRegModifier, *abiInfo,
      livenessAnalysisPass);
  return assemblyGenerator.generate(function);
}
} // namespace llvm