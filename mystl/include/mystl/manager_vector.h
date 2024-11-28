//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_MANAGER_VECTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_MANAGER_VECTOR_H
#include <vector>
#include <memory>
#include "observer_ptr.h"
namespace mystl {
/**
 * @brief A vector that manages the lifetime of the objects it contains
 * typical vector cannot provide pointer to the object it contains since the object may be moved
 * this vector holds the object in a unique_ptr and provides a pointer to the object
 */
template <typename T>
struct manager_vector {
  manager_vector() = default;

  manager_vector(const manager_vector&) = delete;
  manager_vector& operator=(const manager_vector&) = delete;

  manager_vector(manager_vector&&) noexcept = default;
  manager_vector& operator=(manager_vector&&) noexcept = default;

  void push_back(std::unique_ptr<T>&& ptr) {
    data.push_back(std::move(ptr));
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    data.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  [[nodiscard]] observer_ptr<T> operator[](size_t index) const {
    return observer_ptr<T>(data[index].get());
  }

  [[nodiscard]] observer_ptr<T> at(size_t index) const {
    if (index >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
    return observer_ptr<T>(data.at(index).get());
  }

  [[nodiscard]] observer_ptr<T> back() {
    return observer_ptr<T>(data.back().get());
  }

  [[nodiscard]] observer_ptr<const T> back() const {
    return observer_ptr<const T>(data.back().get());
  }

  [[nodiscard]] size_t size() const {
    return data.size();
  }

  [[nodiscard]] bool empty() const {
    return data.empty();
  }

  void clear() {
    data.clear();
  }

  void erase(size_t index) {
    if (index >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
    data.erase(data.begin() + index);
  }

  void erase(typename std::vector<std::unique_ptr<T>>::iterator it) {
    data.erase(it);
  }

  struct iterator {
    using container_iterator = typename std::vector<std::unique_ptr<T>>::iterator;
    explicit iterator(container_iterator it) : it_(it) {}

    observer_ptr<T> operator*() const {
      return observer_ptr<T>(it_->get());
    }

    observer_ptr<T> operator->() const {
      return observer_ptr<T>(it_->get());
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
      return it_ != other.it_;
    }

  private:
    container_iterator it_;
  };

  struct const_iterator {
    using container_iterator = typename std::vector<std::unique_ptr<T>>::const_iterator;
    explicit const_iterator(container_iterator it) : it_(it) {}

    observer_ptr<const T> operator*() const {
      return observer_ptr<const T>(it_->get());
    }

    observer_ptr<const T> operator->() const {
      return observer_ptr<const T>(it_->get());
    }

    const_iterator& operator++() {
      ++it_;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator& operator--() {
      --it_;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const const_iterator& other) const {
      return it_ != other.it_;
    }

  private:
    container_iterator it_;
  };

  iterator begin() {
    return iterator(data.begin());
  }

  iterator end() {
    return iterator(data.end());
  }

  const_iterator begin() const {
    return const_iterator(data.cbegin());
  }

  const_iterator end() const {
    return const_iterator(data.cend());
  }

  const_iterator cbegin() const {
    return const_iterator(data.cbegin());
  }

  const_iterator cend() const {
    return const_iterator(data.cend());
  }

private:
  std::vector<std::unique_ptr<T>> data;
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_MANAGER_VECTOR_H
