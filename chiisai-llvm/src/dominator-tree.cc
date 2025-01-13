//
// Created by creeper on 12/16/24.
//

#include <chiisai-llvm/dominator-tree.h>
#include <chiisai-llvm/function.h>
#include <minilog/logger.h>
#include <mystl/bit_vector.h>
#include <queue>

namespace llvm {

static void computeDepth(const std::vector<std::vector<uint32_t>> &succ,
                         uint32_t father, std::vector<uint32_t> &depth) {
  for (auto son : succ.at(father)) {
    depth[son] = depth[father] + 1;
    computeDepth(succ, son, depth);
  }
}

void DominatorTreeImpl::buildFromGraph(const SparseGraph &graph, size_t entry) {
  std::queue<uint32_t> workList{};
  mystl::bit_vector inQueue(graph.numNodes(), false);
  std::vector<mystl::bit_vector> dom(graph.numNodes());
  for (auto i : std::views::iota(0u, graph.numNodes()))
    if (i == entry) {
      dom[i] = mystl::bit_vector(graph.numNodes(), false);
      dom[i].place(i);
    } else
      dom[i] = mystl::bit_vector(graph.numNodes(), true);
  workList.push(entry);
  inQueue.place(entry);
  dom[entry].place(entry);

  auto inState = [&](uint32_t node) -> mystl::bit_vector {
    mystl::bit_vector result(graph.numNodes(), true);
    for (auto pred : graph.predecessors(node))
      result &= dom[pred];
    return result;
  };

  while (!workList.empty()) {
    auto current = workList.front();
    workList.pop();
    inQueue.unset(current);
    for (auto succ : graph.successors(current)) {
      auto newOutState = inState(succ);
      newOutState.place(succ);
      if (dom[succ] == newOutState)
        continue;
      dom[succ] = newOutState;
      if (inQueue[succ])
        continue;
      workList.push(succ);
      inQueue.place(succ);
    }
  }

  root = entry;
  father.resize(graph.numNodes());
  for (auto u : std::views::iota(0u, graph.numNodes())) {
    if (u == entry)
      continue;
    for (auto v : dom[u]) {
      assert(dom[u][v]);
      if (auto domSet = dom[u]; domSet.unset(u).unset(v).is_subset_of(dom[v])) {
        father[u] = v;
        break;
      }
    }
  }

  domFrontiers.resize(graph.numNodes());
  for (auto u : std::views::iota(0u, graph.numNodes())) {
    if (u == entry)
      continue;
    if (graph.predecessors(u).size() < 2)
      continue;
    for (auto pred : graph.predecessors(u)) {
      auto runner = pred;
      while (runner != father[u]) {
        domFrontiers[runner].emplace_back(u);
        runner = father[runner];
      }
    }
  }

  std::vector<std::vector<uint32_t>> succ(graph.numNodes());

  for (auto u : std::views::iota(0u, graph.numNodes())) {
    if (u == entry)
      continue;
    succ[father[u]].emplace_back(u);
  }
  depth.resize(graph.numNodes(), 0);
  computeDepth(succ, entry, depth);
}

bool DominatorTreeImpl::dominates(size_t a, size_t b) const {
  if (a == b)
    return true;
  if (a == root)
    return true;
  while (b != root) {
    if (a == b)
      return true;
    b = father[b];
  }
  return false;
}

void DominatorTree::buildFromCFG(const Function &func) {
  static auto logger =
      createFileLogger("dominator-tree.log", minilog::LogLevel::debug);
  indexToBlock.resize(func.basicBlocks().size());
  auto idx = 0;
  for (auto bb : func.basicBlockRefs()) {
    blockToIndex[bb] = idx;
    indexToBlock[idx] = bb;
    ++idx;
  }
  auto entry = blockToIndex[makeCRef(func.basicBlock("entry"))];
  std::unordered_set<std::pair<uint32_t, uint32_t>> cfgAdjMat{};
  for (const auto &bb : func.basicBlocks())
    for (auto succ : bb.successors)
      cfgAdjMat.emplace(blockToIndex[makeCRef(bb)], blockToIndex[succ]);
  domTree.buildFromGraph(SparseGraph(cfgAdjMat), entry);
  // log the dominator tree father
  for (auto [bb, idx] : blockToIndex)
    logger->info("block {} father: {}", bb->name(),
                 indexToBlock[domTree.fatherOf(idx)]->name());
  for (auto [bb, idx] : blockToIndex) {
    std::stringstream ss{};
    for (auto df : domTree.dominanceFrontier(idx))
      ss << indexToBlock[df]->name() << " ";
    logger->debug("block {} dominance frontier: {}", bb->name(), ss.str());
  }
  logger->outStream().flush();
}
} // namespace llvm
