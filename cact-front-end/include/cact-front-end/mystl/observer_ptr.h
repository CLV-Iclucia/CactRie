//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
#include <cassert>
#include <memory>
namespace cactfrontend {
template<typename T>
class observer_ptr {
public:
  observer_ptr() = default;

  explicit observer_ptr(T *ptr) : m_ptr(ptr) {}

  T *operator->() const {
    assert(m_ptr != nullptr);
    return m_ptr;
  }

  T &operator*() const {
    assert(m_ptr != nullptr);
    return *m_ptr;
  }

  T *get() const { return m_ptr; }

  explicit operator bool() const { return m_ptr; }
  observer_ptr& operator=(const observer_ptr& other) = default;
  bool operator==(observer_ptr<T> other) const {
    return m_ptr == other.m_ptr;
  }
private:
  T *m_ptr{};
};

template<typename T>
[[nodiscard]]
observer_ptr<T> make_observer(T *ptr) {
  return observer_ptr<T>(ptr);
}

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_MYSTL_OBSERVER_PTR_H
