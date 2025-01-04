//
// Created by creeper on 12/31/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INSTRUCTIONS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INSTRUCTIONS_H
#include <chiisai-llvm/global-variable.h>

#include <chiisai-llvm/basic-block.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/instruction.h>
#include <variant>
namespace llvm {

struct BinaryInstDetails {
  const std::string &name;
  CRef<Type> type{};
  Ref<Value> lhs{}, rhs{};
};

struct BinaryInst final : Instruction {
  explicit BinaryInst(uint8_t op, BasicBlock &basicBlock,
                      const BinaryInstDetails &details)
      : Instruction(op, details.name, details.type, basicBlock) {
    addUse(makeRef(*this), details.lhs);
    m_lhs = makeRef(usedValues.back());
    addUse(makeRef(*this), details.rhs);
    m_rhs = makeRef(usedValues.back());
    assert(op >= Add && op < BinaryIDEnd);
  }

  [[nodiscard]] Ref<Value> lhs() const { return *m_lhs; }
  [[nodiscard]] Ref<Value> rhs() const { return *m_rhs; }
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    return std::format("{} = {} {} {}, {}", name(), inst2String(opCode),
                       type()->toString(), lhs()->name(), rhs()->name());
  }

private:
  Ref<Ref<Value>> m_lhs{}, m_rhs{};
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
        alignment(details.alignment), size(details.size) {}

  size_t alignment{0};
  size_t size{1};
  void accept(Executor &executor) override;
  [[nodiscard]] CRef<Type> holdType() const {
    assert(isa<PointerType>(type()));
    return cast<PointerType>(type())->elementType();
  }
  [[nodiscard]] std::string toString() const override {
    bool hasAlign = alignment != 0;
    auto allocaPart =
        size > 1
            ? std::format("alloca {}, i32 {}", holdType()->toString(), size)
            : std::format("alloca {}", holdType()->toString());
    return name() + " = " + allocaPart +
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
      : Instruction(Store, details.name, details.type, basicBlock) {
    addUse(makeRef(*this), details.pointer);
    m_pointer = makeRef(usedValues.back());
    addUse(makeRef(*this), details.value);
    m_value = makeRef(usedValues.back());
    if (details.index) {
      addUse(makeRef(*this), details.index);
      m_index = makeRef(usedValues.back());
    }
    assert(pointer()->type()->isConvertibleToPointer() ||
           isa<GlobalVariable>(pointer()));
  }

  [[nodiscard]] std::string toString() const override {
    if (index())
      return std::format("store {} {}, {} {}, i32 {}",
                         value()->type()->toString(), value()->name(),
                         pointer()->type()->toString(), pointer()->name(),
                         index()->name());
    return std::format("store {} {}, {} {}", value()->type()->toString(),
                       value()->name(), pointer()->type()->toString(),
                       pointer()->name());
  }

  void accept(Executor &executor) override;
  [[nodiscard]] Ref<Value> pointer() const { return *m_pointer; }
  [[nodiscard]] Ref<Value> value() const { return *m_value; }
  [[nodiscard]] Ref<Value> index() const {
    if (!m_index)
      return {};
    return *m_index;
  }

private:
  Ref<Ref<Value>> m_pointer;
  Ref<Ref<Value>> m_value;
  Ref<Ref<Value>> m_index{};
};

struct LoadInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Value> pointer;
  Ref<Value> index{};
};

struct LoadInst final : Instruction {
  explicit LoadInst(BasicBlock &basicBlock, const LoadInstDetails &details)
      : Instruction(Load, details.name, details.type, basicBlock) {
    addUse(makeRef(*this), details.pointer);
    m_pointer = makeRef(usedValues.back());
    if (details.index) {
      addUse(makeRef(*this), details.index);
      m_index = makeRef(usedValues.back());
    }

    assert(pointer()->type()->isConvertibleToPointer() ||
           isa<GlobalVariable>(pointer()));
  }

  [[nodiscard]] Ref<Value> pointer() const { return *m_pointer; }
  [[nodiscard]] Ref<Value> index() const {
    if (!m_index)
      return {};
    return *m_index;
  }

  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    if (index())
      return std::format("{} = load {} {}, i32 {}", name(),
                         pointer()->type()->toString(), pointer()->name(),
                         index()->name());
    return std::format("{} = load {} {}", name(), pointer()->type()->toString(),
                       pointer()->name());
  }

private:
  Ref<Ref<Value>> m_pointer;
  Ref<Ref<Value>> m_index{};
};

struct PhiValue {
  Ref<Value> basicBlock{};
  Ref<Value> value{};
};

struct PhiInstDetails {
  const std::string &name;
  CRef<Type> type;
  std::vector<PhiValue> &&incomingPhiValues;
};

struct PhiInst final : Instruction {
  explicit PhiInst(BasicBlock &basicBlock, const PhiInstDetails &details)
      : Instruction(Phi, details.name, details.type, basicBlock) {
    for (auto [bb, value] : details.incomingPhiValues)
      addPhiValue(bb, value);
  }
  std::vector<Ref<Value>> incomingValues{};
  std::vector<Ref<Value>> incomingBlocks{};
  void accept(Executor &executor) override;
  void addPhiValue(Ref<Value> bb, Ref<Value> value) {
    addUse(makeRef(*this), bb);
    incomingBlocks.emplace_back(bb);
    addUse(makeRef(*this), value);
    incomingValues.emplace_back(value);
  }
  [[nodiscard]] std::string toString() const override;
};

struct CallInstDetails {
  const std::string &name;
  CRef<Type> type;
  Ref<Function> function;
  std::vector<Ref<Value>> &&realArgs;
};

