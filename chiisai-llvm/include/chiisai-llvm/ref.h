//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_REF_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_REF_H
#include <mystl/observer_ptr.h>
#include <mystl/castings.h>
#include <mystl/ref_counted.h>
#include <mystl/not_null.h>
namespace llvm {

template<typename T>
using Ref = mystl::observer_ptr<T>;

template<typename T>
using CRef = mystl::observer_ptr<const T>;

template<typename T>
using Rc = mystl::ref_counted<T>;

template<typename T>
Ref<T> makeRef(T &t) {
  return mystl::make_observer(&t);
}

template<typename T>
CRef<T> makeCRef(const T &t) {
  return mystl::make_observer(&t);
}

template<typename Derived, typename Base>
bool isa(Ref<Base> base) {
  return mystl::dyn_cast_ref<Derived, Base>(base) != nullptr;
}

template<typename Derived, typename Base>
auto cast(Ref<Base> base) {
  if (!isa<Derived>(base))
    throw std::bad_cast();
  return mystl::dyn_cast_ref<Derived, Base>(base);
}

template<typename Derived, typename Base>
auto tryCast(Ref<Base> base) {
  return mystl::dyn_cast_ref<Derived, Base>(base);
}

template<typename Ptr>
using NotNull = mystl::not_null<Ptr>;
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_REF_H
