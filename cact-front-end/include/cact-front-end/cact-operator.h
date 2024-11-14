//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#include <cact-front-end/cact-expr.h>
#include <functional>
#include <set>

namespace cactfrontend {

struct OperandTypeCheck {
  const std::string errorMessage;
  const std::set<CactBasicType> validOprandTypeSet;

  // constructor
  explicit OperandTypeCheck(const std::string errorMessage, const std::set<CactBasicType> validOprandTypeSet) :
    errorMessage(std::move(errorMessage)), validOprandTypeSet(std::move(validOprandTypeSet)) {}
};

extern const OperandTypeCheck operandTypeCheckIntFloat;
extern const OperandTypeCheck operandTypeCheckInt;
extern const OperandTypeCheck operandTypeCheckBool;

struct Operator {
  [[nodiscard]]
  bool validOperandTypeBasic(const CactType type, const OperandTypeCheck &opTypeSet) const {
    if (!type.validOperandType()){
      throw std::runtime_error("expression must be a scalar");
      return false;
    }
    if (!opTypeSet.validOprandTypeSet.contains(type.basicType)) {
      throw std::runtime_error(opTypeSet.errorMessage);
      return false;
    }
    return true;
  }

  virtual bool validOperandTypeCheck(const CactType type) const = 0;

};

struct UnaryOperator : Operator {
  [[nodiscard]]
  virtual std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const = 0;
};

struct UnaryNopOperator : UnaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    switch(constEvalResultBasicType(x)) {
      case CactBasicType::Int32:
        return std::make_optional<ConstEvalResult>(std::get<int32_t>(x));
      case CactBasicType::Float:
        return std::make_optional<ConstEvalResult>(std::get<float>(x));
      case CactBasicType::Double:
        return std::make_optional<ConstEvalResult>(std::get<double>(x));
      case CactBasicType::Bool:
        return std::make_optional<ConstEvalResult>(std::get<bool>(x));
      default:
        return std::nullopt;
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return true;
  }
};

struct PlusOperator : UnaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    switch(constEvalResultBasicType(x)) {
      case CactBasicType::Int32:
        return std::make_optional<ConstEvalResult>(std::get<int32_t>(x));
      case CactBasicType::Float:
        return std::make_optional<ConstEvalResult>(std::get<float>(x));
      case CactBasicType::Double:
        return std::make_optional<ConstEvalResult>(std::get<double>(x));
      default:
        return std::nullopt;
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct NegOperator : UnaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    switch(constEvalResultBasicType(x)) {
      case CactBasicType::Int32:
        return std::make_optional<ConstEvalResult>(-std::get<int32_t>(x));
      case CactBasicType::Float:
        return std::make_optional<ConstEvalResult>(-std::get<float>(x));
      case CactBasicType::Double:
        return std::make_optional<ConstEvalResult>(-std::get<double>(x));
      default:
        return std::nullopt;
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct LogicalNotOperator : UnaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    if (constEvalResultBasicType(x) == CactBasicType::Bool)
      return std::make_optional<ConstEvalResult>(!std::get<bool>(x));
    return std::nullopt;
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckBool);
  }
};

struct BinaryOperator : Operator {
  [[nodiscard]]
  std::optional<ExpressionResult> evaluate(const EvalResult &lhs, const EvalResult &rhs) const {
    // if (!binaryArithmeticOperandCheck(lhs, rhs))
    //   return std::nullopt;
    auto lhs_value = lhs.compileTimeEvalResult();
    auto rhs_value = rhs.compileTimeEvalResult();
    if (!lhs_value.has_value() || !rhs_value.has_value())
      return std::make_optional<ExpressionResult>(lhs.type());
    auto result = apply(*lhs_value, *rhs_value);
    if (!result) return std::nullopt;
    return std::make_optional<ExpressionResult>(*result);
  }
  [[nodiscard]]
  virtual std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                               const ConstEvalResult &rhs) const = 0;

  // [[nodiscard]]
  bool binaryOperandCheck(const CactType &lhs, const CactType &rhs) const {
    if (lhs.basicType != rhs.basicType) {
      throw std::runtime_error("operands must have the same type");
      return false;
    }
    return validOperandTypeCheck(lhs) && validOperandTypeCheck(rhs);
  }
};

