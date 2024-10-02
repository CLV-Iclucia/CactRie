//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
#include <string>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/mystl/poly_list.h>
namespace llvm {

struct User;

struct Value : RAII {
  auto type() {
    return m_type;
  }
  std::string_view name() {
    return m_name;
  }
  auto& users() {
    return m_users;
  }
  virtual ~Value() = default;
private:
  mystl::poly_list<User> m_users{};
  CRef<Type> m_type{};
  std::string m_name{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
