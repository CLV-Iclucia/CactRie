//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H

#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/predicate.h>
#include <chiisai-llvm/user.h>

namespace llvm {

struct BasicBlock;
struct Function;
struct Instruction : User {
  explicit Instruction(uint8_t op, const std::string &name, CRef<Type> type,
                       BasicBlock &basicBlock)
      : User(name, type), opCode(op), basicBlock(basicBlock) {}
  enum TerminatorOps : uint8_t {
    Ret,
    Br,
    TerminatorIDEnd,
  };

  enum BinaryOps : uint8_t {
    Add = static_cast<uint8_t>(TerminatorIDEnd),
    Sub,
    Mul,
    SDiv,
    SRem,
    Xor,
    Shl,
    LShr,
    AShr,
    FAdd,
    FSub,
    FMul,
    FDiv,
    BinaryIDEnd
  };

  enum LogicalOps : uint8_t {
    And = static_cast<uint8_t>(BinaryIDEnd),
    Or,
    LogicalIDEnd
  };

  enum MemoryOps : uint8_t {
    Alloca = static_cast<uint8_t>(LogicalIDEnd),
    Load,
    Store,
    Gep,
    MemoryIDEnd
  };

  enum OtherOps : uint8_t {
    Phi = static_cast<uint8_t>(MemoryIDEnd),
    Call,
    ICmp,
    FCmp,
    OtherIDEnd
  };

  uint8_t opCode;

  [[nodiscard]] bool isTerminator() const { return opCode < TerminatorIDEnd; }

  [[nodiscard]] bool isBinary() const {
    return opCode >= BinaryIDEnd && opCode < LogicalIDEnd;
  }

  [[nodiscard]] bool isIntBinary() const {
    return opCode >= Add && opCode < AShr;
  }

  [[nodiscard]] bool isFloatBinary() const {
    return opCode >= FAdd && opCode < BinaryIDEnd;
  }

  [[nodiscard]] bool isLogical() const {
    return opCode >= LogicalIDEnd && opCode < MemoryIDEnd;
  }

  [[nodiscard]] bool isMemory() const { return opCode >= MemoryIDEnd; }

  [[nodiscard]] bool isReflexive() const { return opCode == And; }

  [[nodiscard]] bool isCommutative() const {
    return opCode == Add || opCode == Mul || opCode == And || opCode == Or;
  }

  [[nodiscard]] bool isComparison() const {
    return opCode == ICmp || opCode == FCmp;
  }

  [[nodiscard]] bool isOther() const { return opCode >= OtherIDEnd; }

  static bool checkBinaryInstType(CRef<Value> lhs, CRef<Value> rhs) {
    if (lhs->type() != rhs->type())
      return false;
    if (!lhs->type()->isComputable())
      return false;
    return true;
  }

  [[nodiscard]] virtual std::string toString() const = 0;
  BasicBlock &basicBlock;
};

} // namespace llvm
#endif // CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
