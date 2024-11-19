//
// Created by creeper on 11/16/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_ZIP_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_ZIP_H
#include <tuple>
#include <vector>
#include <iterator>
namespace llvm::mystl {

template <typename T>
using select_access_t = std::conditional_t<
std::is_same_v<T, std::vector<bool>::iterator> || std::is_same_v<T, std::vector<bool>::const_iterator>,
typename T::value_type,
typename T::reference
>;

template<std::forward_iterator... Iters>
class zip_iterator {
  std::tuple<Iters...> m_iters;
public:
  using value_type = std::tuple<select_access_t<Iters>...>;
  zip_iterator() = delete;
  explicit zip_iterator(Iters &&... iters) : m_iters(std::forward<Iters>(iters)...) {}

  zip_iterator &operator++() {
    std::apply([](auto &... iters) { (++iters, ...); }, m_iters);
    return *this;
  }
  bool operator==(const zip_iterator &other) const {
    return m_iters == other.m_iters;
  }
  bool operator!=(const zip_iterator &other) const {
    return *this != other;
  }
  value_type operator*() {
    return std::apply([](auto &&... iters) { return value_type(*iters...); }, m_iters);
  }
};

template<typename T>
using select_iterator_t = std::conditional_t<std::is_const_v<std::remove_reference_t<T>>,
typename std::decay_t<T>::const_iterator,
typename std::decay_t<T>::iterator>;

template<std::ranges::forward_range... Ranges>
struct zip_range {
public:
  using iterator_t = zip_iterator<select_iterator_t<Ranges>...>;
  std::tuple<Ranges...> iterables;
  explicit zip_range(Ranges &&... ranges) : iterables(std::forward<Ranges>(iterables)...) {}
  iterator_t begin() {
    return std::apply([](auto &&... args) {
      return (iterator_t(std::begin(args)...)); }, iterables);
  }
  iterator_t end() {
    return std::apply([](auto &&... args) {
      return (iterator_t(std::end(args)...)); }, iterables);
  }
};

template<std::ranges::forward_range... Ranges>
auto zip(Ranges &&... ranges) {
  return zip_range<Ranges...>(std::forward<Ranges>(ranges)...);
}
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_ZIP_H
