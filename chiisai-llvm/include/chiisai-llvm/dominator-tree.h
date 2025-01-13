//
// Created by creeper on 12/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_DOMINATION_TREE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_DOMINATION_TREE_H
#include <algorithm>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/ref.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace llvm {

// I had planned to use Csr Matrix here...but let's just keep it simple and
// stupid
struct SparseGraph {
  SparseGraph() = default;
  explicit SparseGraph(std::vector<std::vector<uint32_t>> adj)
      : succ(std::move(adj)) {
    prev.resize(succ.size());
    for (size_t i = 0; i < this->succ.size(); ++i)
      for (auto succ : this->succ[i])
        prev[succ].push_back(i);
  }
  template <typename T, typename U>
    requires std::is_integral_v<T> && std::is_integral_v<U>
  explicit SparseGraph(const std::unordered_set<std::pair<T, U>> &adjMat) {
    // compair all the keys and values in adj to find the maximum node
    size_t maxNode = 0;
    for (auto [from, to] : adjMat)
      maxNode = std::max(
          {maxNode, static_cast<size_t>(from), static_cast<size_t>(to)});
    succ.resize(maxNode + 1);
    prev.resize(maxNode + 1);
    for (const auto &[from, to] : adjMat) {
      succ[from].emplace_back(to);
      prev[to].emplace_back(from);
    }
  }
  void addEdge(size_t from, size_t to) { succ[from].push_back(to); }
  [[nodiscard]] const std::vector<uint32_t> &successors(size_t node) const {
    return succ[node];
  }
  [[nodiscard]] const std::vector<uint32_t> &predecessors(size_t node) const {
    return prev[node];
  }
  [[nodiscard]]
  size_t numNodes() const {
    return succ.size();
  }

private:
  std::vector<std::vector<uint32_t>> succ{};
  std::vector<std::vector<uint32_t>> prev{};
};

struct DominatorTreeImpl {
  void buildFromGraph(const SparseGraph &graph, size_t entry);
  [[nodiscard]] bool dominates(size_t a, size_t b) const;
  [[nodiscard]] const std::vector<uint32_t> &
  dominanceFrontier(size_t node) const {
    return domFrontiers.at(node);
  }
  [[nodiscard]] uint32_t dominanceLevel(size_t node) const {
    return depth.at(node);
  }
  uint32_t fatherOf(uint32_t node) const { return father[node]; }

private:
  std::vector<uint32_t> father{};
  std::vector<uint32_t> depth{};
  std::vector<std::vector<uint32_t>> domFrontiers{};
  uint32_t root{};
};

struct DominatorTree {
  void buildFromCFG(const Function &func);
  bool dominates(CRef<BasicBlock> a, CRef<BasicBlock> b) const {
    return domTree.dominates(blockToIndex.at(a), blockToIndex.at(b));
  }
  std::vector<Ref<BasicBlock>> dominanceFrontier(CRef<BasicBlock> node) const {
    std::vector<Ref<BasicBlock>> result{};
    result.resize(domTree.dominanceFrontier(blockToIndex.at(node)).size());
    std::ranges::transform(domTree.dominanceFrontier(blockToIndex.at(node)),
                           result.begin(),
                           [this](uint32_t idx) { return indexToBlock[idx]; });
    return result;
  }
  CRef<BasicBlock> fatherOf(CRef<BasicBlock> node) const {
    return indexToBlock.at(domTree.fatherOf(blockToIndex.at(node)));
  }
  uint32_t dominanceLevel(CRef<BasicBlock> node) const {
    return domTree.dominanceLevel(blockToIndex.at(node));
  }

private:
  std::unordered_map<CRef<BasicBlock>, uint32_t> blockToIndex{};
  std::vector<Ref<BasicBlock>> indexToBlock{};
  DominatorTreeImpl domTree{};
};
} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_DOMINATION_TREE_H
