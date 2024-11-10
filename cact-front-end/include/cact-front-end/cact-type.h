//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
#include <cstdint>
#include <vector>
#include <array>
#include <cassert>
#include <map>

namespace cactfrontend {

// the basic type of the Cact language
enum class CactBasicType : uint8_t {
  Unknown,  // unknown type
  Void,     // void type
  Int32,    // 32-bit signed integer
  Bool,     // boolean
  Float,    // 32-bit floating-point number
  Double,   // 64-bit floating-point number
};


// get the size of the basic type
inline uint32_t sizeOf(CactBasicType type) {
  // static std::array<uint32_t, 8> size ={
  //     0, 0, 4, 4, 4, 8,
  // };

  // setup a static dictionary from basic type to its size, with default value 0
  static std::map<CactBasicType, uint32_t> sizeOf = {
      // {CactBasicType::Unknown, 0},
      // {CactBasicType::Void   , 0},
      {CactBasicType::Int32  , 4},
      {CactBasicType::Bool   , 4},
      {CactBasicType::Float  , 4},
      {CactBasicType::Double , 8},
  };

  assert(type != CactBasicType::Unknown && type != CactBasicType::Void);
  return sizeOf[type];
}

// the type of the Cact language
struct CactType {
  // attributes
  CactBasicType basicType{}; // basic type
  bool isConst{}; // const type
  bool initialized{}; // initialized or not
  std::vector<uint32_t> arrayDims{}; // array dimensions as a vector
  bool isParam{}; // is parameter of a function

  // default constructor
  explicit CactType() = default;

  // constructor using basic type, const type
  explicit CactType(CactBasicType basicType, bool isConst)
    : basicType(basicType), isConst(isConst), initialized(isConst), arrayDims(std::vector<uint32_t>{}), isParam(false) {}

  // constructor using basic type, const type, initialized or not, and array dimensions
  explicit CactType(CactBasicType basicType, bool isConst, bool initialized, std::vector<uint32_t> arrayDims, bool isParam)
    : basicType(basicType), isConst(isConst), initialized(initialized), arrayDims(std::move(arrayDims)), isParam(isParam) {}

  // construct a constant type
  [[nodiscard]]
  static CactType constType(CactBasicType basicType) {
    return CactType(basicType, true);
  }

  // construct a variable type
  [[nodiscard]]
  static CactType varType(CactBasicType basicType) {
    return CactType(basicType, false);
  }

  // construct a parameter type
  [[nodiscard]]
  static CactType paramType(CactBasicType basicType, std::vector<uint32_t> arrayDims) {
    return CactType(basicType, false, true, arrayDims, true);
  }

  // get the size of this basicType
  uint32_t size() {
    uint32_t product = sizeOf(basicType);
    for (auto dim : arrayDims)
      product *= dim;
    return product;
  }

  // check if this type is an array
  [[nodiscard]] bool isArray() const {
    return !arrayDims.empty();
  }

  // check if this type is a valid operand
  [[nodiscard]] bool validOperandType() const {
    return basicType != CactBasicType::Unknown && basicType != CactBasicType::Void && !isArray();
  }

  // return the dimension of the array
  [[nodiscard]] uint32_t dim() const {
    return arrayDims.size();
  }
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
