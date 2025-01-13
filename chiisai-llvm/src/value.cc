//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/value.h>
#include <iostream>
#include <minilog/logger.h>
namespace llvm {
static auto usageReplacementLogger =
    minilog::createFileLogger("usage-replacement.log");
void Value::replaceAllUsesWith(Ref<Value> other) {
  assert(other.get() != this);
  for (auto user : users) {
    // let's do it in a brute force way!
    std::transform(user->usedValues.begin(), user->usedValues.end(),
                   user->usedValues.begin(), [=, this](Ref<Value> value) {
                     if (value.get() == this) {
                       usageReplacementLogger->info(
                           "replacing use {} -> {} to {} -> {}", user->name(),
                           name(), user->name(), other->name());
                       usageReplacementLogger->outStream().flush();
                       other->users.emplace_back(user);
                       return other;
                     }
                     return value;
                   });
  }

  for (auto &callback : replacementCallbacks)
    callback(other);
  users.clear();
}
void replaceUse(Ref<User> user, Ref<Value> value, Ref<Value> other) {
  value->users.remove(user);
  other->users.emplace_back(user);
  std::replace(user->usedValues.begin(), user->usedValues.end(), value, other);
}
} // namespace llvm