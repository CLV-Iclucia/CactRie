//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
#include <stack>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/value.h>
namespace llvm {

struct Result {

};

struct CallFrame {
  std::unordered_map<std::string, Result> regs;
};

struct Module;

struct Executor {
  void execute(Ref<Value> value) {
    value->accept(*this);
  }
  void execute(Value& value) {
    value.accept(*this);
  }
  void pushFrame() {
    callFrames.push({});
  }
  void popFrame() {
    callFrames.pop();
  }
  Result& reg(const std::string& name) {
    return callFrames.top().regs.at(name);
  }
  Module& module;
  LLVMContext &ctx;
private:
  std::stack<CallFrame> callFrames;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
