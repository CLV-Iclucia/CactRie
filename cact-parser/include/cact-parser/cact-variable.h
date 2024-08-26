//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_VARIABLE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_VARIABLE_H_
#include <cact-parser/cact-expr.h>
#include <string>
namespace cactparser {
struct CactVariable {
  explicit CactVariable(const CactType& type) : value(type) {}
  ExpressionResult value;
  [[nodiscard]] CactType type() const {
    return value.type();
  }
};
}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_VARIABLE_H_
