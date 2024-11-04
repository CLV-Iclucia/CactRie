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

struct GlobalVariable : Value {

  [[nodiscard]] bool isConstant() const {
    return m_isConstant;
  }
private:
  bool m_isConstant{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
