//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#include <variant>
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/basic-block.h>
namespace llvm {

struct Instruction : User {
  enum TerminatorOps : uint8_t {
    Ret,
    Br,
    Invoke,
    TerminatorIDEnd,
  };

  enum UnaryOps : uint8_t {
    Neg = static_cast<uint8_t>(TerminatorIDEnd),
    UnaryIDEnd
  };

  enum BinaryOps : uint8_t {
    Add = static_cast<uint8_t>(UnaryIDEnd),
    FAdd,
    Sub,
    FSub,
    Mul,
    FMul,
    SDiv,
    FDiv,
    SRem,
    Xor,
    Shl,
    LShr,
    AShr,
    BinaryIDEnd
  };

  enum LogicalOps : uint8_t {
    And = static_cast<uint8_t>(BinaryIDEnd),
    Or,
    LogicalIDEnd
  };

  enum MemoryOps : uint8_t {
    Alloca = static_cast<uint8_t>(LogicalOps::LogicalIDEnd),
    Load,
    Store,
    MemoryIDEnd
  };

  uint8_t opCode;

  [[nodiscard]] bool isTerminator() const {
    return opCode < TerminatorIDEnd;
  }

  [[nodiscard]] bool isUnary() const {
    return opCode >= UnaryIDEnd && opCode < BinaryIDEnd;
  }

  [[nodiscard]] bool isBinary() const {
    return opCode >= BinaryIDEnd && opCode < LogicalIDEnd;
  }

  [[nodiscard]] bool isLogical() const {
    return opCode >= LogicalIDEnd && opCode < MemoryIDEnd;
  }

  [[nodiscard]] bool isMemory() const {
    return opCode >= MemoryIDEnd;
  }

  [[nodiscard]] bool isReflexive() const {
    return opCode == And;
  }

  [[nodiscard]] bool isCommutative() const {
    return opCode == Add || opCode == Mul || opCode == And || opCode == Or;
  }

  [[nodiscard]] CRef<BasicBlock> basicBlock() const {
    return m_basicBlock;
  }
  [[nodiscard]] CRef<Function> function() const {
    return basicBlock()->function();
  }
  [[nodiscard]] CRef<Module> module() const {
    return function()->module();
  }
private:
  CRef<BasicBlock> m_basicBlock{};
};

struct BinaryInstruction : Instruction {
  CRef<Value> lhs, rhs;
};

}
#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
