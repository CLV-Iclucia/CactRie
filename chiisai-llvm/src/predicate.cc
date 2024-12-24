//
// Created by creeper on 10/17/24.
//
#include <map>
#include <string>
#include <chiisai-llvm/predicate.h>
namespace llvm {
Predicate stopdct(const std::string &str) {
  std::map<std::string, Predicate> mapping{
      {"eq", Predicate::EQ},
      {"ne", Predicate::NE},
      {"ugt", Predicate::UGT},
      {"uge", Predicate::UGE},
      {"ult", Predicate::ULT},
      {"ule", Predicate::ULE},
      {"sgt", Predicate::SGT},
      {"sge", Predicate::SGE},
      {"slt", Predicate::SLT},
      {"sle", Predicate::SLE},
  };
  return mapping.at(str);
}
std::string toString(Predicate predicate) {
  std::map<Predicate, std::string> mapping{
        {Predicate::EQ, "eq"},
        {Predicate::NE, "ne"},
        {Predicate::UGT, "ugt"},
        {Predicate::UGE, "uge"},
        {Predicate::ULT, "ult"},
        {Predicate::ULE, "ule"},
        {Predicate::SGT, "sgt"},
        {Predicate::SGE, "sge"},
        {Predicate::SLT, "slt"},
        {Predicate::SLE, "sle"},
    };
  return mapping.at(predicate);
}
}