//
// Created by creeper on 10/14/24.
//
#include <chiisai-llvm/value.h>

namespace llvm {
void Value::replaceAllUsesWith(Ref<Value> other) {
  assert(other.get() != this);
  for (auto user : users()) {

  }
}
}