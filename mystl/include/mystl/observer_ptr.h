//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
#include <cassert>
#include <type_traits>
#include "hash.h"

namespace mystl {
template<typename T>
requires (!std::is_pointer_v<T>)
class observer_ptr {
public:
  observer_ptr() = default;

  template <typename U>
  requires std::is_convertible_v<U*, T*>
  observer_ptr(U *ptr) : m_ptr(ptr) {}
  template<typename U>
  requires std::is_convertible_v<U*, T*>
  observer_ptr(observer_ptr<U> other) : m_ptr(other.get()) {}
  observer_ptr(std::nullptr_t) : m_ptr(nullptr) {}
  T *operator->() const {
    assert(m_ptr);
    return m_ptr;
  }

  T &operator*() const {
    assert(m_ptr);
    return *m_ptr;
  }

  T *get() const { return m_ptr; }

  operator bool() const { return m_ptr; }
  template<typename U>
  requires std::is_convertible_v<U *, T *>
  observer_ptr &operator=(observer_ptr<U> other) {
    m_ptr = other.get();
    return *this;
  }
  bool operator==(observer_ptr other) const {
    return m_ptr == other.m_ptr;
  }
  bool operator!() const {
    return !m_ptr;
  }
private:
  template<typename U>
  requires (!std::is_pointer_v<U>)
  friend class observer_ptr;
  T *m_ptr{};
};

template<typename T>
struct hash<observer_ptr<T>> {
  size_t operator()(observer_ptr<T> ptr) const {
    return std::hash<T *>{}(ptr.get());
  }
};

template<typename T>
observer_ptr<T> make_observer(T *ptr) {
  return observer_ptr<T>(ptr);
}

template<typename T>
observer_ptr<const T> make_observer(const T *ptr) {
  return observer_ptr<const T>(ptr);
}
}

template<typename T>
struct std::hash<mystl::observer_ptr<T>> {
  size_t operator()(const mystl::observer_ptr<T> &ptr) const {
    return mystl::hash<mystl::observer_ptr<T>>{}(ptr);
  }
};
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
