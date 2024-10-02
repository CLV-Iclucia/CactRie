//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#include <string>

namespace llvm {

struct FunctionInfo {
  std::string name;
};

struct Function {
  explicit Function(const FunctionInfo &functionInfo)
      : name(functionInfo.name) {}
  [[nodiscard]] const std::string &functionName() const { return name; }

private:
  std::string name;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
