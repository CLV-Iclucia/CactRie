//
// Created by creeper on 1/5/25.
//
#include "chiisai-llvm/instructions.h"

#include <chiisai-llvm/passes/const-prop-pass.h>

namespace llvm {

using ConstLookup =
    std::unordered_map<CRef<Value>, std::variant<int32_t, float, double, bool>>;

struct ConstantState {

  static ConstantState identity() { return ConstantState{}; }

  ConstantState meet(const ConstantState &other) const {
    ConstantState result{values};
    for (const auto &[key, value] : other.values) {
      if (result.values.contains(key) && result.values[key] != value)
        result.values.erase(key);
      else
        result.values[key] = value;
    }
    return result;
  }

  bool operator==(const ConstantState &other) const {
    return values == other.values;
  }

  ConstLookup values{};
};

} // namespace llvm