//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
#include <chiisai-llvm/value.h>
namespace llvm {

struct User : Value {
  explicit User(const std::string &name, CRef<Type> type) : Value(name, type) {}
private:
  friend struct Module;

  friend void addUse(Ref<User> user, Ref<Value> value);
  mystl::poly_view_list<Value> m_usedValues{};
};

void addUse(Ref<User> user, Ref<Value> value);


}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
