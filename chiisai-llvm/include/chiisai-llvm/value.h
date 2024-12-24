//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
#include <string>
#include <format>
#include <mystl/poly_list.h>
#include <chiisai-llvm/type.h>
#include <minilog/logger.h>
namespace llvm {

struct User;
struct Executor;
struct Value : RAII, Executable {
  explicit Value(const std::string& name, CRef<Type> type) : m_type(type), m_name(name) {}
  [[nodiscard]] auto type() const {
    return m_type;
  }
  mystl::poly_view_list<User> users{};
  // after replacement no user will be using this value and this value should be deleted
  // we leave this work to the manager of the value
  void replaceAllUsesWith(Ref<Value> other);
  [[nodiscard]] bool isUsed() const {
    return !users.empty();
  }
  void accept(Executor& executor) override {
    minilog::warn("value shouldn't be executed for class that inherits from Value");
  }
  [[nodiscard]] const std::string& name() const {
    return m_name;
  }
  [[nodiscard]] uint64_t handle() const {
    return reinterpret_cast<uint64_t>(this);
  }
  ~Value() override = default;
private:
  friend struct Module;
  friend void addUse(Ref<User> user, Ref<Value> value);
  CRef<Type> m_type{};
  std::string m_name{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_VALUE_H