struct CallInst final : Instruction {
  explicit CallInst(BasicBlock &basicBlock, const CallInstDetails &details)
      : Instruction(Call, details.name, details.type, basicBlock) {
    addUse(makeRef(*this), details.function);
    m_function = makeRef(usedValues.back());
    for (auto &arg : details.realArgs) {
      addUse(makeRef(*this), arg);
      m_realArgs.emplace_back(makeRef(usedValues.back()));
    }
  }
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override;
  [[nodiscard]] Ref<Function> function() const {
    assert(isa<Function>(*m_function));
    return cast<Function>(*m_function);
  }
  [[nodiscard]] auto realArgs() const {
    return m_realArgs | std::views::transform([](Ref<Ref<Value>> arg) {
             assert(arg);
             assert(*arg);
             return *arg;
           });
  }

private:
  Ref<Ref<Value>> m_function;
  std::vector<Ref<Ref<Value>>> m_realArgs{};
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
        predicate(details.predicate) {
    addUse(makeRef(*this), details.lhs);
    m_lhs = makeRef(usedValues.back());
    addUse(makeRef(*this), details.rhs);
    m_rhs = makeRef(usedValues.back());

    assert(lhs()->type() == rhs()->type());
    assert((op == OtherOps::ICmp && lhs()->type()->isInteger()) ||
           (op == OtherOps::FCmp && lhs()->type()->isFloatingPoint()));
  }

  [[nodiscard]] Ref<Value> lhs() const { return *m_lhs; }
  [[nodiscard]] Ref<Value> rhs() const { return *m_rhs; }

  Predicate predicate;
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override;

private:
  Ref<Ref<Value>> m_lhs, m_rhs;
};

struct BrInstDetails {
  Ref<Value> cond;
  Ref<BasicBlock> thenBranch;
  Ref<BasicBlock> elseBranch;
};

std::string genBrInstName();

struct BrInst final : Instruction {
  struct Conditional {
    Ref<Ref<Value>> cond;
    Ref<Ref<Value>> thenBranch;
    Ref<Ref<Value>> elseBranch;
  };
  explicit BrInst(BasicBlock &current, Ref<BasicBlock> destBlock)
      : Instruction(Br, genBrInstName(), {}, current) {
    addUse(makeRef(*this), destBlock);
    dest = makeRef(usedValues.back());
  }
  explicit BrInst(BasicBlock &current, const BrInstDetails &details)
      : Instruction(Br, genBrInstName(), {}, current) {
    Conditional cond;
    addUse(makeRef(*this), details.cond);
    cond.cond = makeRef(usedValues.back());
    addUse(makeRef(*this), details.thenBranch);
    cond.thenBranch = makeRef(usedValues.back());
    addUse(makeRef(*this), details.elseBranch);
    cond.elseBranch = makeRef(usedValues.back());
    dest = cond;
  }

  [[nodiscard]] bool isConditional() const {
    return std::holds_alternative<Conditional>(dest);
  }
  [[nodiscard]] BasicBlock &thenBranch() const {
    if (isConditional())
      return *cast<BasicBlock>(*std::get<Conditional>(dest).thenBranch);
    return *cast<BasicBlock>(*std::get<Ref<Ref<Value>>>(dest));
  }
  [[nodiscard]] BasicBlock &elseBranch() const {
    if (isConditional())
      return *cast<BasicBlock>(*std::get<Conditional>(dest).elseBranch);
    throw std::runtime_error(
        "unconditional branch doesn't support elseBranch()");
  }
  [[nodiscard]] const Value &cond() const {
    if (isConditional())
      return **std::get<Conditional>(dest).cond;
    throw std::runtime_error("unconditional branch doesn't support cond()");
  }
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override;

private:
  std::variant<Conditional, Ref<Ref<Value>>> dest;
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
      : Instruction(Gep, details.name, details.type, basicBlock) {
    addUse(makeRef(*this), details.pointer);
    m_pointer = makeRef(usedValues.back());
    if (details.index) {
      addUse(makeRef(*this), details.index);
      m_index = makeRef(usedValues.back());
    }
  }

  void accept(Executor &executor) override;
  [[nodiscard]] CRef<Type> holdType() const {
    assert(isa<PointerType>(type()));
    return cast<PointerType>(type())->elementType();
  }
  [[nodiscard]] std::string toString() const override {
    if (!index())
      return std::format("{} = getelementptr {}, {} {}", name(),
                         holdType()->toString(), pointer()->type()->toString(),
                         pointer()->name());
    return std::format("{} = getelementptr {}, {} {}, i32 {}", name(),
                       holdType()->toString(), pointer()->type()->toString(),
                       pointer()->name(), index()->name());
  }

  [[nodiscard]] Ref<Value> pointer() const { return *m_pointer; }
  [[nodiscard]] Ref<Value> index() const {
    if (!m_index)
      return {};
    return *m_index;
  }

private:
  Ref<Ref<Value>> m_index{};
  Ref<Ref<Value>> m_pointer;
};

std::string genReturnInstName();

struct RetInst final : Instruction {
  explicit RetInst(BasicBlock &basicBlock, Ref<Value> ret)
      : Instruction(Ret, {}, {}, basicBlock) {
    if (ret) {
      addUse(makeRef(*this), ret);
      this->m_ret = makeRef(usedValues.back());
    }
  }
  void accept(Executor &executor) override;
  [[nodiscard]] std::string toString() const override {
    if (!ret())
      return "ret void";
    return std::format("ret {} {}", ret()->type()->toString(), ret()->name());
  }

  [[nodiscard]] Ref<Value> ret() const {
    if (!m_ret)
      return {};
    return *m_ret;
  }

private:
  Ref<Ref<Value>> m_ret{};
};

} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INSTRUCTIONS_H
