//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H

#include <list>
#include <memory>

namespace llvm {

struct Variable {
  enum class Type {
    i32,
    f32,
    f64,
  };
};

struct Instruction {
  enum class BinaryOps {
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
};

struct BasicBlock {
  using InstIterator = std::list<std::unique_ptr<Instruction>>::iterator;
private:
  std::list<std::unique_ptr<Instruction>> instructions{};
  std::list<std::reference_wrapper<BasicBlock>> successors{};
  std::list<std::reference_wrapper<BasicBlock>> predecessors{};
};

struct Function {
  std::list<BasicBlock> basicBlocks{};
};

struct Module {
  explicit Module(const std::string& name) : name(name) {}
  std::list<Function> functions{};
  std::string name{};
};

}

#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_IR_H
