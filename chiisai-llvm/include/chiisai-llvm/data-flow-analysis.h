//
// Created by creeper on 12/15/24.
//

#ifndef DATA_FLOW_ANALYSIS_H
#define DATA_FLOW_ANALYSIS_H

#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <queue>
namespace llvm {
struct Instruction;
template <typename T>
concept is_analysis_state = requires(T t) {
  { t.meet(t) } -> std::same_as<T>;
  { T::identity() } -> std::same_as<T>;
  { t == t } -> std::same_as<bool>;
};

template <typename State>
  requires is_analysis_state<State>
struct ForwardDataFlowAnalysis {
  void runOnFunction(Function &function) {
    std::queue<Ref<BasicBlock>> workList{};
    std::unordered_map<Ref<BasicBlock>, bool> inQueue{};
    auto entry = makeRef(function.basicBlock("entry"));
    workList.push(entry);
    inQueue[entry] = true;
    outState[entry] = transfer(entry, State::identity());
    while (!workList.empty()) {
      auto current = workList.front();
      workList.pop();
      inQueue[current] = false;
      for (auto succ : current->successors) {
        auto newOutState = transfer(succ, inState(succ));
        if (outState.contains(succ) && outState[succ] == newOutState)
          continue;
        outState[succ] = newOutState;
        if (inQueue[succ])
          continue;
        workList.push(succ);
        inQueue[succ] = true;
      }
    }
  }
  State inState(Ref<BasicBlock> block) {
    auto result = State::identity();
    for (auto pred : block->predecessors) {
      result = result.meet(outState[pred]);
    }
    return result;
  }
  std::unordered_map<Ref<Instruction>, State> programState{};
  std::unordered_map<Ref<BasicBlock>, State> outState{};
  virtual State transfer(Ref<BasicBlock> block, State incoming) = 0;
  virtual ~ForwardDataFlowAnalysis() = default;
};
} // namespace llvm
#endif // DATA_FLOW_ANALYSIS_H
