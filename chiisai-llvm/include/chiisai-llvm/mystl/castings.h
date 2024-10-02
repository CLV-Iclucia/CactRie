//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_CASTINGS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_CASTINGS_H
#include "observer_ptr.h"
namespace llvm::mystl {

template <typename Base, typename Derived>
observer_ptr<Derived> dynCast(observer_ptr<Base> base) {
  return make_observer(dynamic_cast<Derived>(base.get()));
}

template <typename S, typename T>
observer_ptr<S> staticCast(observer_ptr<T> t) {
  return make_observer(static_cast<S*>(t.get()));
}

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_CASTINGS_H
