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
struct poly_vector {
public:
  struct iterator {
    using container_iterator = typename std::vector<std::unique_ptr<Base>>::iterator;
    explicit iterator(container_iterator it) : it(it) {}
    observer_ptr<Base> operator*() {
      return it->get();
    }
    observer_ptr<Base> operator->() {
      return it->get();
    }
    iterator &operator++() {
      ++it;
      return *this;
    }
    iterator &operator--() {
      --it;
      return *this;
    }
    bool operator==(const iterator &other) const {
      return it == other.it;
    }
    bool operator!=(const iterator &other) const {
      return it != other.it;
    }
  private:
    container_iterator it;
  };

  iterator begin() {
    return iterator(data.begin());
  }
  iterator end() {
    return iterator(data.end());
  }
  observer_ptr<Base> front() {
    return make_observer(data.front().get());
  }
  observer_ptr<Base> back() {
    return make_observer(data.back().get());
  }
  void pop_back() {
    data.pop_back();
  }
  void pop_front() {
    data.erase(data.begin());
  }
  template<typename Derived, typename... Args>
  void emplace_back(Args &&... args) {
    data.emplace_back(std::make_unique<Derived>(std::forward<Args>(args)...));
  }
  template<typename Derived, typename... Args>
  void push_back(Args &&... args) {
    data.push_back(std::make_unique<Derived>(std::forward<Args>(args)...));
  }
  void clear() {
    data.clear();
  }
  bool empty() {
    return data.empty();
  }
  size_t size() {
    return data.size();
  }
private:
  std::vector<std::unique_ptr<Base>> data{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_VECTOR_H
