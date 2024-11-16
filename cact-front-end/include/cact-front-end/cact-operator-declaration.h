//
// Created by sailinbay on Nov 13, 2024.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_FUNCTION_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_FUNCTION_H_

#include <cact-front-end/CactParser.h>
#include <functional>
#include <set>

namespace cactfrontend {


std::unique_ptr<BinaryOperator> binaryOperator(CactParser::MulExpressionContext &ctx);
std::unique_ptr<BinaryOperator> binaryOperator(CactParser::AddExpressionContext &ctx);
std::unique_ptr<BinaryOperator> binaryOperator(CactParser::RelationalExpressionContext &ctx);
std::unique_ptr<BinaryOperator> binaryOperator(CactParser::LogicalEqualExpressionContext &ctx);
std::unique_ptr<UnaryOperator> unaryOperator(CactParser::UnaryExpressionContext &ctx);

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_OPERATOR_FUNCTION_H_
