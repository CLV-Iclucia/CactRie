//
// Created by creeper on 8/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LITERAL_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LITERAL_H
#include <variant>
namespace llvm {


enum class LLVMType {
  i1,
  i32,
  f32,
  f64,
};

template <LLVMType T>
struct TypeWrapper {};

template <>
struct TypeWrapper<LLVMType::i1> {
  using type = bool;
};

template <>
struct TypeWrapper<LLVMType::i32> {
  using type = int;
};

template <>
struct TypeWrapper<LLVMType::f32> {
  using type = float;
};

template <>
struct TypeWrapper<LLVMType::f64> {
  using type = double;
};

template <LLVMType T>
using Type = typename TypeWrapper<T>::type;

struct Literal {
  template <LLVMType T>
  Type<T>& value() {
    return std::get<Type<T>>(m_value);
  }

  template <LLVMType T>
  Type<T> value() const {
    return std::get<Type<T>>(m_value);
  }

protected:
  std::variant<bool, int, float, double> m_value;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_LITERAL_H
