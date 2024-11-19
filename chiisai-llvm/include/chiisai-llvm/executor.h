//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
#include <stack>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/constant-scalar.h>
namespace llvm {

struct RuntimeVar {
  CRef<Value> value;
  std::optional<size_t> frameIndex{};

  [[nodiscard]] bool isGlobal() const {
    return !frameIndex.has_value();
  }
};

struct SpanAddress {
  RuntimeVar begin{};
  size_t index{};
};

struct Result {
  using Integer = std::variant<int32_t, int64_t>;
  using Floating = std::variant<float, double>;

  template<typename... Ts>
  explicit Result(std::variant<Ts...> value) {
    bool matched = ((std::holds_alternative<Ts>(value) ? (this->value = value, true) : false) || ...);
    if (!matched) {
      throw std::invalid_argument("Invalid type for std::variant");
    }
  }

  explicit Result(bool value) : value(value) {}
  explicit Result(SpanAddress value) : value(value) {}

  std::variant<bool, int32_t, int64_t, float, double, SpanAddress> value;
  [[nodiscard]] bool isBool() const {
    return std::holds_alternative<bool>(value);
  }
  [[nodiscard]] bool isPointer() const {
    return std::holds_alternative<SpanAddress>(value);
  }
  [[nodiscard]] bool canOperateWith(const Result &other) const {
    return !isBool() && !isPointer() && value.index() == other.value.index();
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
  template<typename T> requires std::is_integral_v<T>
  [[nodiscard]] T as() const {
    if (std::holds_alternative<int32_t>(value))
      return std::get<int32_t>(value);
    if (std::holds_alternative<int64_t>(value))
      return std::get<int64_t>(value);
    throw std::runtime_error("Cannot convert to integer");
  }
};

struct CallFrame {
  std::unordered_map<std::string, Result> regs;
  // memory maps pointer name to the value it points to
  // it is for alloca and load/store instructions
  std::unordered_map<std::string, std::vector<Result>> memory;
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
    returnFlag = false;
    callFrames.emplace_back();
  }
  void popFrame() {
    callFrames.pop_back();
    returnFlag = false;
  }
  Result &reg(CRef<Value> value);
  Result &reg(const std::string &name) {
    return callFrames.back().regs.at(name);
  }
  Result load(SpanAddress span) const {
    CRef<std::unordered_map<std::string, std::vector<Result>>> mem{};
    if (span.begin.isGlobal())
      mem = makeCRef(globalMemory);
    else mem = makeCRef(callFrames.at(span.begin.frameIndex.value()).memory);
    return mem->at(span.begin.value->name()).at(span.index);
  }
  void store(SpanAddress span, Result result) {
    Ref<std::unordered_map<std::string, std::vector<Result>>> mem{};
    if (span.begin.isGlobal())
      mem = makeRef(globalMemory);
    else mem = makeRef(callFrames.at(span.begin.frameIndex.value()).memory);
    mem->at(span.begin.value->name()).at(span.index) = result;
  }
  Module &module;
  LLVMContext &ctx;
  std::string prvBasicBlock{};
  std::string nxtBasicBlock{};
  std::optional<Result> returnReg{};
  bool returnFlag{};
private:
  std::vector<CallFrame> callFrames{};
  std::unordered_map<std::string, std::vector<Result>> globalMemory;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_EXECUTOR_H
