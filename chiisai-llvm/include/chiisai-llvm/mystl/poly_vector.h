//
// Created by creeper on 9/27/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
#include "observer_ptr.h"
#include <memory>
#include <vector>
namespace llvm::mystl {
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

  iterator begin() { return iterator(data.begin()); }
  iterator end() { return iterator(data.end()); }
  const_iterator begin() const { return const_iterator(data.cbegin()); }
  const_iterator end() const { return const_iterator(data.cend()); }
  const_iterator cbegin() const { return const_iterator(data.cbegin()); }
  const_iterator cend() const { return const_iterator(data.cend()); }

  [[nodiscard]] observer_ptr<Base> front() { return make_observer(data.front().get()); }
  [[nodiscard]] observer_ptr<const Base> front() const { return make_observer(data.front().get()); }
  [[nodiscard]] observer_ptr<Base> back() { return make_observer(data.back().get()); }
  [[nodiscard]] observer_ptr<const Base> back() const { return make_observer(data.back().get()); }

  void pop_back() { data.pop_back(); }
  void pop_front() { data.erase(data.begin()); }

  template<typename Derived, typename... Args>
  requires std::is_base_of_v<Base, Derived>
  void emplace_back(Args &&... args) {
    data.emplace_back(std::make_unique<Derived>(std::forward<Args>(args)...));
  }

  template<typename Derived>
  requires std::is_base_of_v<Base, Derived>
  void push_back(std::unique_ptr<Derived> &&ptr) {
    data.push_back(std::move(ptr));
  }

  void clear() { data.clear(); }

  [[nodiscard]] bool empty() const { return data.empty(); }
  [[nodiscard]] size_t size() const { return data.size(); }

private:
  std::vector<std::unique_ptr<Base>> data{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
