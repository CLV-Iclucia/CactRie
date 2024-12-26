//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/value.h>
#include <minilog/logger.h>
namespace llvm {
void Value::replaceAllUsesWith(Ref<Value> other) {
  static auto usageReplacementLogger =
      minilog::createFileLogger("usage-replacement.log");
  assert(other.get() != this);
  for (auto user : users) {
    // let's do it in a brute force way!
    std::transform(user->usedValues().begin(), user->usedValues().end(),
                   user->usedValues().begin(), [=, this](Ref<Value> value) {
                     if (value.get() == this) {
                       usageReplacementLogger->info(
                           "replacing use {} -> {} to {} -> {}", value->name(),
                           name(), value->name(), other->name());
                       return other;
                     }
                     return value;
                   });
  }
  users.clear();
}
} // namespace llvm