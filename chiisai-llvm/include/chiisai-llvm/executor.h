//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
#include <stack>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/address.h>
namespace llvm {

struct Result {
  using Integer = std::variant<int32_t, int64_t>;
  using Floating = std::variant<float, double>;

  explicit Result(Integer value) {
    if (std::holds_alternative<int32_t>(value))
      this->value = std::get<int32_t>(value);
    this->value = std::get<int64_t>(value);
  }

  explicit Result(Floating value) {
    if (std::holds_alternative<float>(value))
      this->value = std::get<float>(value);
    this->value = std::get<double>(value);
  }

  std::variant<bool, int32_t, int64_t, float, double, Address> value;
  [[nodiscard]] bool isBool() const {
    return std::holds_alternative<bool>(value);
  }
  [[nodiscard]] bool isPointer() const {
    return std::holds_alternative<Address>(value);
  }
  [[nodiscard]] bool canOperateWith(const Result &other) const {
    return !isBool() && value.index() == other.value.index() && !std::holds_alternative<Address>(value);
  }
  [[nodiscard]] Integer toInteger() const {
    if (std::holds_alternative<int32_t>(value))
      return std::get<int32_t>(value);
    if (std::holds_alternative<int64_t>(value))
      return std::get<int64_t>(value);
    throw std::runtime_error("Cannot convert to integer");
  }
  [[nodiscard]] Floating toFloating() const {
    if (std::holds_alternative<float>(value))
      return std::get<float>(value);
    if (std::holds_alternative<double>(value))
      return std::get<double>(value);
    throw std::runtime_error("Cannot convert to floating point");
  }
  [[nodiscard]] Address toPointer() const {
    return std::get<Address>(value);
  }
};

struct CallFrame {
  std::unordered_map<std::string, Result> regs;
};

struct Module;

struct Executor {
  explicit Executor(Module &module, LLVMContext &ctx) : module(module), ctx(ctx) {}
  void execute(Ref<Executable> value) {
    value->accept(*this);
  }
  void execute(Executable &value) {
    value.accept(*this);
  }
  void pushFrame() {
    callFrames.emplace();
  }
  void popFrame() {
    callFrames.pop();
  }
  Result &reg(const std::string &name) {
    return callFrames.top().regs.at(name);
  }
  Module &module;
  LLVMContext &ctx;
  std::string incomingBasicBlock{};
  std::optional<Result> returnReg{};
private:
  std::stack<CallFrame> callFrames{};
  std::unordered_map<std::string, Result> globalResults;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
