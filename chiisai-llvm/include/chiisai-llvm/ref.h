//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_REF_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_REF_H
#include <chiisai-llvm/mystl/observer_ptr.h>
#include <chiisai-llvm/mystl/castings.h>
#include <chiisai-llvm/mystl/not_null.h>
namespace llvm {

template <typename T>
using Ref = mystl::observer_ptr<T>;

template <typename T>
using CRef = mystl::observer_ptr<const T>;

template <typename T>
Ref<T> ref(T& t) {
  return mystl::make_observer(&t);
}

template <typename T>
CRef<T> cref(const T& t) {
  return mystl::make_observer(&t);
}

template <typename Ptr>
using NotNull = mystl::not_null<Ptr>;
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_REF_H
