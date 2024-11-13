//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/user.h>
#include <minilog/logger.h>
#include <chiisai-llvm/value.h>

namespace llvm {
void addUse(Ref<User> user, Ref<Value> value) {
  static auto useDefLogger = minilog::createFileLogger("useDef.log", minilog::LogLevel::debug);
  if (user == nullptr)
    throw std::runtime_error("user is nullptr");
  if (value == nullptr)
    throw std::runtime_error("value is nullptr");
  user->m_usedValues.push_back(value);
  value->m_users.push_back(user);
  useDefLogger->debug("add use: {} -> {}", user->name(), value->name());
}
}