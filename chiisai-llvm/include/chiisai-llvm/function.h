//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
#include <string>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/function-type.h>
namespace llvm {

struct FunctionInfo {
  std::string name;
};

struct BasicBlock;
struct Function : Value {
  explicit Function(const FunctionInfo &functionInfo)
      : m_name(functionInfo.name) {}
  [[nodiscard]] const std::string &name() const { return m_name; }
  [[nodiscard]] CRef<FunctionType> functionType() const {
    return m_functionType;
  }
  [[nodiscard]] std::span<const std::string> argNames() const {
    return {m_argNames};
  }
  std::list<BasicBlock> basicBlocks{};
private:
  std::string m_name;
  CRef<FunctionType> m_functionType{};
  std::vector<std::string> m_argNames{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_FUNCTION_H