struct BinaryNopOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float) {
      return {std::get<float>(lhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double) {
      return {std::get<double>(lhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Bool) {
      return {std::get<bool>(lhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return true;
  }
};

struct AddOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) + std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) + std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) + std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct SubOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) - std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) - std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) - std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct MulOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) * std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) * std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) * std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct DivOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) / std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) / std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) / std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct ModOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) % std::get<int32_t>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckInt);
  }
};

struct LogicalOrOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Bool
        && constEvalResultBasicType(rhs) == CactBasicType::Bool) {
      return {std::get<bool>(lhs) || std::get<bool>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckBool);
  }
};

struct LogicalAndOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Bool
        && constEvalResultBasicType(rhs) == CactBasicType::Bool) {
      return {std::get<bool>(lhs) && std::get<bool>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckBool);
  }
};

// check if two ConstEvalResult have the same CactBasicType 
inline bool sameValidBasicType(const ConstEvalResult &x, const ConstEvalResult &y,
                               const std::set<CactBasicType> validTypes) {
  // if the type of x/y are among validTypes
  CactBasicType xType = constEvalResultBasicType(x);

  if (validTypes.find(xType) != validTypes.end()) {
    return xType == constEvalResultBasicType(y);
  }

  return false;
}

// get the value of a ConstEvalResult by its CactBasicType
// e.g. getValueByBasicType(variable, CactBasicType::Int32) -> std::get<int32_t>(variable)
template<typename T>
inline T getValueByBasicType(const ConstEvalResult &value, CactBasicType type) {
  switch(type) {
    case CactBasicType::Int32:  return std::get<int32_t>(value);
    case CactBasicType::Float:  return std::get<float>(value);
    case CactBasicType::Double: return std::get<double>(value);
    case CactBasicType::Bool:   return std::get<bool>(value);
    default:
      throw std::runtime_error("IMPORTANT: unknown basic type");
  }
}

struct LessOperator : BinaryOperator {


  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    // if (constEvalResultBasicType(lhs) == CactBasicType::Int32
    //     && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
    //   return {std::get<int32_t>(lhs) < std::get<int32_t>(rhs)};
    // } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
    //     && constEvalResultBasicType(rhs) == CactBasicType::Float) {
    //   return {std::get<float>(lhs) < std::get<float>(rhs)};
    // } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
    //     && constEvalResultBasicType(rhs) == CactBasicType::Double) {
    //   return {std::get<double>(lhs) < std::get<double>(rhs)};
    // } else {
    //   return {};
    // }

    // list of valid CactBasicType
    const std::set<CactBasicType> validTypes = {
      CactBasicType::Int32,
      CactBasicType::Float,
      CactBasicType::Double,
    };

    if (sameValidBasicType(lhs, rhs, validTypes)) {
      CactBasicType type = constEvalResultBasicType(lhs);
      return {getValueByBasicType<bool>(lhs, type) < getValueByBasicType<bool>(rhs, type)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct GreaterOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) > std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) > std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) > std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct LessEqualOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) <= std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) <= std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) <= std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct GreaterEqualOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) >= std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) >= std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) >= std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct EqualOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) == std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) == std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) == std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

struct NotEqualOperator : BinaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                       const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {std::get<int32_t>(lhs) != std::get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {std::get<float>(lhs) != std::get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {std::get<double>(lhs) != std::get<double>(rhs)};
    } else {
      return {};
    }
  }

  bool validOperandTypeCheck(const CactType type) const override {
    return validOperandTypeBasic(type, operandTypeCheckIntFloat);
  }
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
