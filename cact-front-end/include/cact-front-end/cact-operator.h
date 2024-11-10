//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-expr.h>
#include <functional>
namespace cactfrontend {

struct UnaryOperator {
  [[nodiscard]]
  virtual std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const = 0;
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
};

struct LogicalNotOperator : UnaryOperator {
  [[nodiscard]]
  std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    if (constEvalResultBasicType(x) == CactBasicType::Bool)
      return std::make_optional<ConstEvalResult>(!std::get<bool>(x));
    return std::nullopt;
  }
};

struct BinaryOperator {
  [[nodiscard]]
  std::optional<ExpressionResult> evaluate(const EvalResult &lhs, const EvalResult &rhs) const {
    if (!binaryArithmeticOperandCheck(lhs, rhs))
      return std::nullopt;
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
      throw std::runtime_error("Invalid basic type");
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
};

std::unique_ptr<BinaryOperator> binaryOperator(CactParser::MulExpressionContext &ctx);
std::unique_ptr<BinaryOperator> binaryOperator(CactParser::AddExpressionContext &ctx);
std::unique_ptr<BinaryOperator> binaryOperator(CactParser::RelationalExpressionContext &ctx);
std::unique_ptr<BinaryOperator> binaryOperator(CactParser::LogicalEqualExpressionContext &ctx);
std::unique_ptr<UnaryOperator> unaryOperator(CactParser::UnaryExpressionContext &ctx);

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
