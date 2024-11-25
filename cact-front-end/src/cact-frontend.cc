//
// Created by creeper on 8/15/24.
//

#include <cact-front-end/cact-typedef.h>
#include <cact-front-end/cact-type.h>
#include <cact-front-end/cact-expr.h>
#include <optional>
#include <memory>

namespace cactfrontend {


// get a CactType based on the type of the variant
CactType constEvalResultType(ConstEvalResult value) {
  // return a CactType object based on the type of the variant
  if (std::holds_alternative<int32_t>(value)) {
    return CactType(CactBasicType::Int32, false);
  } else if (std::holds_alternative<float>(value)) {
    return CactType(CactBasicType::Float, false);
  } else if (std::holds_alternative<double>(value)) {
    return CactType(CactBasicType::Double, false);
  } else {
    return CactType(CactBasicType::Bool, false);
  }
}

// get the basic type of the variant
CactBasicType constEvalResultBasicType(ConstEvalResult value) {
  if (std::holds_alternative<int32_t>(value)) {
    return CactBasicType::Int32;
  } else if (std::holds_alternative<float>(value)) {
    return CactBasicType::Float;
  } else if (std::holds_alternative<double>(value)) {
    return CactBasicType::Double;
  } else if (std::holds_alternative<bool>(value)) {
    return CactBasicType::Bool;
  } else {
    return CactBasicType::Unknown;
  }
}

// get the value of the variant
inline std::optional<bool> conditionEvalResult(ConstEvalResult value) {
  if (constEvalResultBasicType(value) == CactBasicType::Bool)
    return std::make_optional<bool>(std::get<bool>(value));
  else return std::nullopt;
}

}
