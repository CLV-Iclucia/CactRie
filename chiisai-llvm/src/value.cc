//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/user.h>
#include <minilog/logger.h>
namespace llvm {
void Value::replaceAllUsesWith(Ref<Value> other) {
  assert(other.get() != this);
  for (auto user : users()) {
    // let's do it in a brute force way!
    std::transform(
        user->usedValues().begin(), user->usedValues().end(), user->usedValues().begin(),
        [=, this](Ref<Value> value) {
          if (value.get() == this) {
            minilog::info("replacing use of {} with {}, user: {}", value->name(), other->name(), user->name());
            return other;
          }
          return value;
        });
  }
  users().clear();
}
}