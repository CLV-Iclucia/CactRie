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
template <typename Base>
struct poly_list {
public:
  template <typename Derived, typename... Args>
  requires std::is_base_of_v<Base, Derived>
  void emplace_back(Args&&... args) {
    container.emplace_back(std::make_unique<Derived>(std::forward<Args>(args)...));
  }

  template <typename Derived, typename... Args>
  requires std::is_base_of_v<Base, Derived>
  void emplace_front(Args&&... args) {
    container.emplace_front(std::make_unique<Derived>(std::forward<Args>(args)...));
  }

  template <typename Derived>
  requires std::is_base_of_v<Base, Derived>
  void push_back(std::unique_ptr<Derived> ptr) {
    container.push_back(std::move(ptr));
  }

  template <typename Derived>
  requires std::is_base_of_v<Base, Derived>
  void push_front(std::unique_ptr<Derived> ptr) {
    container.push_front(std::move(ptr));
  }

  struct iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = observer_ptr<Base>;
    using difference_type = std::ptrdiff_t;
    using pointer = observer_ptr<Base>*;
    using reference = observer_ptr<Base>&;

    explicit iterator(typename std::list<std::unique_ptr<Base>>::iterator it)
        : it_(it) {}

    observer_ptr<Base> operator*() const {
      return observer_ptr<Base>(it_->get());
    }

    observer_ptr<Base> operator->() const {
      return observer_ptr<Base>(it_->get());
    }

    iterator& operator++() {
      ++it_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      --it_;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const iterator& other) const {
      return !(*this == other);
    }

  private:
    typename std::list<std::unique_ptr<Base>>::iterator it_;
  };

  iterator begin() {
    return iterator(container.begin());
  }

  iterator end() {
    return iterator(container.end());
  }

  iterator erase(iterator it) {
    return iterator(container.erase(it.it_));
  }

  [[nodiscard]] bool empty() const {
    return container.empty();
  }

  [[nodiscard]] size_t size() const {
    return container.size();
  }
private:
  std::list<std::unique_ptr<Base>> container;
};


template <typename Base>
struct poly_view_list {
public:
  template <typename Derived>
  requires std::is_base_of_v<Base, Derived>
  void push_back(observer_ptr<Derived> ptr) {
    container.push_back(static_cast<observer_ptr<Base>>(ptr));
  }

  template <typename Derived>
  requires std::is_base_of_v<Base, Derived>
  void push_front(observer_ptr<Derived> ptr) {
    container.push_front(static_cast<observer_ptr<Base>>(ptr));
  }

  struct iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = observer_ptr<Base>;
    using difference_type = std::ptrdiff_t;
    using pointer = observer_ptr<Base>*;
    using reference = observer_ptr<Base>&;

    explicit iterator(typename std::list<observer_ptr<Base>>::iterator it)
        : it_(it) {}

    observer_ptr<Base> operator*() const {
      return *it_;
    }

    observer_ptr<Base> operator->() const {
      return *it_;
    }

    iterator& operator++() {
      ++it_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      --it_;
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const iterator& other) const {
      return !(*this == other);
    }

  private:
    typename std::list<observer_ptr<Base>>::iterator it_;
  };

  iterator begin() {
    return iterator(container.begin());
  }

  iterator end() {
    return iterator(container.end());
  }

  iterator erase(iterator it) {
    return iterator(container.erase(it.it_));
  }

  [[nodiscard]] bool empty() const {
    return container.empty();
  }

  [[nodiscard]] size_t size() const {
    return container.size();
  }

private:
  std::list<observer_ptr<Base>> container{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_POLY_LIST_H
