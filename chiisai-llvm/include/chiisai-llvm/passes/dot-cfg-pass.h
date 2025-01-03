//
// Created by creeper on 12/15/24.
//

#ifndef DOT_CFG_PASS_H
#define DOT_CFG_PASS_H
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/instructions.h>
#include <filesystem>
#include <fstream>

namespace llvm {
struct DotCFGPass {
  explicit DotCFGPass(const std::filesystem::path& path) : file(path) {
    if (!file.is_open())
      throw std::runtime_error("DotCFGPass: failed to open file " + path.string());
  }

  void runOnFunction(Function&func) {
    if (!func.isImplemented())
      return ;
    file << "digraph \"CFG of " << func.name() << "\" {\nnode [shape=\"box\"];\n";
    std::unordered_map<CRef<BasicBlock>, std::string> blockContents{};
    for (const auto& bb : func.basicBlocks()) {
      auto blockRef = makeCRef(bb);
      blockContents.insert({blockRef, {}});
      for (auto inst : bb.instructions)
        blockContents[blockRef] += inst->toString() + "\n";
    }
    for (const auto& bb : func.basicBlocks()) {
      auto blockRef = makeCRef(bb);
      file << std::format("\"{}\" [label=\"{}\"];\n", bb.name(), bb.name() + "\n\n" + blockContents[blockRef]);
    }
    for (auto bb : func.basicBlockRefs())
      for (auto inst : bb->instructions) {
        if (isa<BrInst>(inst)) {
          if (auto brInst = cast<BrInst>(inst); brInst->isConditional()) {
            file << std::format("\"{}\" -> \"{}\" [label=\"true\"];\n", bb->name(), brInst->thenBranch().name());
            file << std::format("\"{}\" -> \"{}\" [label=\"false\"];\n", bb->name(), brInst->elseBranch().name());
          } else
            file << std::format("\"{}\" -> \"{}\";\n", bb->name(), brInst->thenBranch().name());
        }
      }
    file << "}\n" << std::flush;
  }

  ~DotCFGPass() = default;
  std::ofstream file;
};
};

#endif //DOT_CFG_PASS_H
