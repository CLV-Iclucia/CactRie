//
// Created by creeper on 1/13/25.
//

#ifndef DATA_FLOW_ANALYSIS_H
#define DATA_FLOW_ANALYSIS_H

#include <chiisai-llvm/function.h>
#include <chiisai-llvm/instruction.h>
#include <queue>
#include <unordered_set>

namespace llvm {
struct PhiInst;
struct DataFlowAnalysis {
  // follow the above pseudocode
  struct CFGEdge {
    CRef<BasicBlock> from{};
    CRef<BasicBlock> to{};
    bool isExecutable{};
  };
  struct SSAEdge {
    CRef<Value> from{};
    CRef<Value> to{};
    bool isExecutable{};
  };
  void sparseDataFlowPropagation(const Function &func) ;
  void visitPhi(CRef<PhiInst> phi) ;
  void visitInstruction(CRef<Instruction> inst) ;
};
} // namespace llvm
#endif // DATA_FLOW_ANALYSIS_H
