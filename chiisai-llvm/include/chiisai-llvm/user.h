//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
#include <chiisai-llvm/value.h>
namespace llvm {

struct User : Value {
  explicit User(const std::string &name, CRef<Type> type) : Value(name, type) {}
  std::list<Ref<Value>> usedValues{};
private:
  friend struct Module;
  void replaceUseOfWith(Ref<Value> oldValue, Ref<Value> newValue);
  friend void addUse(Ref<User> user, Ref<Value> value);
};

void addUse(Ref<User> user, Ref<Value> value);
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
