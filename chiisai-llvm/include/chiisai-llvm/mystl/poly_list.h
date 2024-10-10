//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_LIST_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_LIST_H
#include "observer_ptr.h"
#include <memory>
#include <vector>
#include <list>
namespace llvm::mystl {
template<typename Base>
struct poly_list {
public:
  template<typename Derived>
  void emplace_back() {
    container.emplace_back(std::make_unique<Derived>());
  }
  template<typename Derived, typename... Args>
  void emplace_back(Args &&... args) {
    container.emplace_back(std::make_unique<Derived>(std::forward<Args>(args)...));
  }
  template<typename Derived>
  void emplace_front() {
    container.emplace_front(std::make_unique<Derived>());
  }
  template<typename Derived, typename... Args>
  void emplace_front(Args &&... args) {
    container.emplace_front(std::make_unique<Derived>(std::forward<Args>(args)...));
  }
  template<typename Derived>
  void push_back(std::unique_ptr<Derived> ptr) {
    container.push_back(std::move(ptr));
  }
  template<typename Derived>
  void push_front(std::unique_ptr<Derived> ptr) {
    container.push_front(std::move(ptr));
  }

  struct iterator {
    using container_iterator = typename std::list<std::unique_ptr<Base>>::iterator;
    explicit iterator(container_iterator it) : it(it) {}
    observer_ptr<Base> operator*() {
      return make_observer(it->get());
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
  iterator begin() const {
    return iterator(container.begin());
  }
  iterator end() const {
    return iterator(container.end());
  }
  iterator erase(iterator it) {
    return iterator(container.erase(it.it));
  }
private:
  std::list<std::unique_ptr<Base>> container{};
};

template <typename Base>
struct poly_view_list {
public:
  template<typename Derived>
  void push_back(observer_ptr<Derived> ptr) {
    container.push_back(ptr);
  }
  template<typename Derived>
  void push_front(observer_ptr<Derived> ptr) {
    container.push_front(ptr);
  }

  struct iterator {
    using container_iterator = typename std::vector<std::unique_ptr<Base>>::iterator;
    explicit iterator(container_iterator it) : it(it) {}
    observer_ptr<Base> operator*() {
      return make_observer(it->get());
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
  iterator begin() const {
    return iterator(container.begin());
  }
  iterator end() const {
    return iterator(container.end());
  }
  iterator erase(iterator it) {
    return iterator(container.erase(it.it));
  }
private:
  std::list<observer_ptr<Base>> container{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_LIST_H
