//
// Created by creeper on 12/18/24.
//

#ifndef PSEUDO_INST_H
#define PSEUDO_INST_H

namespace llvm {
// Pseudo instructions are instructions that use infinite number of registers
// and use riscv instruction structure to represent them
// 'mov' instruction, which is not directly supported by riscv, is also a pseudo
// instruction after register allocation, pseudo instructions become real
// instructions

enum class InstModifier : uint8_t {
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

struct PseudoMove {
  std::string dest{};
  std::string src{};
};

using PseudoInstruction =
    std::variant<RiscvPseudoBinary, RiscvPseudoCmp, RiscvPseudoLoad,
                 RiscvPseudoStore, PseudoMove>;

inline bool isMove(const PseudoInstruction &inst) {
  return std::holds_alternative<PseudoMove>(inst);
}

} // namespace llvm
#endif // PSEUDO_INST_H
