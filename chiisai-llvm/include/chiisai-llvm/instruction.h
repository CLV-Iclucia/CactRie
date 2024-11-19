//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
#include <variant>
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/predicate.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/mystl/hash.h>
#include <chiisai-llvm/integer-type.h>

namespace llvm {

struct Instruction : User {
  explicit Instruction(uint8_t op, const std::string &name, CRef<Type> type, BasicBlock &basicBlock) :
      User(name, type), opCode(op), basicBlock(basicBlock) {}
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

  [[nodiscard]] const Function &function() const {
    return basicBlock.function();
  }
  [[nodiscard]] Function &function() {
    return basicBlock.function();
  }
  virtual uint64_t hash() const = 0;
  BasicBlock &basicBlock;
};

struct BinaryInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> lhs, rhs;
};

struct BinaryInst final : Instruction {
  explicit BinaryInst(uint8_t op, BasicBlock &basicBlock, const BinaryInstDetails &details) :
      Instruction(op, details.name, details.type, basicBlock), lhs(details.lhs), rhs(details.rhs) {
    assert(op >= Add && op < BinaryIDEnd);
  }

  Ref<Value> lhs, rhs;
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode = 0;
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, lhs->name());
    mystl::hash_combine(hashCode, rhs->name());
    return hashCode;
  }
};

struct AllocaInstDetails {
  const std::string &name;
  CRef<PointerType> type;
  size_t size;
  size_t alignment;
};

struct AllocaInst : Instruction {
  explicit AllocaInst(BasicBlock &basicBlock, const AllocaInstDetails &details) : Instruction(
      MemoryOps::Alloca, details.name, details.type, basicBlock), alignment(details.alignment) {}

  size_t alignment{};
  size_t size{};
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, alignment);
    return hashCode;
  }
};

struct MemInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> pointer;
};

struct StoreInst : Instruction {
  explicit StoreInst(BasicBlock &basicBlock, const MemInstDetails &details) : Instruction(MemoryOps::Store,
                                                                                          details.name,
                                                                                          details.type,
                                                                                          basicBlock),
                                                                              pointer(details.pointer) {
    assert(pointer->type()->isPointer());
  }
  Ref<Value> pointer;
  Ref<Value> value;
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, pointer->name());
    return hashCode;
  }
};

struct LoadInst : Instruction {
  explicit LoadInst(BasicBlock &basicBlock, const MemInstDetails &details) : Instruction(MemoryOps::Load,
                                                                                         details.name,
                                                                                         details.type,
                                                                                         basicBlock),
                                                                             pointer(details.pointer) {
    assert(pointer->type()->isPointer());
  }
  Ref<Value> pointer;
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, pointer->name());
    return hashCode;
  }
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

struct PhiInst final : Instruction {
  explicit PhiInst(BasicBlock &basicBlock, const PhiInstDetails &details) : Instruction(Instruction::OtherOps::Phi,
                                                                                        details.name,
                                                                                        details.type,
                                                                                        basicBlock),
                                                                            incomingValues(details.incomingValues) {}
  std::vector<PhiValue> incomingValues;
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    for (auto [basicBlock, val] : incomingValues) {
      mystl::hash_combine(hashCode, basicBlock->name());
      mystl::hash_combine(hashCode, val->name());
    }
    return hashCode;
  }
};

struct CallInstDetails {
  std::string name;
  CRef<Type> type;
  Function &function;
  const std::vector<std::string> &realArgs;
};

struct CallInst : Instruction {
  explicit CallInst(BasicBlock &basicBlock, const CallInstDetails &details)
      : Instruction(Instruction::OtherOps::Call,
                    details.name,
                    details.type,
                    basicBlock),
        function(details.function), realArgs(details.realArgs) {}
  Function &function;
  std::vector<std::string> realArgs;
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override;
};

struct CmpInstDetails {
  const LLVMContext &ctx;
  const std::string &name;
  Ref<Value> lhs, rhs;
  Predicate predicate{};
};

struct CmpInst final : Instruction {
  explicit CmpInst(uint8_t op, BasicBlock &basicBlock, const CmpInstDetails &details)
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
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, lhs->name());
    mystl::hash_combine(hashCode, rhs->name());
    mystl::hash_combine(hashCode, predicate);
    return hashCode;
  }
};

struct BrInst : Instruction {
  struct Conditional {
    CRef<Value> cond;
    CRef<BasicBlock> thenBranch;
    CRef<BasicBlock> elseBranch;
  };
  [[nodiscard]] bool isConditional() const {
    return std::holds_alternative<Conditional>(dest);
  }
  [[nodiscard]] const BasicBlock &thenBranch() const {
    if (isConditional())
      return *std::get<Conditional>(dest).thenBranch;
    return *std::get<CRef<BasicBlock>>(dest);
  }
  [[nodiscard]] const BasicBlock &elseBranch() const {
    if (isConditional())
      return *std::get<Conditional>(dest).elseBranch;
    throw std::runtime_error("unconditional branch");
  }
  [[nodiscard]] const Value &cond() const {
    if (isConditional())
      return *std::get<Conditional>(dest).cond;
    throw std::runtime_error("unconditional branch");
  }
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, isConditional());
    if (isConditional()) {
      mystl::hash_combine(hashCode, cond().name());
      mystl::hash_combine(hashCode, thenBranch().name());
      mystl::hash_combine(hashCode, elseBranch().name());
    } else
      mystl::hash_combine(hashCode, std::get<CRef<BasicBlock>>(dest)->name());
    return hashCode;
  }
private:
  std::variant<Conditional, CRef<BasicBlock>> dest;
};

// we only support at most one index for now
struct GepInstDetails {
  const std::string &name;
  CRef<Type> type;
  Value& pointer;
  Ref<Value> index{};
};

struct GepInst : Instruction {
  explicit GepInst(BasicBlock &basicBlock, const GepInstDetails &details) : Instruction(MemoryOps::Gep,
                                                                                        details.name,
                                                                                        details.type,
                                                                                        basicBlock),
                                                                            pointer(details.pointer),
                                                                            index(details.index) {}
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, name());
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, pointer.name());
    if (index)
      mystl::hash_combine(hashCode, index->name());
    return hashCode;
  }
  void accept(Executor &executor) override;
  Ref<Value> index{};
  Value& pointer;
};

struct RetInst : Instruction {
  explicit RetInst(BasicBlock &basicBlock, CRef<Value> ret) : Instruction(TerminatorOps::Ret, {}, {}, basicBlock),
                                                              ret(ret) {}
  void accept(Executor &executor) override;
  [[nodiscard]] uint64_t hash() const override {
    uint64_t hashCode{};
    mystl::hash_combine(hashCode, opCode);
    mystl::hash_combine(hashCode, ret->name());
    return hashCode;
  }
  CRef<Value> ret{};
};

}
#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_LLVM_INSTRUCTIONS_H
