//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_HASH_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_HASH_H

#include <functional>
#include <vector>
namespace mystl {
template<typename T>
struct hash {};

template <typename T>
inline void hash_combine(std::size_t& seed, const T& value) {
  std::hash<T> hasher;
  seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
}

template<typename T, typename U>
struct std::hash<std::pair<T, U>> {
  size_t operator()(const std::pair<T, U> &pair) const {
    size_t seed = 0;
    mystl::hash_combine(seed, pair.first);
    mystl::hash_combine(seed, pair.second);
    return seed;
  }
};

template<typename T>
struct std::hash<std::vector<T>> {
  size_t operator()(const std::vector<T> &vec) const {
    size_t seed = 0;
    for (const auto &elem : vec) {
      mystl::hash_combine(seed, elem);
    }
    return seed;
  }
};
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_HASH_H
