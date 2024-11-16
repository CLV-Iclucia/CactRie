//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_CASTINGS_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_CASTINGS_H
#include "observer_ptr.h"
namespace llvm::mystl {

template <typename Derived, typename Base>
observer_ptr<std::conditional_t<std::is_const_v<Base>, const Derived, Derived>>
dyn_cast_ref(observer_ptr<Base> base) {
  using element_type = std::conditional_t<std::is_const_v<Base>, const Derived, Derived>;
  return make_observer(dynamic_cast<element_type*>(base.get()));
}

template <typename T, typename U>
observer_ptr<T> static_cast_ref(observer_ptr<U> ptr) {
  return observer_ptr<T>(static_cast<T *>(ptr.get()));
}

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_CASTINGS_H
