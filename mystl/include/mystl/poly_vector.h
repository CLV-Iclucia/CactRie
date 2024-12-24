//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
#include "observer_ptr.h"
#include <memory>
#include <vector>

namespace mystl {
/**
 * @brief A vector that holds polymorphic objects
 * @tparam Base the base class of the polymorphic objects
 */
template<typename Base>
class poly_vector {
public:
  class iterator {
  public:
    using container_iterator = typename std::vector<std::unique_ptr<Base>>::iterator;

    explicit iterator(container_iterator it) : it(it) {}
    observer_ptr<Base> operator*() const { return make_observer(it->get()); }
    observer_ptr<Base> operator->() const { return make_observer(it->get()); }
    iterator &operator++() {
      ++it;
      return *this;
    }
    iterator &operator--() {
      --it;
      return *this;
    }
    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }
    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const iterator &other) const { return it == other.it; }
    bool operator!=(const iterator &other) const { return !(*this == other); }

  private:
    container_iterator it;
  };

  class const_iterator {
  public:
    using container_iterator = typename std::vector<std::unique_ptr<Base>>::const_iterator;

    explicit const_iterator(container_iterator it) : it(it) {}
    observer_ptr<const Base> operator*() const { return make_observer(it->get()); }
    observer_ptr<const Base> operator->() const { return make_observer(it->get()); }
    const_iterator &operator++() {
      ++it;
      return *this;
    }
    const_iterator &operator--() {
      --it;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator &other) const { return it == other.it; }
    bool operator!=(const const_iterator &other) const { return !(*this == other); }

  private:
    container_iterator it;
  };

  iterator begin() { return iterator(m_container.begin()); }
  iterator end() { return iterator(m_container.end()); }
  const_iterator begin() const { return const_iterator(m_container.cbegin()); }
  const_iterator end() const { return const_iterator(m_container.cend()); }
  const_iterator cbegin() const { return const_iterator(m_container.cbegin()); }
  const_iterator cend() const { return const_iterator(m_container.cend()); }

  [[nodiscard]] observer_ptr<Base> front() { return make_observer(m_container.front().get()); }
  [[nodiscard]] observer_ptr<const Base> front() const { return make_observer(m_container.front().get()); }
  [[nodiscard]] observer_ptr<Base> back() { return make_observer(m_container.back().get()); }
  [[nodiscard]] observer_ptr<const Base> back() const { return make_observer(m_container.back().get()); }

  void pop_back() { m_container.pop_back(); }
  void pop_front() { m_container.erase(m_container.begin()); }

  template<typename Derived, typename... Args>
  requires std::is_base_of_v<Base, Derived>
  void emplace_back(Args &&... args) {
    m_container.emplace_back(std::make_unique<Derived>(std::forward<Args>(args)...));
  }

  template<typename Derived>
  requires std::is_base_of_v<Base, Derived>
  void push_back(std::unique_ptr<Derived> &&ptr) {
    m_container.push_back(std::move(ptr));
  }

  void clear() { m_container.clear(); }

  [[nodiscard]] bool empty() const { return m_container.empty(); }
  [[nodiscard]] size_t size() const { return m_container.size(); }

private:
  std::vector<std::unique_ptr<Base>> m_container{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
