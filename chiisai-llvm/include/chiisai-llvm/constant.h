//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_H
#include <chiisai-llvm/user.h>
namespace llvm {

struct Constant : User {
  Constant(const std::string &name, CRef<Type> type) : User(name, type) {}
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_CONSTANT_H
