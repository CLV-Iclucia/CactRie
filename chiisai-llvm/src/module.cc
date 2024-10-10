//
// Created by creeper on 10/4/24.
//
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/module.h>

namespace llvm {

void Module::addUse(Ref<User> user, Ref<Value> value) {
  if (!valueMap.contains(user))
    throw std::runtime_error(std::format("Value {} is not registered in current LLVM context", user->name()));
  if (!valueMap.contains(value))
    throw std::runtime_error(std::format("Value {} is not registered in current LLVM context", value->name()));
  user->m_usedValues.push_back(value);
  value->m_users.push_back(user);
}
}