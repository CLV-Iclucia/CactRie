//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_H_
#include <cact-parser/CactParser.h>
#include <cact-parser/cact-expr.h>
#include <functional>
namespace cactparser {

struct UnaryOperator {
  [[nodiscard]] virtual std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const = 0;
};

struct PlusOperator : UnaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    switch(constEvalResultBasicType(x)) {
      case CactBasicType::Int32:
        return std::make_optional<ConstEvalResult>(get<int32_t>(x));
      case CactBasicType::Float:
        return std::make_optional<ConstEvalResult>(get<float>(x));
      case CactBasicType::Double:
        return std::make_optional<ConstEvalResult>(get<double>(x));
      default:
        return std::nullopt;
    }
  }
};

struct NegOperator : UnaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    switch(constEvalResultBasicType(x)) {
      case CactBasicType::Int32:
        return std::make_optional<ConstEvalResult>(-get<int32_t>(x));
      case CactBasicType::Float:
        return std::make_optional<ConstEvalResult>(-get<float>(x));
      case CactBasicType::Double:
        return std::make_optional<ConstEvalResult>(-get<double>(x));
      default:
        return std::nullopt;
    }
  }
};

struct LogicalNotOperator : UnaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult& x) const override {
    if (constEvalResultBasicType(x) == CactBasicType::Bool)
      return std::make_optional<ConstEvalResult>(!get<bool>(x));
    return std::nullopt;
  }
};

struct BinaryOperator {
  [[nodiscard]] std::optional<ExpressionResult> evaluate(const EvalResult &lhs, const EvalResult &rhs) const {
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
  [[nodiscard]] virtual std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                             const ConstEvalResult &rhs) const = 0;
};

struct AddOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs, const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) + get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) + get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) + get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct SubOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs, const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) - get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) - get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) - get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct MulOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs, const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) * get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) * get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) * get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct DivOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) / get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) / get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) / get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct ModOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) % get<int32_t>(rhs)};
    } else {
      return {};
    }
  }
};

struct LogicalOrOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Bool
        && constEvalResultBasicType(rhs) == CactBasicType::Bool) {
      return {get<bool>(lhs) || get<bool>(rhs)};
    } else {
      return {};
    }
  }
};

struct LogicalAndOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Bool
        && constEvalResultBasicType(rhs) == CactBasicType::Bool) {
      return {get<bool>(lhs) && get<bool>(rhs)};
    } else {
      return {};
    }
  }
};

struct LessOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) < get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) < get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) < get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct GreaterOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) > get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) > get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) > get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct LessEqualOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) <= get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) <= get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) <= get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct GreaterEqualOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) >= get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) >= get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) >= get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct EqualOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) == get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) == get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) == get<double>(rhs)};
    } else {
      return {};
    }
  }
};

struct NotEqualOperator : BinaryOperator {
  [[nodiscard]] std::optional<ConstEvalResult> apply(const ConstEvalResult &lhs,
                                                     const ConstEvalResult &rhs) const override {
    if (constEvalResultBasicType(lhs) == CactBasicType::Int32
        && constEvalResultBasicType(rhs) == CactBasicType::Int32) {
      return {get<int32_t>(lhs) != get<int32_t>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Float
        && constEvalResultBasicType(rhs) == CactBasicType::Float) {
      return {get<float>(lhs) != get<float>(rhs)};
    } else if (constEvalResultBasicType(lhs) == CactBasicType::Double
        && constEvalResultBasicType(rhs) == CactBasicType::Double) {
      return {get<double>(lhs) != get<double>(rhs)};
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
