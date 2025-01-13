//
// Created by creeper on 1/13/25.
//
#include <chiisai-llvm/data-flow-analysis.h>
#include <chiisai-llvm/instructions.h>
namespace llvm {
/*
procedure SparseDataFlowPropagation(CFG)
    for each edge in CFG do
        mark edge as non-executable
    end for
    CFGWorkList ← output edges of the CFG start node
    SSAWorkList ← ∅

    while CFGWorkList is not empty or SSAWorkList is not empty do
        if CFGWorkList is not empty then
            edge ← remove top of CFGWorkList
            if edge is non-executable then
                mark edge as executable
                visit φ-operations at the target node of edge
                if target node is reached for the first time then
                    visit all operations at the target node
                end if
                if target node has exactly one non-executable outgoing edge then
                    add that edge to CFGWorkList
                end if
            end if
        else if SSAWorkList is not empty then
            edge ← remove top of SSAWorkList
            targetOp ← target operation of edge
            if targetOp is a φ-operation then
                visit φ-operation(targetOp)
            else
                if any incoming CFG edge to targetOp is executable then
                    visit operation(targetOp)
                end if
            end if
        end if
    end while
end procedure
 */


void DataFlowAnalysis::sparseDataFlowPropagation(const Function &func) {
  std::vector<CFGEdge> cfgEdges{};
  std::vector<SSAEdge> ssaEdges{};
  std::unordered_map<CRef<BasicBlock>, std::vector<uint32_t>> cfg{};
  std::unordered_map<CRef<Value>, std::vector<uint32_t>> ssa{};
  for (auto &bb : func.basicBlocks()) {
    for (auto to : bb.successors) {
      cfgEdges.emplace_back(makeCRef(bb), to, false);
      cfg[makeCRef(bb)].push_back(cfgEdges.size() - 1);
    }
    for (auto inst : bb.instructions) {
      for (auto user : inst->users) {
        ssaEdges.emplace_back(inst, user, false);
        ssa[inst].push_back(ssaEdges.size() - 1);
      }
    }
  }

  std::unordered_set<CRef<BasicBlock>> visited{};
  std::queue<uint32_t> cfgWorkList{};
  std::queue<uint32_t> ssaWorkList{};
  for (auto edge : cfg[makeCRef(func.basicBlock("entry"))])
    cfgWorkList.push(edge);

  while (!cfgWorkList.empty() || !ssaWorkList.empty()) {
    if (!cfgWorkList.empty()) {
      auto edge = cfgWorkList.front();
      cfgWorkList.pop();
      if (cfgEdges[edge].isExecutable) {
        cfgEdges[edge].isExecutable = true;
        auto to = cfgEdges[edge].to;
        if (!visited.contains(to)) {
          visited.insert(to);
          for (auto inst : to->instructions) {
            if (isa<PhiInst>(inst)) {
              visitPhi(cast<PhiInst>(inst));
            } else {
              if (std::any_of(cfg[to].begin(), cfg[to].end(),
                              [&](uint32_t edge) {
                                return cfgEdges[edge].isExecutable;
                              })) {
                visitInstruction(inst);
              }
            }
          }
          if (std::count_if(cfg[to].begin(), cfg[to].end(), [&](uint32_t edge) {
                return cfgEdges[edge].isExecutable;
              }) == 1) {
            for (auto edgeIdx : cfg[to])
              if (!cfgEdges[edgeIdx].isExecutable)
                cfgWorkList.push(edgeIdx);
          }
        }
      }
    } else if (!ssaWorkList.empty()) {
      auto edge = ssaWorkList.front();
      ssaWorkList.pop();
      auto targetOp = ssaEdges[edge].to;
      auto targetInst = cast<Instruction>(targetOp);
      if (isa<PhiInst>(targetOp)) {
        visitPhi(cast<PhiInst>(targetOp));
      } else {
        if (std::any_of(cfg[makeCRef(targetInst->basicBlock)].begin(),
                        cfg[makeCRef(targetInst->basicBlock)].end(), [&](uint32_t edge) {
                          return cfgEdges[edge].isExecutable;
                        })) {
          visitInstruction(targetInst);
        }
      }
    }
  }
}
/*
procedure VisitOperation(operation)
    if operation is φ-operation then
        merge data flow information from operand nodes
        where corresponding CFG edges are executable
    else if operation is a conditional branch then
        check branch condition using operand data flow information
        for each outgoing edge of the branch CFG node do
            if the branch condition may be satisfied then
                if edge is non-executable then
                    add edge to CFGWorkList
                end if
            end if
        end for
    else
        update data flow information of operation using its transfer function
    end if

    if data flow information of operation has changed then
        for each outgoing SSA edge of operation do
            add edge to SSAWorkList
        end for
    end if
end procedure

 */
void DataFlowAnalysis::visitPhi(CRef<PhiInst> phi) {
  // merge data flow information from operand nodes
  // where corresponding CFG edges are executable
}

void DataFlowAnalysis::visitInstruction(CRef<Instruction> inst) {
  // update data flow information of operation using its transfer function
  // if data flow information of operation has changed then
  // for each outgoing SSA edge of operation do
  // add edge to SSAWorkList
  if (isa<PhiInst>(inst)) {
    visitPhi(cast<PhiInst>(inst));
  } else {
  }
}
} // namespace llvm