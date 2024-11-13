//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PROPERTIES_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PROPERTIES_H
namespace llvm {
struct NonCopyable {
  NonCopyable() = default;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
  NonCopyable(NonCopyable &&) = default;
};

struct RAII {
  RAII() = default;
  RAII(RAII &&) = delete;
};

struct Executor;
struct Executable {
  virtual void accept(Executor &executor) = 0;
  virtual ~Executable() = default;
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PROPERTIES_H
