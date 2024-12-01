//
// Created by creeper on 12/1/24.
//

#ifndef CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_LOCAL_VAR_COLLECTOR_H
#define CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_LOCAL_VAR_COLLECTOR_H
#include <cact-front-end/CactParserBaseVisitor.h>
namespace cactfrontend {
struct LocalVarCollector : CactParserBaseVisitor {
  std::any visitVariableDefinition(CactParser::VariableDefinitionContext *ctx) override {
    localVars.emplace_back(ctx->variable);
    return {};
  }
  std::vector<std::shared_ptr<CactConstVar>> localVars{};
};
}
#endif //CACTRIE_CACT_FRONT_END_INCLUDE_CACT_FRONT_END_LOCAL_VAR_COLLECTOR_H
