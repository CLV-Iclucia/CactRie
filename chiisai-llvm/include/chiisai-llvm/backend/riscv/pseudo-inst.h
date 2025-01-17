//
// Created by creeper on 12/18/24.
//

#ifndef PSEUDO_INST_H
#define PSEUDO_INST_H

#include <chiisai-llvm/backend/riscv/utils.h>
#include <chiisai-llvm/instruction.h>
#include <cstdint>
#include <map>
#include <sstream>
#include <string>
#include <variant>

namespace llvm {
// Pseudo instructions are instructions that use infinite number of registers
// and use riscv instruction structure to represent them

enum class RiscvPredicate : uint8_t { FEQ, LT, FLT, FLE };

inline std::string toString(RiscvPredicate pred) {
  switch (pred) {
  case RiscvPredicate::LT:
    return "<";
  case RiscvPredicate::FEQ:
    return "==";
  case RiscvPredicate::FLT:
    return "<";
  case RiscvPredicate::FLE:
    return "<=";
  default:
    throw std::runtime_error("unsupported riscv predicate");
  }
}

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
};

inline std::string toString(RiscvBinaryOps op) {
  switch (op) {
  case RiscvBinaryOps::Add:
    return "+";
  case RiscvBinaryOps::Sub:
    return "-";
  case RiscvBinaryOps::Mul:
    return "*";
  case RiscvBinaryOps::Div:
    return "/";
  case RiscvBinaryOps::Rem:
    return "%";
  case RiscvBinaryOps::And:
    return "&";
  case RiscvBinaryOps::Or:
    return "|";
  case RiscvBinaryOps::Xor:
    return "^";
  case RiscvBinaryOps::Shl:
    return "<<";
  case RiscvBinaryOps::Shr:
    return ">>";
  default:
    throw std::runtime_error("unsupported riscv binary operation");
  }
}

struct RiscvPseudoBinary {
  std::string result{};
  std::string lhs{};
  std::string rhs{};
  RiscvBinaryOps op{};
};

struct RiscvPseudoCmp {
  std::string lhs{};
  std::string rhs{};
  std::string dest{};
  RiscvPredicate predicate;
};

struct RiscvPseudoLoad {
  std::string base{};
  uint32_t offset{};
  std::string dest{};
};

struct RiscvPseudoStore {
  std::string base{};
  uint32_t offset{};
  std::string value{};
};

struct RiscvPseudoMove {
  std::string dest{};
  std::string src{};
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

struct RiscvPseudoAlloca {
  std::string result{};
};

struct RiscvPseudoEqz {
  std::string dest{};
  std::string src{};
  bool isEqz{};
};

using RiscvPseudoInstruction =
    std::variant<RiscvPseudoBinary, RiscvPseudoCmp, RiscvPseudoLoad,
                 RiscvPseudoStore, RiscvPseudoMove, RiscvPseudoCall,
                 RiscvPseudoRet, RiscvPseudoJump, RiscvPseudoAlloca,
                 RiscvLoadGlobal, RiscvPseudoEqz>;

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

inline bool isLoadGlobal(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvLoadGlobal>(inst);
}

inline bool isAlloca(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoAlloca>(inst);
}

inline bool isEqz(const RiscvPseudoInstruction &inst) {
  return std::holds_alternative<RiscvPseudoEqz>(inst);
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
                   if (isConstant(ret.value))
                     return;
                   func(ret.value);
                 },
                 [&](const RiscvPseudoEqz &eqz) {
                   if (isConstant(eqz.src))
                     return;
                   func(eqz.src);
                 },
                 [&](const RiscvLoadGlobal &loadGlobal) {},
                 [&](const RiscvPseudoAlloca &alloca) {},
             },
             inst);
}

template <typename Func>
void forDefinedRegs(const RiscvPseudoInstruction &inst, Func &&func) {
  std::visit(Overload{[&](const RiscvPseudoBinary &bin) {
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
                      [&](const RiscvPseudoAlloca &alloca) {
                        if (isConstant(alloca.result))
                          return;
                        func(alloca.result);
                      },
                      [&](const RiscvPseudoEqz &eqz) {
                        if (isConstant(eqz.dest))
                          return;
                        func(eqz.dest);
                      }},
             inst);
}

template <typename Func>
void forRegs(const RiscvPseudoInstruction &inst, Func &&func) {
  forUsedRegs(inst, func);
  forDefinedRegs(inst, func);
}

inline std::string toString(const RiscvPseudoInstruction &pseudoInst) {
  return std::visit(
      Overload{
          [](const RiscvPseudoBinary &bin) {
            return std::format("{} = {} {} {}", bin.result, bin.lhs,
                               toString(bin.op), bin.rhs);
          },
          [](const RiscvPseudoCmp &cmp) {
            return std::format("{} = {} {} {}", cmp.dest, cmp.lhs,
                               toString(cmp.predicate), cmp.rhs);
          },
          [](const RiscvPseudoLoad &load) {
            return std::format("{} = load {}({})", load.dest, load.offset,
                               load.base);
          },
          [](const RiscvPseudoStore &store) {
            return std::format("store {} {}({})", store.value, store.offset,
                               store.base);
          },
          [](const RiscvPseudoMove &move) {
            return std::format("{} = {}", move.dest, move.src);
          },
          [](const RiscvPseudoJump &jump) {
            if (jump.cond.empty())
              return "jump " + jump.trueLabel;
            return std::format("if ({}) jump {}", jump.cond, jump.trueLabel);
          },
          [](const RiscvPseudoCall &call) {
            std::stringstream ss;
            if (!call.result.empty())
              ss << call.result << " = ";
            ss << call.func << "(";
            for (int i = 0; i < call.args.size(); i++) {
              ss << call.args[i];
              if (i != call.args.size() - 1)
                ss << ", ";
            }
            ss << ")";
            return ss.str();
          },
          [](const RiscvPseudoRet &ret) {
            return ret.value.empty() ? "ret" : "ret " + ret.value;
          },
          [](const RiscvLoadGlobal &loadGlobal) {
            return loadGlobal.dest + " = la " + loadGlobal.global;
          },
          [](const RiscvPseudoAlloca &alloca) {
            return alloca.result + " = alloca";
          },
          [](const RiscvPseudoEqz &eqz) {
            if (eqz.isEqz)
              return std::format("{} = {} == 0", eqz.dest, eqz.src);
            return std::format("{} = {} != 0", eqz.dest, eqz.src);
          },
      },
      pseudoInst);
}

struct PseudoInstructionSequence {
  std::vector<RiscvPseudoInstruction> insts{};
  std::map<int32_t, std::string> labels{};
};

inline std::string toString(const PseudoInstructionSequence &seq) {
  std::stringstream ss;
  for (int i = 0; i < seq.insts.size(); i++) {
    if (seq.labels.contains(i))
      ss << "." << seq.labels.at(i) << ":\n";
    ss << i << " " << toString(seq.insts[i]) << "\n";
  }
  return ss.str();
}
inline std::string toIndexedString(const PseudoInstructionSequence &seq) {
  std::stringstream ss;
  for (int i = 0; i < seq.insts.size(); i++) {
    if (seq.labels.contains(i))
      ss << "." << seq.labels.at(i) << ":\n";
    ss << i << " " << toString(seq.insts[i]) << "\n";
  }
  return ss.str();
}
} // namespace llvm
#endif // PSEUDO_INST_H
