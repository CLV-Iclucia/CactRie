//
// Created by creeper on 12/31/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INSTRUCTIONS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INSTRUCTIONS_H
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/basic-block.h>
#include <variant>
namespace llvm {

struct BinaryInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> lhs, rhs;
};

struct BinaryInst final : Instruction {
  explicit BinaryInst(uint8_t op, BasicBlock &basicBlock,
                      const BinaryInstDetails &details)
      : Instruction(op, details.name, details.type, basicBlock),
        lhs(details.lhs), rhs(details.rhs) {
    assert(op >= Add && op < BinaryIDEnd);
  }

  Ref<Value> lhs, rhs;
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    return std::format("{} = {} {} {}, {}", name(), inst2String(opCode),
                       type()->toString(), lhs->name(), rhs->name());
  }
};

struct AllocaInstDetails {
  const std::string &name;
  CRef<PointerType> type;
  size_t size = 1;
  size_t alignment = 0;
};

struct AllocaInst final : Instruction {
  explicit AllocaInst(BasicBlock &basicBlock, const AllocaInstDetails &details)
      : Instruction(Alloca, details.name, details.type, basicBlock),
        alignment(details.alignment) {}

  size_t alignment{0};
  size_t size{1};
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    bool hasAlign = alignment != 0;
    auto allocaPart =
        size > 1 ? std::format("alloca {} {}", type()->toString(), size)
                 : std::format("alloca {}", type()->toString());
    return "{} = " + allocaPart +
           (hasAlign ? std::format(", align {}", alignment) : "");
  }
};

struct StoreInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> pointer;
  Ref<Value> value;
  Ref<Value> index{};
};

struct StoreInst final : Instruction {
  explicit StoreInst(BasicBlock &basicBlock, const StoreInstDetails &details)
      : Instruction(Store, details.name, details.type, basicBlock),
        pointer(details.pointer), value(details.value), index(details.index) {
    assert(pointer->type()->isConvertibleToPointer());
  }
  Ref<Value> pointer;
  Ref<Value> value;
  Ref<Value> index{};
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    if (index)
      return std::format("store {} {}, {} {}, i32 {}", value->type()->toString(),
                         value->name(), pointer->type()->toString(),
                         pointer->name(), index->name());
    return std::format("store {} {}, {} {}", value->type()->toString(),
                       value->name(), pointer->type()->toString(),
                       pointer->name());
  }
};

struct LoadInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> pointer;
  Ref<Value> index{};
};

struct LoadInst final : Instruction {
  explicit LoadInst(BasicBlock &basicBlock, const LoadInstDetails &details)
      : Instruction(Load, details.name, details.type, basicBlock),
        pointer(details.pointer), index(details.index) {
    assert(pointer->type()->isConvertibleToPointer());
  }
  Ref<Value> pointer;
  Ref<Value> index{};
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    if (index)
      return std::format("{} = load {} {}, i32 {}", name(),
                         pointer->type()->toString(), pointer->name(),
                         index->name());
    return std::format("{} = load {} {}", name(), pointer->type()->toString(),
                       pointer->name());
  }
};

struct PhiValue {
  Ref<BasicBlock> basicBlock{};
  Ref<Value> value{};
};

struct PhiInstDetails {
  const std::string &name;
  CRef<Type> type;
  std::vector<PhiValue> &&incomingValues;
};

struct PhiInst final : Instruction {
  explicit PhiInst(BasicBlock &basicBlock, const PhiInstDetails &details)
      : Instruction(Phi, details.name, details.type, basicBlock),
        incomingValues(details.incomingValues) {}
  std::vector<PhiValue> incomingValues;
  void accept(Executor &executor) override;

  void removeBranch(const std::string &blockName);
  [[nodiscard]] std::string toString() const override;
};

struct CallInstDetails {
  std::string name;
  CRef<Type> type;
  Function &function;
  std::vector<Ref<Value>> &&realArgs;
};

