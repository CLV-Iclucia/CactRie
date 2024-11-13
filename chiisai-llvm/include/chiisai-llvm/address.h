//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
#include <variant>
#include <chiisai-llvm/value.h>
namespace llvm {

struct Address {
  Ref<Value> value;
  size_t index;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
