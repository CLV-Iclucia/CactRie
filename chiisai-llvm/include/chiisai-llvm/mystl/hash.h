//
// Created by creeper on 9/30/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_HASH_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_HASH_H
namespace llvm::mystl {
template<typename T>
struct hash {};

template <typename T>
inline void hash_combine(std::size_t& seed, const T& value) {
  std::hash<T> hasher;
  seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_HASH_H
