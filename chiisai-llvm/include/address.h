//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
#include <variant>
#include <chiisai-llvm/value.h>
namespace llvm {

struct ArrayAddress {

};

struct Address {
  std::variant<Ref<Value>, ArrayAddress> pointer;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
