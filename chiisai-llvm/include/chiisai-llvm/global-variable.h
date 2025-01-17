//
// Created by creeper on 10/2/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
#include <chiisai-llvm/constant.h>
namespace llvm {

struct GlobalVariableDetails {
  const std::string &name;
  CRef<Constant> initializer{};
  bool isConstant{};
};

// GlobalVariable is actually a pointer to a global object
struct GlobalVariable final : Constant {

  explicit GlobalVariable(const GlobalVariableDetails &details)
      : Constant(details.name, details.initializer->type()),
        initVal(details.initializer), isConst(details.isConstant) {}

  GlobalVariable(const std::string &name, CRef<Type> type)
      : Constant(name, type) {}
  [[nodiscard]] bool isConstant() const { return isConst; }
  bool hasInitializer() const { return initVal.has_value(); }
  [[nodiscard]] CRef<Constant> initializer() const {
    if (!initVal.has_value())
      throw std::runtime_error("Global variable has no initializer");
    return initVal.value();
  }

private:
  std::optional<CRef<Constant>> initVal{};
  bool isConst{};
};

} // namespace llvm
#endif // CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_GLOBAL_VARIABLE_H
