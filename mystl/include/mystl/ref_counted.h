//
// Created by creeper on 11/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_REF_COUNTED_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_REF_COUNTED_H
#include <cstddef>
#include <utility>
namespace mystl {

template<typename T>
class ref_counted {
private:
  struct control_block {
    T *ptr;
    size_t count;

    explicit control_block(T *p) : ptr(p), count(1) {}
  };

  control_block *control{};

  void release() {
    if (control) {
      --control->count;
      if (control->count == 0) {
        delete control->ptr;
        delete control;
      }
    }
  }

public:
  explicit ref_counted(T *raw_ptr = nullptr)
      : control(raw_ptr ? new control_block(raw_ptr) : nullptr) {}

  ref_counted(const ref_counted &other) noexcept: control(other.control) {
    if (control)
      ++control->count;
  }

  ref_counted(ref_counted &&other) noexcept: control(other.control) {
    other.control = nullptr;
  }

  ref_counted &operator=(const ref_counted &other) noexcept {
    if (this != &other) {
      release();
      control = other.control;
      if (control) {
        ++control->count;
      }
    }
    return *this;
  }

  ref_counted &operator=(ref_counted &&other) noexcept {
    if (this != &other) {
      release();
      control = other.control;
      other.control = nullptr;
    }
    return *this;
  }

  T &operator*() const noexcept {
    return *(control->ptr);
  }

  T *operator->() const noexcept {
    return control->ptr;
  }

  [[nodiscard]] size_t use_count() const noexcept {
    return control ? control->count : 0;
  }

  [[nodiscard]] bool empty() const noexcept {
    return control == nullptr;
  }

  [[nodiscard]] T *get() const noexcept {
    return control ? control->ptr : nullptr;
  }

  void reset() {
    release();
    control = nullptr;
  }

  ~ref_counted() {
    release();
  }
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_REF_COUNTED_H
