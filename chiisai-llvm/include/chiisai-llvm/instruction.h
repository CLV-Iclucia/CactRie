//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#include <variant>
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/predicate.h>
namespace llvm {

struct Instruction : User {
  explicit Instruction(uint8_t op, const std::string &name, CRef<Type> type, Ref<BasicBlock> basicBlock) :
      User(name, type), opCode(op), m_basicBlock(basicBlock) {}
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
    Alloca = static_cast<uint8_t>(LogicalOps::LogicalIDEnd),
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

  [[nodiscard]] bool isTerminator() const {
    return opCode < TerminatorIDEnd;
  }

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

  [[nodiscard]] bool isMemory() const {
    return opCode >= MemoryIDEnd;
  }

  [[nodiscard]] bool isReflexive() const {
    return opCode == And;
  }

  [[nodiscard]] bool isCommutative() const {
    return opCode == Add || opCode == Mul || opCode == And || opCode == Or;
  }

  static bool checkBinaryInstType(CRef<Value> lhs, CRef<Value> rhs) {
    if (lhs->type() != rhs->type())
      return false;
    if (!lhs->type()->isComputable())
      return false;
    return true;
  }

  [[nodiscard]] const BasicBlock &basicBlock() const {
    if (!m_basicBlock)
      throw std::runtime_error("access null basic block of an instruction");
    return *m_basicBlock;
  }

  [[nodiscard]] BasicBlock &basicBlock() {
    if (!m_basicBlock)
      throw std::runtime_error("access null basic block of an instruction");
    return *m_basicBlock;
  }

  [[nodiscard]] const Function &function() const {
    return basicBlock().function();
  }
  [[nodiscard]] Function &function() {
    return basicBlock().function();
  }

private:
  Ref<BasicBlock> m_basicBlock{};
};

struct BinaryInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> lhs, rhs;
};

struct BinaryInst : Instruction {
  explicit BinaryInst(uint8_t op, Ref<BasicBlock> basicBlock, const BinaryInstDetails &details) :
      Instruction(op, details.name, details.type, basicBlock), lhs(details.lhs), rhs(details.rhs) {
    assert(op >= Add && op < BinaryIDEnd);
  }

  Ref<Value> lhs, rhs;
  void accept(Executor &executor) override;
};

struct AllocaInst : Instruction {
  explicit AllocaInst(const std::string &name, CRef<Type> type, Ref<BasicBlock> basicBlock) : Instruction(
      MemoryOps::Alloca, name, type, basicBlock) {}
};

struct MemInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> pointer;
  size_t alignment;
};

struct StoreInst : Instruction {
  explicit StoreInst(Ref<BasicBlock> basicBlock, const MemInstDetails &details) : Instruction(MemoryOps::Store,
                                                                                              details.name,
                                                                                              details.type,
                                                                                              basicBlock),
                                                                                  pointer(details.pointer) {}
  Ref<Value> pointer;
  void accept(Executor &executor) override;
};

struct LoadInst : Instruction {
  explicit LoadInst(Ref<BasicBlock> basicBlock, const MemInstDetails &details) : Instruction(MemoryOps::Load,
                                                                                             details.name,
                                                                                             details.type,
                                                                                             basicBlock),
                                                                                 pointer(details.pointer) {}
  Ref<Value> pointer;
  void accept(Executor &executor) override;
};

struct PhiValue {
  Ref<BasicBlock> basicBlock;
  Ref<Value> value;
};

struct PhiInstDetails {
  const std::string &name;
  CRef<Type> type;
  std::vector<PhiValue> &&incomingValues;
};

struct PhiInst : Instruction {
  explicit PhiInst(Ref<BasicBlock> basicBlock, const PhiInstDetails &details) : Instruction(Instruction::OtherOps::Phi,
                                                                                            details.name,
                                                                                            details.type,
                                                                                            basicBlock),
                                                                                incomingValues(details.incomingValues) {}
  std::vector<PhiValue> incomingValues;
};

struct CallInstDetails {
  std::string name;
  CRef<Type> type;
  Ref<Function> function;
  const std::vector<std::string>& realArgs;
};

struct CallInst : Instruction {
  explicit CallInst(Ref<BasicBlock> basicBlock, const CallInstDetails &details)
      : Instruction(Instruction::OtherOps::Call,
                    details.name,
                    details.type,
                    basicBlock),
        function(details.function), realArgs(details.realArgs) {}
  Ref<Function> function;
  std::vector<std::string> realArgs;
  void accept(Executor &executor);
};

struct CmpInstDetails {
  const LLVMContext &ctx;
  const std::string &name;
  Ref<Value> lhs, rhs;
  Predicate predicate;
};

struct CmpInst : Instruction {
  explicit CmpInst(uint8_t op, Ref<BasicBlock> basicBlock, const CmpInstDetails &details)
      : Instruction(op, details.name, Type::boolType(details.ctx), basicBlock),
        predicate(details.predicate),
        lhs(details.lhs),
        rhs(details.rhs) {
    assert(lhs->type() == rhs->type());
    assert((op == OtherOps::ICmp && lhs->type()->isInteger())
               || (op == OtherOps::FCmp && lhs->type()->isFloatingPoint()));
  }

  Predicate predicate;
  Ref<Value> lhs, rhs;
};

}
#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
