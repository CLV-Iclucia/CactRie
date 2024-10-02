//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_MANAGER_VECTOR_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_MANAGER_VECTOR_H
#include <vector>
#include <memory>
#include "observer_ptr.h"
namespace llvm::mystl {
/**
 * @brief A vector that manages the lifetime of the objects it contains
 * typical vector cannot provide pointer to the object it contains since the object may be moved
 * this vector holds the object in a unique_ptr and provides a pointer to the object
 */
template<typename T>
struct manager_vector {
  manager_vector() = default;
  manager_vector(const manager_vector &) = delete;
  manager_vector &operator=(const manager_vector &) = delete;
  manager_vector(manager_vector &&) = default;
  manager_vector &operator=(manager_vector &&) = default;
  void push_back(std::unique_ptr<T> &&ptr) {
    data.push_back(std::move(ptr));
  }

  template<typename... Args>
  void emplace_back(Args &&... args) {
    data.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }
  [[nodiscard]] observer_ptr<T> operator[](size_t index) const {
    return observer_ptr<T>(data[index].get());
  }
  [[nodiscard]] observer_ptr<T> at(size_t index) const {
    return observer_ptr<T>(data.at(index).get());
  }
  [[nodiscard]] observer_ptr<T> back() {
    return observer_ptr<T>(data.back().get());
  }
  [[nodiscard]] observer_ptr<const T> back() const {
    return observer_ptr<const T>(data.front().get());
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
    data.erase(data.begin() + index);
  }
private:
  std::vector<std::unique_ptr<T>> data{};
};
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_MANAGER_VECTOR_H
