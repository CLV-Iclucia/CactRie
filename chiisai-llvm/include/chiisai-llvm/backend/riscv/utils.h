//
// Created by creeper on 1/11/25.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <string_view>
#include <cassert>
namespace llvm {
inline bool isConstantInt(std::string_view str) {
  assert(!str.empty());
  if (str[0] == '-')
    str.remove_prefix(1);
  for (auto c : str)
    if (!std::isdigit(c))
      return false;
  return true;
}

inline bool isConstantHex(std::string_view str) {
  assert(!str.empty());
  if (str.size() < 3)
    return false;
  if (str[0] != '0' || str[1] != 'x')
    return false;
  str.remove_prefix(2);
  for (auto c : str)
    if (!std::isxdigit(c))
      return false;
  return true;
}

inline bool isConstant(std::string_view str) {
  assert(!str.empty());
  return isConstantInt(str) || isConstantHex(str);
}
}
#endif //UTILS_H
