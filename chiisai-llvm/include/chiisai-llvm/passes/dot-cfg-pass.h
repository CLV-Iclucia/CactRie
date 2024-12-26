//
// Created by creeper on 12/15/24.
//

#ifndef DOT_CFG_PASS_H
#define DOT_CFG_PASS_H
#include <filesystem>
#include <fstream>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/instruction.h>

namespace llvm {
struct DotCFGPass {
  explicit DotCFGPass(const std::filesystem::path& path) : file(path) {
    if (!file.is_open())
      throw std::runtime_error("failed to open file");
  }

  void runOnFunction(Function&func) {
    if (!func.isImplemented())
      return ;
    file << "diagraph G(" << func.name() << ") {\n";
    std::unordered_map<CRef<BasicBlock>, std::string> blockContents{};
    for (const auto& bb : func.basicBlocks()) {
      auto blockRef = makeCRef(bb);
      blockContents.insert({blockRef, {}});
      for (auto inst : bb.instructions)
        blockContents[blockRef] += inst->toString();
    }
    for (const auto& bb : func.basicBlocks()) {
      auto blockRef = makeCRef(bb);
      file << std::format("{} [label=\"{}\"];\n", bb.name(), blockContents[blockRef]);
    }
    for (auto bb : func.basicBlockRefs())
      for (auto inst : bb->instructions) {
        if (auto brInst = cast<BrInst>(inst)) {
          if (brInst->isConditional()) {
            file << std::format("{} -> {} [label=\"true\"];\n", bb->name(), brInst->thenBranch().name());
            file << std::format("{} -> {} [label=\"false\"];\n", bb->name(), brInst->elseBranch().name());
          } else
            file << std::format("{} -> {};\n", bb->name(), brInst->thenBranch().name());
        }
      }
    file << "}\n" << std::flush;
  }

  ~DotCFGPass() = default;
  std::fstream file;
};
};

#endif //DOT_CFG_PASS_H
