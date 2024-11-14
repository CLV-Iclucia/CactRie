//
// Created by creeper on 11/3/24.
//
#include <functional>
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/basic-block.h>
namespace llvm {

void BinaryInst::accept(Executor &executor) {
  const auto &lhsReg = executor.reg(lhs->name());
  const auto &rhsReg = executor.reg(rhs->name());
  if (!lhsReg.canOperateWith(rhsReg))
    throw std::runtime_error("Binary instruction operands must have the same type and cannot be an address or a boolean");

  static std::unordered_map<BinaryOps, std::function<Result::Integer(Result::Integer, Result::Integer)>> intOps = {
      {Add, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 + arg2); }, lhs, rhs);
      }},
      {Sub, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 - arg2); }, lhs, rhs);
      }},
      {Mul, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 * arg2); }, lhs, rhs);
      }},
      {SDiv, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 / arg2); }, lhs, rhs);
      }},
      {SRem, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 % arg2); }, lhs, rhs);
      }},
      {Xor, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 ^ arg2); }, lhs, rhs);
      }},
      {Shl, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 << arg2); }, lhs, rhs);
      }},
      {LShr, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 >> arg2); }, lhs, rhs);
      }},
      {AShr, [](Result::Integer lhs, Result::Integer rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Integer(arg1 >> arg2); }, lhs, rhs);
      }},
  };

  static std::unordered_map<BinaryOps, std::function<Result::Floating(Result::Floating, Result::Floating)>> floatOps = {
      {FAdd, [](Result::Floating lhs, Result::Floating rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Floating(arg1 + arg2); }, lhs, rhs);
      }},
      {FSub, [](Result::Floating lhs, Result::Floating rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Floating(arg1 - arg2); }, lhs, rhs);
      }},
      {FMul, [](Result::Floating lhs, Result::Floating rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Floating(arg1 * arg2); }, lhs, rhs);
      }},
      {FDiv, [](Result::Floating lhs, Result::Floating rhs) {
        return std::visit([](auto arg1,
                             auto arg2) { return Result::Floating(arg1 / arg2); }, lhs, rhs);
      }},
  };

  if (isIntBinary())
    executor.reg(name()) = Result{intOps[static_cast<BinaryOps>(opCode)](lhsReg.toInteger(), rhsReg.toInteger())};
  else if (isFloatBinary())
    executor.reg(name()) = Result{floatOps[static_cast<BinaryOps>(opCode)](lhsReg.toFloating(), rhsReg.toFloating())};
  else
    throw std::runtime_error("What the fucking binary instruction is this?");
}

void StoreInst::accept(Executor &executor) {
  auto src = executor.reg(pointer->name());
  if (src.isPointer())
    throw std::runtime_error("Store instruction cannot store a pointer");

  auto srcPointer = std::get<Address>(src.value);
}

void LoadInst::accept(Executor &executor) {
  executor.reg(name()) = executor.reg(pointer->name());
}

void CallInst::accept(Executor &executor) {
  auto func = executor.module.function(function.name());
  executor.pushFrame();
  for (auto arg : func->args())
    executor.reg(arg->name()) = executor.reg(arg->name());
  executor.execute(func);
  executor.reg(name()) = executor.returnReg.value();
}

uint64_t CallInst::hash() const {
  uint64_t hashCode;
  mystl::hash_combine(hashCode, name());
  mystl::hash_combine(hashCode, opCode);
  mystl::hash_combine(hashCode, function.name());
  for (const auto &arg : realArgs)
    mystl::hash_combine(hashCode, arg);
  return hashCode;
}

void CmpInst::accept(Executor &executor) {
  static std::unordered_map<Predicate, std::function<bool(Result::Integer, Result::Integer)>> intPredicates = {
      {Predicate::EQ, [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::equal_to<>(), lhs, rhs); }},
      {Predicate::NE,
       [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::not_equal_to<>(), lhs, rhs); }},
      {Predicate::UGT, [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::greater<>(), lhs, rhs); }},
      {Predicate::UGE,
       [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::greater_equal<>(), lhs, rhs); }},
      {Predicate::ULT, [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::less<>(), lhs, rhs); }},
      {Predicate::ULE,
       [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::less_equal<>(), lhs, rhs); }},
      {Predicate::SGT, [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::greater<>(), lhs, rhs); }},
      {Predicate::SGE,
       [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::greater_equal<>(), lhs, rhs); }},
      {Predicate::SLT, [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::less<>(), lhs, rhs); }},
      {Predicate::SLE,
       [](Result::Integer lhs, Result::Integer rhs) { return std::visit(std::less_equal<>(), lhs, rhs); }},
  };

  static std::unordered_map<Predicate, std::function<bool(Result::Floating, Result::Floating)>> floatPredicates = {
      {Predicate::EQ,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::equal_to<>(), lhs, rhs); }},
      {Predicate::NE,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::not_equal_to<>(), lhs, rhs); }},
      {Predicate::UGT,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::greater<>(), lhs, rhs); }},
      {Predicate::UGE,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::greater_equal<>(), lhs, rhs); }},
      {Predicate::ULT, [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::less<>(), lhs, rhs); }},
      {Predicate::ULE,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::less_equal<>(), lhs, rhs); }},
      {Predicate::SGT,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::greater<>(), lhs, rhs); }},
      {Predicate::SGE,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::greater_equal<>(), lhs, rhs); }},
      {Predicate::SLT, [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::less<>(), lhs, rhs); }},
      {Predicate::SLE,
       [](Result::Floating lhs, Result::Floating rhs) { return std::visit(std::less_equal<>(), lhs, rhs); }},
  };

  const auto &lhsReg = executor.reg(lhs->name());
  const auto &rhsReg = executor.reg(rhs->name());

  if (!lhsReg.canOperateWith(rhsReg))
    throw std::runtime_error("Binary instruction operands must have the same type and cannot be an address or a boolean");

  if (isIntBinary())
    executor.reg(name()) = Result{intPredicates[predicate](lhsReg.toInteger(), rhsReg.toInteger())};
  else if (isFloatBinary())
    executor.reg(name()) = Result{floatPredicates[predicate](lhsReg.toFloating(), rhsReg.toFloating())};
  else
    throw std::runtime_error("What the fucking comparison instruction is this?");
}

void PhiInst::accept(Executor &executor) {
  const auto &incoming = executor.incomingBasicBlock;
  for (const auto &[bb, value] : incomingValues)
    if (bb->name() == incoming) {
      executor.reg(name()) = executor.reg(value->name());
      return;
    }
}

void BrInst::accept(Executor &executor) {
  if (isConditional()) {
    if (executor.reg(cond().name()).isBool()) {
      if (std::get<bool>(executor.reg(cond().name()).value))
        executor.execute(thenBranch());
      else
        executor.execute(elseBranch());
    } else
      throw std::runtime_error("Branch condition must be a boolean");
  } else
    executor.execute(std::get<CRef<BasicBlock>>(dest));
  executor.incomingBasicBlock = basicBlock.name();
}

void RetInst::accept(Executor &executor) {
  executor.returnReg = ret == nullptr ? std::nullopt : std::make_optional(executor.reg(ret->name()));
  executor.popFrame();
}
}