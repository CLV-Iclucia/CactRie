//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PROPERTIES_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PROPERTIES_H
namespace llvm {
struct RAII {
  RAII() = default;
  RAII(const RAII &) = delete;
  RAII &operator=(const RAII &) = delete;
};

struct FixedInMem {
  FixedInMem() = default;
  FixedInMem(FixedInMem &&) = delete;
};

template<typename Derived>
struct PtrImpl : RAII {
  // overload operator -> to access Derived::Impl
  Derived *operator->() {
    return static_cast<Derived *>(this);
  }
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_PROPERTIES_H
