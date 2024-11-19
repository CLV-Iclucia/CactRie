//
// Created by creeper on 10/2/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
#include <chiisai-llvm/constant.h>
namespace llvm {

struct GlobalVariableDetails {
  const std::string& name;
  CRef<Constant> initializer{};
  bool isConstant{};
};

// GlobalVariable is actually a pointer to a global object
struct GlobalVariable : Constant {

  [[nodiscard]] bool isConstant() const {
    return constVal.has_value();
  }

private:
  std::optional<Ref<Constant>> constVal;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
