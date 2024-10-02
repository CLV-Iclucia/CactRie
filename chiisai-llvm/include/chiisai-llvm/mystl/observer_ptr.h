//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
#include <cassert>
#include "hash.h"
#include <functional>
namespace llvm::mystl {
template<typename T>
class observer_ptr {
public:
  observer_ptr() = default;

  explicit observer_ptr(T *ptr) : m_ptr(ptr) {}
  observer_ptr(const observer_ptr &) = default;
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
  observer_ptr(const observer_ptr<U>& other) : m_ptr(other.get()) {}
  T *operator->() const {
    if (!m_ptr)
      throw std::runtime_error("observer_ptr is null");
    return m_ptr;
  }

  T &operator*() const {
    if (!m_ptr)
      throw std::runtime_error("observer_ptr is null");
    return *m_ptr;
  }

  T *get() const { return m_ptr; }

  explicit operator bool() const { return m_ptr; }
  observer_ptr &operator=(const observer_ptr &other) = default;
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
  observer_ptr &operator=(const observer_ptr<U>& other) {
    m_ptr = other.get();
    return *this;
  }
  bool operator==(observer_ptr<const T> other) const {
    return m_ptr == other.m_ptr;
  }
  bool operator!=(observer_ptr<const T> other) const {
    return m_ptr != other.m_ptr;
  }
private:
  T *m_ptr{};
};

template <typename T>
struct hash<observer_ptr<T>> {
  size_t operator()(const observer_ptr<T> &ptr) const {
    return std::hash<T*>{}(ptr.get());
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

namespace std {
template<typename T>
struct hash<llvm::mystl::observer_ptr<T>> {
  size_t operator()(const llvm::mystl::observer_ptr<T> &ptr) const {
    return llvm::mystl::hash<llvm::mystl::observer_ptr<T>>{}(ptr);
  }
};

template<typename T, typename U>
struct hash<pair<llvm::mystl::observer_ptr<T>, U>> {
  size_t operator()(const std::pair<T, U> &pair) const {
    size_t seed = 0;
    llvm::mystl::hash_combine(seed, pair.first);
    llvm::mystl::hash_combine(seed, pair.second);
    return seed;
  }
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H