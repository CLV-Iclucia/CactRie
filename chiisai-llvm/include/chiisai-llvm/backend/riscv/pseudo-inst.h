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

enum class InstDetail {
  Byte,
  Half,
  Word,
  Double,
  Float,
};

struct RiscvPseudoBinary {
  std::string result{};
  std::string lhs{};
  std::string rhs{};
  Instruction::BinaryOps op{};
  InstDetail detail{};
};

struct RiscvPseudoCmp {
  std::string lhs{};
  std::string rhs{};
  std::string dest{};
  InstDetail detail{};
  Predicate predicate;
};

struct RiscvPseudoLoad {
  std::string base{};
  std::string offset{};
  std::string dest{};
  InstDetail detail{};
};

struct RiscvPseudoStore {
  std::string base{};
  std::string offset{};
  std::string value{};
  InstDetail detail{};
};

struct PseudoMove {
  std::string dest{};
  std::string src{};
};

using PseudoInstruction = std::variant<RiscvPseudoBinary, RiscvPseudoCmp, RiscvPseudoLoad,
                                       RiscvPseudoStore, PseudoMove>;

inline bool isMove(const PseudoInstruction &inst) {
  return std::holds_alternative<PseudoMove>(inst);
}

} // namespace llvm
#endif // PSEUDO_INST_H
