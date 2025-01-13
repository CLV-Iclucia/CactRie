//
// Created by creeper on 12/12/24.
//

#ifndef CONST_PROP_PASS_H
#define CONST_PROP_PASS_H
namespace llvm {

struct ConstantPropagationPass {
  void runOnFunction(Function &function);

private:

};

} // namespace llvm
#endif // CONST_PROP_PASS_H
