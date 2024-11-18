//
// Created by creeper on 8/15/24.
//

#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/cact-typedef.h>
#include <cact-front-end/cact-type.h>
#include <cact-front-end/cact-expr.h>
#include <optional>
#include <memory>

namespace cactfrontend {


// get a CactType based on the type of the variant
CactType constEvalResultType(const ConstEvalResult value) {
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
CactBasicType constEvalResultBasicType(const ConstEvalResult value) {
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
inline std::optional<bool> conditionEvalResult(const ConstEvalResult value) {
  if (constEvalResultBasicType(value) == CactBasicType::Bool)
    return std::make_optional<bool>(std::get<bool>(value));
  else return std::nullopt;
}


[[nodiscard]]
observer_ptr<CactExpr> getObserverPtrExpr(CactExpr expr) {
    return make_observer<CactExpr>(std::make_unique<CactExpr>(expr).get());
}

[[nodiscard]]
observer_ptr<CactExpr> getObserverPtrBiExpr(CactBinaryExpr expr) {
    return make_observer<CactExpr>((CactExpr *)(std::make_unique<CactBinaryExpr>(expr).get()));
}

}
