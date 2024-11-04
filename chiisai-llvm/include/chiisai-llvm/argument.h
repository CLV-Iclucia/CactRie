//
// Created by creeper on 10/13/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARGUMENT_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARGUMENT_H
#include <chiisai-llvm/value.h>
namespace llvm {

struct Argument : Value {
  explicit Argument(const std::string &name, CRef<Type> type) : Value(name, type) {}
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_ARGUMENT_H
