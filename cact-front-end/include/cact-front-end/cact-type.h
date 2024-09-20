//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
#include <cstdint>
#include <vector>
#include <array>
#include <cassert>

namespace cactfrontend {
enum class CactBasicType : uint8_t {
  Unknown,
  Void,
  Int32,
  Bool,
  Float,
  Double
};

inline uint32_t sizeOf(CactBasicType type) {
  static std::array<uint32_t, 8> size ={
      0, 0, 4, 4, 4, 8,
  };
  assert(type != CactBasicType::Unknown && type != CactBasicType::Void);
  return size[static_cast<int>(type)];
}

struct CactType {
  bool isConst{};
  CactBasicType type{};
  std::vector<uint32_t> arrayDims{};
  uint32_t size() {
    uint32_t product = sizeOf(type);
    for (auto dim : arrayDims)
      product *= dim;
    return product;
  }
  [[nodiscard]] bool isArray() const {
    return !arrayDims.empty();
  }
  [[nodiscard]] bool validOperandType() const {
    return type != CactBasicType::Unknown && type != CactBasicType::Void && !isArray();
  }
  [[nodiscard]] bool validFormalParameterType() const {
    // dummy, need to be implemented
    return type != CactBasicType::Unknown && type != CactBasicType::Void;
  }

  [[nodiscard]] uint32_t dim() const {
    return arrayDims.size();
  }
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
