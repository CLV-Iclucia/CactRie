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
#include <optional>
#include <chiisai-llvm/mystl/observer_ptr.h>
#include <chiisai-llvm/literal.h>
namespace llvm {

struct Instruction;
struct Function;
struct BasicBlock;
struct Module;

struct VariableInfo {
  std::string name;
  bool isConstant;
  std::optional<Literal> initialValue;
};

struct FunctionInfo {
  std::string name;
};

struct Variable {
  explicit Variable(VariableInfo &&info)
      : m_name(std::move(info.name)), m_isConstant(info.isConstant), m_initialValue(info.initialValue) {}
  [[nodiscard]] bool isConstant() const {
    return m_isConstant;
  }
  [[nodiscard]] const std::optional<Literal> &initialValue() const {
    return m_initialValue;
  }
  [[nodiscard]] const std::string &name() const {
    return m_name;
  }
  [[nodiscard]] bool match(LLVMType otherType) const {
    return this->type == otherType;
  }
private:
  LLVMType type;
  bool m_isConstant;
  std::string m_name;
  std::optional<Literal> m_initialValue;
};

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
  int idx;
  observer_ptr<const BasicBlock> basicBlock{};
};

struct BasicBlock {
  observer_ptr<Function> function{};
  auto &instructions() { return m_instructions; }
private:
  friend struct Function;
  size_t idx;
  std::list<std::unique_ptr<Instruction>> m_instructions{};
  std::list<std::reference_wrapper<BasicBlock>> successors{};
  std::list<std::reference_wrapper<BasicBlock>> predecessors{};
};

struct Function {
  explicit Function(const FunctionInfo &functionInfo)
      : name(functionInfo.name) {}
  using BlockListIter = std::list<std::reference_wrapper<BasicBlock>>::iterator;

  [[nodiscard]] const std::string &functionName() const { return name; }
  void appendBlock(BasicBlock &&block) {
    block.idx = basicBlocks.size();
    basicBlocks.emplace_back(block);
  }
  void removeBasicBlock(BlockListIter& iter) {
    auto cur = iter;
    basicBlocks.erase(cur);
    ++iter;
  }
  void removeBasicBlock(std::reference_wrapper<BasicBlock> block) {
    removeBasicBlock(block.get());
  }
  void removeBasicBlock(BasicBlock &block) {
    auto idx = block.idx;
    std::swap(basicBlockContainer[idx], basicBlockContainer.back());
  }
  BasicBlock &entryBlock() {
    return *basicBlocks.begin();
  }
  std::list<std::reference_wrapper<BasicBlock>> basicBlocks{};
private:
  std::vector<BasicBlock> basicBlockContainer{};
  std::string name;
};

struct ModuleInfo {
  std::list<Function> functions;
  std::vector<Variable> globalVars;
  std::string name;
};

struct Module {
  explicit Module(ModuleInfo &&info)
      : functions(std::move(info.functions)), globalVars(std::move(info.globalVars)), m_moduleName(info.name) {}
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
  Variable &globalVar(const std::string &name) {
    if (functionMap.find(name) != functionMap.end())
      return globalVars.at(globalVarMap[name]);
    for (auto i = 0; i < globalVars.size(); i++) {
      if (globalVars[i].name() == name) {
        globalVarMap.insert({name, i});
        return globalVars[i];
      }
    }
    throw std::runtime_error("function not found");
  }
  bool findGlobalVar(const std::string &name) {
    if (globalVarMap.find(name) != globalVarMap.end())
      return true;
    for (auto i = 0; i < globalVars.size(); i++) {
      if (globalVars[i].name() == name) {
        globalVarMap.insert({name, i});
        return true;
      }
    }
    return false;
  }
  std::list<Function> functions{};
  std::vector<Variable> globalVars{};
private:
  std::map<std::string, std::reference_wrapper<Function>> functionMap{};
  std::map<std::string, size_t> globalVarMap{};
  std::string m_moduleName{};
};

}

#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H
