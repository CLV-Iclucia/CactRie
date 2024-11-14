//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
#include <variant>
#include <chiisai-llvm/value.h>
namespace llvm {

struct ArrayAddress {
  Ref<Value> array{};
  size_t index{};
};

struct Address {
  std::variant<Ref<Value>, ArrayAddress> value;
  static Address fromValue(Ref<Value> value) {
    return Address{value};
  }
  static Address fromArray(Ref<Value> array, size_t index) {
    return {ArrayAddress{array, index}};
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_ADDRESS_H