struct CallInst final : Instruction {
  explicit CallInst(BasicBlock &basicBlock, const CallInstDetails &details)
      : Instruction(Call, details.name, details.type, basicBlock),
        function(details.function), realArgs(details.realArgs) {}
  Function &function;
  std::vector<Ref<Value>> realArgs{};
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override;
};

struct CmpInstDetails {
  const LLVMContext &ctx;
  const std::string &name;
  Ref<Value> lhs, rhs;
  Predicate predicate{};
};

struct CmpInst final : Instruction {
  explicit CmpInst(uint8_t op, BasicBlock &basicBlock,
                   const CmpInstDetails &details)
      : Instruction(op, details.name, Type::boolType(details.ctx), basicBlock),
        predicate(details.predicate), lhs(details.lhs), rhs(details.rhs) {
    assert(lhs->type() == rhs->type());
    assert((op == OtherOps::ICmp && lhs->type()->isInteger()) ||
           (op == OtherOps::FCmp && lhs->type()->isFloatingPoint()));
  }

  Predicate predicate;
  Ref<Value> lhs, rhs;
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override;
};

struct BrInstDetails {
  Ref<Value> cond;
  Ref<BasicBlock> thenBranch;
  Ref<BasicBlock> elseBranch;
};

std::string genBrInstName();

struct BrInst final : Instruction {
  struct Conditional {
    Ref<Value> cond;
    Ref<BasicBlock> thenBranch;
    Ref<BasicBlock> elseBranch;
  };
  explicit BrInst(BasicBlock &current, Ref<BasicBlock> dest)
      : Instruction(Br, genBrInstName(), {}, current), dest(dest) {}
  explicit BrInst(BasicBlock &current, const BrInstDetails &details)
      : Instruction(Br, genBrInstName(), {}, current),
        dest(Conditional{details.cond, details.thenBranch,
                         details.elseBranch}) {}

  [[nodiscard]] bool isConditional() const {
    return std::holds_alternative<Conditional>(dest);
  }
  [[nodiscard]] const BasicBlock &thenBranch() const {
    if (isConditional())
      return *std::get<Conditional>(dest).thenBranch;
    return *std::get<Ref<BasicBlock>>(dest);
  }
  BasicBlock &thenBranch() {
    if (isConditional())
      return *std::get<Conditional>(dest).thenBranch;
    return *std::get<Ref<BasicBlock>>(dest);
  }
  [[nodiscard]] const BasicBlock &elseBranch() const {
    if (isConditional())
      return *std::get<Conditional>(dest).elseBranch;
    throw std::runtime_error(
        "unconditional branch doesn't support elseBranch()");
  }
  [[nodiscard]] const Value &cond() const {
    if (isConditional())
      return *std::get<Conditional>(dest).cond;
    throw std::runtime_error("unconditional branch doesn't support cond()");
  }
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override;

private:
  std::variant<Conditional, Ref<BasicBlock>> dest;
};

// we only support at most one index for now
struct GepInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> pointer;
  Ref<Value> index{};
};

struct GepInst final : Instruction {
  explicit GepInst(BasicBlock &basicBlock, const GepInstDetails &details)
      : Instruction(Gep, details.name, details.type, basicBlock),
        index(details.index), pointer(details.pointer) {}

  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    if (!index)
      return std::format("{} = getelementptr {} {}", name(),
                         pointer->type()->toString(), pointer->name());
    return std::format("{} = getelementptr {} {}, i32 {}", name(),
                       pointer->type()->toString(), pointer->name(),
                       index->name());
  }
  Ref<Value> index{};
  Ref<Value> pointer;
};

std::string genReturnInstName();

struct RetInst final : Instruction {
  explicit RetInst(BasicBlock &basicBlock, Ref<Value> ret)
      : Instruction(Ret, {}, {}, basicBlock), ret(ret) {}
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    if (!ret)
      return "ret void";
    return std::format("ret {} {}", ret->type()->toString(), ret->name());
  }
  Ref<Value> ret{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INSTRUCTIONS_H
