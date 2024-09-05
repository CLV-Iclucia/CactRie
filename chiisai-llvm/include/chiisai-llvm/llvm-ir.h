//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H

#include <list>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <chiisai-llvm/mystl/observer_ptr.h>
namespace llvm {

struct Variable;
struct Instruction;
struct Function;
struct BasicBlock;
struct Module;


struct Instruction {
  enum class BinaryOp {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    And,
    Or,
    Xor,
    Shl,
    LShr,
    AShr,
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
  };
  enum class MemoryOp {
    Load,
    Store,
  };
  const BasicBlock &basicBlock;
};

struct BasicBlock {
  const Function &function;
  auto &instructions() { return m_instructions; }
private:
  std::list<std::unique_ptr<Instruction>> m_instructions{};
  std::list<std::reference_wrapper<BasicBlock>> successors{};
  std::list<std::reference_wrapper<BasicBlock>> predecessors{};
};

struct Function {
  std::list<BasicBlock> basicBlocks{};
  const Module &module;
  [[nodiscard]] const std::string &functionName() const { return name; }
  BasicBlock &entryBlock() {
    return *basicBlocks.begin();
  }
private:
  std::string name;
};

struct Module {
  explicit Module(const std::string &name) : m_moduleName(name) {}
  [[nodiscard]] const std::string &moduleName() const { return m_moduleName; }
  Function &function(const std::string &name) {
    if (functionMap.find(name) != functionMap.end())
      return functionMap.at(name).get();
    for (auto &func : functions) {
      if (func.functionName() == name) {
        functionMap.insert({name, func});
        return func;
      }
    }
    throw std::runtime_error("function not found");
  }
  bool findFunction(const std::string &name) {
    if (functionMap.find(name) != functionMap.end())
      return true;
    for (auto &func : functions) {
      if (func.functionName() == name) {
        functionMap.insert({name, func});
        return true;
      }
    }
    return false;
  }
  std::list<Function> functions{};
private:
  std::map<std::string, std::reference_wrapper<Function>> functionMap{};
  std::string m_moduleName{};
};

}

#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H
