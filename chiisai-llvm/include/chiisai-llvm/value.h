//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
#include <string>
#include <format>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/mystl/poly_list.h>
#include <minilog/logger.h>
namespace llvm {

struct User;
struct Executor;
struct Value : RAII, Executable {
  explicit Value(const std::string& name, CRef<Type> type) : m_name(name), m_type(type) {}
  [[nodiscard]] auto type() const {
    return m_type;
  }
  [[nodiscard]] const std::string& name() const {
    return m_name;
  }
  auto& users() {
    return m_users;
  }
  void replaceAllUsesWith(Ref<Value> other);
  void accept(Executor& executor) override {
    minilog::warn("value shouldn't be executed for class that inherits from Value");
  }
  ~Value() override = default;
private:
  friend struct Module;
  friend void addUse(Ref<User> user, Ref<Value> value);
  mystl::poly_view_list<User> m_users{};
  CRef<Type> m_type{};
  std::string m_name{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
