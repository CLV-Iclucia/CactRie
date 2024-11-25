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

static inline std::string type2String(CactBasicType basic_type) {
  const static std::map <CactBasicType, std::string> basic_typeToString = {
      {CactBasicType::Int32,  "int"   },
      {CactBasicType::Bool,   "bool"  },
      {CactBasicType::Float,  "float" },
      {CactBasicType::Double, "double"},
  };

  std::string result = basic_typeToString.at(basic_type);
  return result;
}


// the type of the Cact language
struct CactType {
  // attributes
  CactBasicType basic_type; // basic type
  std::vector<uint32_t> array_dims{}; // array dimensions as a vector
  bool is_param; // is parameter of a function

  // constructors
  explicit CactType() = default;

  explicit CactType(const CactBasicType basic_type) :
    basic_type(basic_type), is_param(false) {}

  explicit CactType(const CactBasicType basic_type, const bool is_param) :
    basic_type(basic_type), is_param(is_param) {}

  explicit CactType(const CactBasicType basic_type, const std::vector<uint32_t> array_dims, const bool is_param) :
    basic_type(basic_type), array_dims(array_dims), is_param(is_param) {}

  void addDim(const uint32_t dim) {
    this->array_dims.emplace_back(dim);
  }

  // get the size of this whole type
  [[nodiscard]]
  uint32_t size() const {
    uint32_t product = sizeOf(this->basic_type);
    for (auto dim : this->array_dims)
      product *= dim;
    return product;
  }

  // Get the size of the type inner than given dimension.
  // e.g. with "int a[2][2]",  a.size(1) == 2 * 4 == 8
  // This would equal to the size of a[0] or a[1]
  [[nodiscard]]
  uint32_t size(uint32_t _current_dim) const {
    uint32_t product = sizeOf(this->basic_type);
    uint32_t dimension = this->dim();
    for (uint32_t i = _current_dim; i < dimension; i++)
      product *= this->array_dims[i];
    return product;
  }

  // get the width of certain dimension
  [[nodiscard]]
  uint32_t width(uint32_t current_dim) const {
    return this->array_dims[current_dim];
  }

  // check if this type is an array
  [[nodiscard]]
  bool isArray() const {
    return !this->array_dims.empty();
  }

  // return the dimension of the array
  [[nodiscard]]
  uint32_t dim() const {
    return this->array_dims.size();
  }

  // check if this type is a valid operand
  [[nodiscard]]
  bool validOperandType() const {
    return this->basic_type != CactBasicType::Unknown && this->basic_type != CactBasicType::Void && !isArray();
  }

  // check if this type is a valid array index
  [[nodiscard]]
  bool validArrayIndex() const {
    return this->basic_type == CactBasicType::Int32 && !isArray();
  }

  // compare two CactType for equality
  [[nodiscard]]
  bool operator==(const CactType &rhs) const {
    return this->basic_type == rhs.basic_type && this->array_dims == rhs.array_dims;
  }

  // generate string from type
  [[nodiscard]]
  std::string toStringFull() const {
    std::string result = type2String(basic_type);
    for (auto dim : array_dims) {
      result += "[" + (dim > 0 ? std::to_string(dim) : "") + "]";
    }
    return result;
  }

  [[nodiscard]]
  std::string toString() const {
    std::string result = type2String(basic_type);
    if (isArray())
      result += "[]";
    return result;
  }

};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_TYPE_H_
