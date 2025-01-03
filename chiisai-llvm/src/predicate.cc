//
// Created by creeper on 10/17/24.
//
#include <chiisai-llvm/predicate.h>
#include <map>
#include <string>
namespace llvm {
Predicate stopdct(const std::string &str) {
  std::map<std::string, Predicate> mapping{
      {"eq", Predicate::EQ},   {"ne", Predicate::NE},   {"ugt", Predicate::UGT},
      {"uge", Predicate::UGE}, {"ult", Predicate::ULT}, {"ule", Predicate::ULE},
      {"sgt", Predicate::SGT}, {"sge", Predicate::SGE}, {"slt", Predicate::SLT},
      {"sle", Predicate::SLE}, {"oeq", Predicate::EQ},  {"one", Predicate::NE},
      {"ogt", Predicate::UGT}, {"oge", Predicate::UGE}, {"olt", Predicate::ULT},
      {"ole", Predicate::ULE}, {"ogt", Predicate::SGT}, {"oge", Predicate::SGE},
      {"olt", Predicate::SLT}, {"ole", Predicate::SLE},
  };
  return mapping.at(str);
}
std::string toString(Predicate predicate) {
  std::map<Predicate, std::string> mapping{
      {Predicate::EQ, "eq"},   {Predicate::NE, "ne"},   {Predicate::UGT, "ugt"},
      {Predicate::UGE, "uge"}, {Predicate::ULT, "ult"}, {Predicate::ULE, "ule"},
      {Predicate::SGT, "sgt"}, {Predicate::SGE, "sge"}, {Predicate::SLT, "slt"},
      {Predicate::SLE, "sle"},
  };
  return mapping.at(predicate);
}
} // namespace llvm