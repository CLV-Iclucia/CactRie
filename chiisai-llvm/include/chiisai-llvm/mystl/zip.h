//
// Created by creeper on 11/16/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_ZIP_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_ZIP_H
#include <tuple>
#include <vector>
namespace llvm::mystl {
template<typename T>
concept Iterator = requires(T it) {
  requires std::is_convertible_v<std::decay_t<decltype(*it)>, typename T::value_type>;
  typename T::reference;
  { ++it } -> std::convertible_to<T>;
  { it != it } -> std::convertible_to<bool>;
  { it == it } -> std::convertible_to<bool>;
};

template<typename T>
concept Iterable = requires(T t) {
  { std::begin(t) } -> Iterator;
  { std::end(t) } -> Iterator;
};

template <typename T>
using select_access_t = std::conditional_t<
std::is_same_v<T, std::vector<bool>::iterator> || std::is_same_v<T, std::vector<bool>::const_iterator>,
typename T::value_type,
typename T::reference
>;

template<Iterator... Iters>
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
template<Iterable... Iterables>
struct zip_range {
public:
  using iterator_t = zip_iterator<select_iterator_t<Iterables>...>;
  std::tuple<Iterables ...> iterables;
  template<Iterable... Args>
  explicit zip_range(Args &&... iterables) : iterables(std::forward<Args>(iterables)...) {}
  iterator_t begin() {
    return std::apply([](auto &&... args) {
      return (iterator_t(std::begin(args)...)); }, iterables);
  }
  iterator_t end() {
    return std::apply([](auto &&... args) {
      return (iterator_t(std::end(args)...)); }, iterables);
  }
};
template<Iterable... Iterables>
auto zip(Iterables &&... iterables) {
  return zip_range<Iterables...>(std::forward<Iterables>(iterables)...);
}
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_ZIP_H
