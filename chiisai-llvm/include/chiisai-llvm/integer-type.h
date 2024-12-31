//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INTEGER_TYPE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INTEGER_TYPE_H
#include <chiisai-llvm/type.h>

namespace llvm {

struct IntegerType final : Type {
  explicit IntegerType(size_t bitWidth) : Type(TypeEnum::Integer), m_bitWidth(bitWidth) {}
  [[nodiscard]]
  size_t bitWidth() const {
    return m_bitWidth;
  }
  [[nodiscard]] std::string toString() const override {
    return "i" + std::to_string(m_bitWidth);
  }
private:
  size_t m_bitWidth{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_INTEGER_TYPE_H
