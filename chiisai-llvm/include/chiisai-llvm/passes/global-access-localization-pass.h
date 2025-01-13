//
// Created by creeper on 1/4/25.
//

#ifndef GLOBAL_ACCESS_LOCALIZATION_PASS_H
#define GLOBAL_ACCESS_LOCALIZATION_PASS_H
#include <chiisai-llvm/function.h>
namespace llvm {

// a pass that renames some global accesses
struct GlobalAccessLocalizationPass {
  void runOnFunction(Function &func);
};
} // namespace llvm
#endif //GLOBAL_ACCESS_LOCALIZATION_PASS_H
