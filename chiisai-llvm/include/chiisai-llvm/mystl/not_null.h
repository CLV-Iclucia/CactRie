//
// Created by creeper on 10/20/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_NOT_NULL_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_NOT_NULL_H

#include <cstddef>
#include <stdexcept>
namespace llvm::mystl {

template<typename Ptr>
struct not_null {
  not_null(Ptr ptr) : ptr(ptr) {
    if (ptr == nullptr)
      throw std::invalid_argument("null pointer passed to not_null");
  }
  not_null(std::nullptr_t) = delete;
  not_null() = delete;
  operator Ptr() const { return ptr; }
  decltype(auto) operator*() const { return *ptr; }
  decltype(auto) operator->() const { return ptr; }
  decltype(auto) operator->() { return ptr; }
  Ptr ptr;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_NOT_NULL_H
