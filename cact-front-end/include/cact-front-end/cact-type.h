//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
#include <cstdint>
#include <vector>
#include <string>
#include <cassert>
#include <map>

namespace cactfrontend {

// the basic type of the Cact language
enum class CactBasicType : uint8_t {
  Unknown, // unknown type
  Void,    // void type
  Int32,   // 32-bit signed integer
  Bool,    // boolean
  Float,   // 32-bit floating-point number
  Double,  // 64-bit floating-point number
};


// get the size of the basic type
static inline uint32_t sizeOf(CactBasicType type) {
  // setup a static dictionary from basic type to its size, with default value 0
  const static std::map<CactBasicType, uint32_t> sizeOf = {
      {CactBasicType::Int32  , 4},
      {CactBasicType::Bool   , 4},
      {CactBasicType::Float  , 4},
      {CactBasicType::Double , 8},
  };

  assert(type != CactBasicType::Unknown && type != CactBasicType::Void);
  return sizeOf.at(type);
}

static inline std::string type2String(CactBasicType basicType) {
  const static std::map <CactBasicType, std::string> basicTypeToString = {
      {CactBasicType::Int32,  "int"   },
      {CactBasicType::Bool,   "bool"  },
      {CactBasicType::Float,  "float" },
      {CactBasicType::Double, "double"},
  };

  std::string result = basicTypeToString.at(basicType);
  return std::move(result);
}


// the type of the Cact language
struct CactType {
  // attributes
  CactBasicType basicType{}; // basic type
  std::vector<uint32_t> arrayDims{}; // array dimensions as a vector
  bool isParam{}; // is parameter of a function

  // constructor
  explicit CactType() = default;
  explicit CactType(CactBasicType basicType, bool isParam) : basicType(basicType), isParam(isParam) {}
  explicit CactType(CactBasicType basicType, std::vector<uint32_t> arrayDims, bool isParam) :
    basicType(basicType), arrayDims(arrayDims), isParam(isParam) {}

  // initialize the type
  void init(CactBasicType basicType, bool isParam) {
    this->basicType = basicType;
    this->isParam = isParam;
    this->arrayDims.clear();
  }

  void addDim(uint32_t dim) {
    this->arrayDims.push_back(dim);
  }

  // get the size of this basicType
  uint32_t size() {
    uint32_t product = sizeOf(this->basicType);
    for (auto dim : this->arrayDims)
      product *= dim;
    return product;
  }

  // check if this type is an array
  [[nodiscard]]
  bool isArray() const {
    return !this->arrayDims.empty();
  }

  // check if this type is a valid operand
  [[nodiscard]]
  bool validOperandType() const {
    return this->basicType != CactBasicType::Unknown && this->basicType != CactBasicType::Void && !isArray();
  }

  // check if this type is a valid array index
  [[nodiscard]]
  bool validArrayIndex() const {
    return this->basicType == CactBasicType::Int32 && !isArray();
  }

  // return the dimension of the array
  [[nodiscard]]
  uint32_t dim() const {
    return this->arrayDims.size();
  }

  // compare two CactType for equality
  [[nodiscard]]
  bool operator==(const CactType &rhs) const {
    return this->basicType == rhs.basicType && this->arrayDims == rhs.arrayDims;
  }

  // generate std::string from type
  [[nodiscard]]
  std::string toStringFull() const {
    std::string result = type2String(basicType);
    for (auto dim : arrayDims) {
      result += "[" + (dim > 0 ? std::to_string(dim) : "") + "]";
    }
    return std::move(result);
  }

  [[nodiscard]]
  std::string toString() const {
    std::string result = type2String(basicType);
    if (isArray())
      result += "[]";
    return std::move(result);
  }

};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
