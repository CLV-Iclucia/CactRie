//
// Created by creeper on 10/17/24.
//
#include <chiisai-llvm/predicate.h>
#include <map>
#include <string>
namespace llvm {
Predicate stopdct(const std::string &str) {
  std::map<std::string, Predicate> mapping{
      {"eq", Predicate::EQ},   {"ne", Predicate::NE},   {"ugt", Predicate::OGT},
      {"uge", Predicate::OGE}, {"ult", Predicate::OLT}, {"ule", Predicate::OLE},
      {"sgt", Predicate::SGT}, {"sge", Predicate::SGE}, {"slt", Predicate::SLT},
      {"sle", Predicate::SLE}, {"oeq", Predicate::EQ},  {"one", Predicate::NE},
      {"ogt", Predicate::OGT}, {"oge", Predicate::OGE}, {"olt", Predicate::OLT},
      {"ole", Predicate::OLE}, {"ogt", Predicate::SGT}, {"oge", Predicate::SGE},
      {"olt", Predicate::SLT}, {"ole", Predicate::SLE},
  };
  return mapping.at(str);
}
std::string toString(Predicate predicate) {
  std::map<Predicate, std::string> mapping{
      {Predicate::EQ, "eq"},   {Predicate::NE, "ne"},   {Predicate::OGT, "ugt"},
      {Predicate::OGE, "uge"}, {Predicate::OLT, "ult"}, {Predicate::OLE, "ule"},
      {Predicate::SGT, "sgt"}, {Predicate::SGE, "sge"}, {Predicate::SLT, "slt"},
      {Predicate::SLE, "sle"},
  };
  return mapping.at(predicate);
}
} // namespace llvm