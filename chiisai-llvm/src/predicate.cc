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
}