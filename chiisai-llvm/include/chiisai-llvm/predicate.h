//
// Created by creeper on 10/17/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PREDICATE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PREDICATE_H
#include <cstdint>
#include <string>
namespace llvm {
enum class Predicate : uint8_t {
  EQ,
  NE,
  OGT,
  OGE,
  OLT,
  OLE,
  SGT,
  SGE,
  SLT,
  SLE,
};

Predicate stopdct(const std::string &str);
std::string toString(Predicate predicate);
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PREDICATE_H
