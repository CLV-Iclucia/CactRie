//
// Created by creeper on 12/18/24.
//

#ifndef PSEUDO_INST_H
#define PSEUDO_INST_H
#include <chiisai-llvm/backend/riscv/utils.h>
#include <chiisai-llvm/instruction.h>
#include <cstdint>
#include <string>
#include <variant>

namespace llvm {
// Pseudo instructions are instructions that use infinite number of registers
// and use riscv instruction structure to represent them
// 'mov' instruction, which is not directly supported by riscv, is also a pseudo
// instruction after register allocation, pseudo instructions become real
// instructions

enum class InstModifier : uint8_t {
  None,
  Byte,
  Half,
  Word,
  Double,
  Float,
};

enum class RiscvPredicate : uint8_t {
  EQ,
  NE,
  GT,
  GE,
  LT,
  LE,
};

enum class RiscvBinaryOps : uint8_t {
  Add,
  Sub,
  Mul,
  Div,
  Rem,
  And,
  Or,
  Xor,
  Shl,
  Shr,
  Sar,
};

struct RiscvPseudoBinary {
  std::string result{};
  std::string lhs{};
  std::string rhs{};
  Instruction::BinaryOps op{};
  InstModifier modifier{};
};

struct RiscvPseudoCmp {
  std::string lhs{};
  std::string rhs{};
  std::string dest{};
  RiscvPredicate predicate;
  InstModifier modifier{};
};

struct RiscvPseudoLoad {
  std::string base{};
  uint32_t offset{};
  std::string dest{};
  InstModifier modifier{};
};

struct RiscvPseudoStore {
  std::string base{};
  uint32_t offset{};
  std::string value{};
  InstModifier modifier{};
};

struct RiscvPseudoMove {
  std::string dest{};
  std::string src{};
  InstModifier modifier{};
};

struct RiscvPseudoJump {
  std::string cond{}; // if cond is empty string, it is an unconditional jump
  std::string trueLabel{};
};

struct RiscvPseudoCall {
  std::string result{};
  std::string func{};
  std::vector<std::string> args{};
};

struct RiscvPseudoRet {
  std::string value{};
};

struct RiscvLoadGlobal {
  std::string dest{};
  std::string global{};
};

using RiscvPseudoInstruction =
    std::variant<RiscvPseudoBinary, RiscvPseudoCmp, RiscvPseudoLoad,
                 RiscvPseudoStore, RiscvPseudoMove, RiscvPseudoCall,
                 RiscvPseudoRet, RiscvPseudoJump, RiscvLoadGlobal, std::string>;

inline bool isMove(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoMove>(inst);
}

inline bool isBinary(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoBinary>(inst);
}

inline bool isCmp(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoCmp>(inst);
}

inline bool isLoad(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoLoad>(inst);
}

inline bool isStore(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoStore>(inst);
}

inline bool isJump(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoJump>(inst);
}

inline bool isCall(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoCall>(inst);
}

inline bool isRet(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoRet>(inst);
}

inline bool isLabel(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<std::string>(inst);
}

inline bool isLoadGlobal(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvLoadGlobal>(inst);
}

template <typename... Fs> struct Overload : Fs... {
  using Fs::operator()...;
};

template <typename... Fs> Overload(Fs...) -> Overload<Fs...>;

template <typename Func>
void forUsedRegs(const RiscvPseudoInstruction &inst, Func &&func) {
  std::visit(Overload{
                 [&](const RiscvPseudoBinary &bin) {
                   if (!isConstant(bin.lhs))
                     func(bin.lhs);
                   if (isConstant(bin.rhs))
                     return;
                   func(bin.rhs);
                 },
                 [&](const RiscvPseudoCmp &cmp) {
                   if (!isConstant(cmp.lhs))
                     func(cmp.lhs);
                   if (isConstant(cmp.rhs))
                     return;
                   func(cmp.rhs);
                 },
                 [&](const RiscvPseudoLoad &load) {
                   if (!isConstant(load.base))
                     func(load.base);
                 },
                 [&](const RiscvPseudoStore &store) {
                   if (!isConstant(store.base))
                     func(store.base);
                   if (isConstant(store.value))
                     return;
                   func(store.value);
                 },
                 [&](const RiscvPseudoMove &move) {
                   if (isConstant(move.src))
                     return;
                   func(move.src);
                 },
                 [&](const RiscvPseudoCall &call) {
                   for (const auto &arg : call.args) {
                     if (isConstant(arg))
                       continue;
                     func(arg);
                   }
                 },
                 [&](const RiscvPseudoJump &jump) {
                   if (jump.cond.empty())
                     return;
                   if (isConstant(jump.cond))
                     return;
                   func(jump.cond);
                 },
                 [&](const RiscvPseudoRet &ret) {
                   if (ret.value.empty())
                     return;
                   func(ret.value);
                 },
                 [&](const RiscvLoadGlobal &loadGlobal) {},
                 [&](const std::string &str) {},
             },
             inst);
}

template <typename Func>
void forDefinedRegs(const RiscvPseudoInstruction &inst, Func &&func) {
  std::visit(Overload{
                 [&](const RiscvPseudoBinary &bin) {
                   if (isConstant(bin.result))
                     return;
                   func(bin.result);
                 },
                 [&](const RiscvPseudoCmp &cmp) {
                   if (isConstant(cmp.dest))
                     return;
                   func(cmp.dest);
                 },
                 [&](const RiscvPseudoLoad &load) {
                   if (isConstant(load.dest))
                     return;
                   func(load.dest);
                 },
                 [&](const RiscvPseudoStore &store) {},
                 [&](const RiscvPseudoMove &move) {
                   if (isConstant(move.dest))
                     return;
                   func(move.dest);
                 },
                 [&](const RiscvPseudoCall &call) {
                   if (call.result.empty())
                     return;
                   if (isConstant(call.result))
                     return;
                   func(call.result);
                 },
                 [&](const RiscvPseudoJump &jump) {},
                 [&](const RiscvPseudoRet &ret) {},
                 [&](const RiscvLoadGlobal &loadGlobal) {
                   if (isConstant(loadGlobal.dest))
                     return;
                   func(loadGlobal.dest);
                 },
                 [&](const std::string &str) {},
             },
             inst);
}

template <typename Func>
void forRegs(const RiscvPseudoInstruction &inst, Func &&func) {
  forUsedRegs(inst, func);
  forDefinedRegs(inst, func);
}

inline InstModifier getModifier(const RiscvPseudoInstruction &inst) {
  return std::visit(
      Overload{
          [](const RiscvPseudoBinary &bin) { return bin.modifier; },
          [](const RiscvPseudoCmp &cmp) { return cmp.modifier; },
          [](const RiscvPseudoLoad &load) { return load.modifier; },
          [](const RiscvPseudoStore &store) { return store.modifier; },
          [](const RiscvPseudoMove &move) { return move.modifier; },
          [](const RiscvPseudoCall &call) { return InstModifier::None; },
          [](const RiscvPseudoRet &ret) { return InstModifier::None; },
          [](const std::string &str) { return InstModifier::None; },
          [](const RiscvPseudoJump &jump) { return InstModifier::None; },
          [](const RiscvLoadGlobal &loadGlobal) { return InstModifier::None; },
      },
      inst);
}

} // namespace llvm
#endif // PSEUDO_INST_H
