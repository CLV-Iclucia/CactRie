//
// Created by creeper on 11/24/24.
//
#include <typeindex>
#include <cact-front-end/ir-generator.h>

namespace cactfrontend {

static std::string endingLabel(const std::string &label) {
  return std::format("{}.end", label);
}

static std::string loopBodyLabel(const std::string &label) {
  return std::format("{}.loop", label);
}

static std::string condCheckLabel(const std::string &label) {
  return std::format("{}.cond", label);
}

static std::string thenBranchLabel(const std::string &label) {
  return std::format("{}.then", label);
}

static std::string elseBranchLabel(const std::string &label) {
  return std::format("{}.else", label);
}

static std::string address(const std::string &name) {
  return std::format("%{}.addr", name);
}

std::optional<CactParser::StatementContext *> LLVMIRGenerator::reduceIfBranch(CactParser::IfStatementContext *ctx) {
  if (!ctx->cond_expr->isConstant())
    return std::nullopt;
  auto condVal = std::get<bool>(ctx->cond_expr->getConstantValue());
  if (condVal) {
    auto then = ctx->statement(0);
    return reduceStatement(then);
  } else {
    if (ctx->statement().size() == 1)
      return std::make_optional(nullptr);
    else if (ctx->statement().size() == 2) {
      auto elseBranch = ctx->statement(1);
      return reduceStatement(elseBranch);
    }
    throw std::runtime_error("if statement has more than 2 branches");
  }
}

std::optional<CactParser::StatementContext *> LLVMIRGenerator::reduceWhileLoop(CactParser::WhileStatementContext *ctx) {
  if (!ctx->cond_expr->isConstant())
    return std::nullopt;
  auto condVal = std::get<bool>(ctx->cond_expr->getConstantValue());
  if (condVal)
    return std::nullopt;
  else
    return std::make_optional(nullptr);
}

std::optional<CactParser::StatementContext *> LLVMIRGenerator::reduceStatement(CactParser::StatementContext *ctx) {
  if (ctx->ifStatement()) {
    return reduceIfBranch(ctx->ifStatement());
  } else if (ctx->whileStatement()) {
    return reduceWhileLoop(ctx->whileStatement());
  } else
    return std::make_optional(ctx);
}

std::any LLVMIRGenerator::visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) {
  // visit all children
  irCodeStream
      << std::format("define {} @{}(", type2String(ctx->function->return_type), ctx->Identifier()->getText());

  ifID.clear();
  whileID.clear();
  localIdentifierMangler.clear();

  for (auto &param : ctx->function->parameters) {
    auto type = param.type;
    std::string typeStr = basicTypeString(type.basic_type) + (type.isArray() ? "*" : "");
    irCodeStream << std::format("{} %{}", typeStr, param.name);
    if (&param != &ctx->function->parameters.back())
      irCodeStream << ", ";
  }

  irCodeStream << ")\n";
  auto funcBody = ctx->block();
  irCodeStream << "{\n";
  irCodeStream << "entry:\n";

  allocateLocalVariables(funcBody);

  // use ranges to rewrite the above code
  ifID.emplace_back(0);
  whileID.emplace_back(0);
  for (auto item : funcBody->blockItem()) {
    if (auto stmt = item->statement())
      irCodeStream << statementIRGen({}, stmt);
  }
  irCodeStream << "}\n";
  return {};
}
std::string LLVMIRGenerator::statementIRGen(const std::string &labelPrefix, CactParser::StatementContext *ctx) {
  if (ctx->ifStatement()) {
    auto ifCtx = ctx->ifStatement();
    auto reduced = reduceIfBranch(ifCtx);
    if (reduced)
      return statementIRGen(labelPrefix, reduced.value());
    const auto &ifLabel = std::format("{}.if{}", labelPrefix, ifID.back()++);
    return ifStatementIRGen(ifLabel, ifCtx);
  }
  if (ctx->whileStatement()) {
    auto whileCtx = ctx->whileStatement();
    auto reduced = reduceWhileLoop(whileCtx);
    if (reduced)
      return statementIRGen(labelPrefix, reduced.value());
    const auto &whileLabel = std::format("{}.while{}", labelPrefix, whileID.back()++);
    return whileStatementIRGen(whileLabel, whileCtx);
  }
  if (ctx->returnStatement()) {
    auto returnCtx = ctx->returnStatement();
    if (returnCtx->expression()) {
      const auto &[code, regName] = evaluationCodeGen(returnCtx->expr);
      return code + std::format("ret {} %{}\n",
                                basicTypeString(returnCtx->expr->resultBasicType()),
                                regName);
    } else {
      return std::format("ret void\n");
    }
  }
  if (ctx->expressionStatement()) {

  }
  if (ctx->assignStatement()) {

  }
  if (ctx->breakStatement()) {
    return std::format("br label %{}\n", endingLabel(labelPrefix));
  }
  if (ctx->continueStatement()) {
    return std::format("br label %{}\n", condCheckLabel(labelPrefix));
  }
  if (ctx->block()) {
    ifID.emplace_back(0);
    whileID.emplace_back(0);
    for (auto item : ctx->block()->blockItem()) {
      if (auto stmt = item->statement())
        irCodeStream << statementIRGen({}, stmt);
    }
  }
  return {};
}
std::string LLVMIRGenerator::whileStatementIRGen(const std::string &labelPrefix,
                                                 CactParser::WhileStatementContext *ctx) {
  assert(!ctx->cond_expr->isConstant());
  const auto &[condEvalCode, condRegName] = evaluationCodeGen(ctx->cond_expr);
  const auto &loopBodyCode = statementIRGen(loopBodyLabel(labelPrefix), ctx->statement());
  const auto &endLabel = endingLabel(labelPrefix);
  return std::format("br label %{}\n", condCheckLabel(labelPrefix))
      + condCheckLabel(labelPrefix) + ":\n"
      + condEvalCode
      + std::format("br i1 %{}, label %{}, label %{}\n", condRegName, loopBodyLabel(labelPrefix), endLabel)
      + loopBodyLabel(labelPrefix) + ":\n"
      + loopBodyCode
      + std::format("br label %{}\n", condCheckLabel(labelPrefix))
      + endLabel + ":\n";
}
std::string LLVMIRGenerator::ifStatementIRGen(const std::string &labelPrefix, CactParser::IfStatementContext *ctx) {
  assert(!ctx->cond_expr->isConstant());
  const auto &[condEvalCode, condRegName] = evaluationCodeGen(ctx->cond_expr);
  const auto &thenBranchCode = statementIRGen(thenBranchLabel(labelPrefix), ctx->statement(0));
  if (ctx->statement().size() == 1)
    return condEvalCode + "\n"
        + std::format("br i1 %{}, label %{}, label %{}\n", condRegName, thenBranchLabel(labelPrefix),
                      endingLabel(labelPrefix))
        + thenBranchLabel(labelPrefix) + ":\n"
        + thenBranchCode
        + std::format("br label %{}\n", endingLabel(labelPrefix));
  const auto &elseBranchCode = statementIRGen(elseBranchLabel(labelPrefix), ctx->statement(1));
  return condEvalCode + "\n"
      + std::format("br i1 %{}, label %{}, label %{}\n", condRegName, thenBranchLabel(labelPrefix),
                    elseBranchLabel(labelPrefix))
      + thenBranchLabel(labelPrefix) + ":\n"
      + thenBranchCode
      + std::format("br label %{}\n", endingLabel(labelPrefix))
      + elseBranchLabel(labelPrefix) + ":\n"
      + elseBranchCode
      + std::format("br label %{}\n", endingLabel(labelPrefix));
}

static std::string binaryToLLVMOp(const BinaryOperator &op, CactBasicType type) {
  assert(type != CactBasicType::Void && type != CactBasicType::Unknown);
  static std::map<std::type_index, std::string> intOpMap = {
      {typeid(AddOperator), "add"},
      {typeid(SubOperator), "sub"},
      {typeid(MulOperator), "mul"},
      {typeid(DivOperator), "sdiv"},
      {typeid(ModOperator), "srem"},
  };
  static std::map<std::type_index, std::string> floatOpMap = {
      {typeid(AddOperator), "fadd"},
      {typeid(SubOperator), "fsub"},
      {typeid(MulOperator), "fmul"},
      {typeid(DivOperator), "fdiv"},
  };
  if (type == CactBasicType::Int32) {
    return intOpMap.at(typeid(op));
  } else {
    return floatOpMap.at(typeid(op));
  }
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::evaluationCodeGen(std::shared_ptr<CactExpr> expr) {
  assert(!expr->isConstant());
  if (expr->isBinaryExpression()) {
    auto lhs = evaluationCodeGen(expr->left_expr);
    auto rhs = evaluationCodeGen(expr->right_expr);
    const auto &lhsReg = lhs.resultName;
    const auto &rhsReg = rhs.resultName;
    const auto &op = expr->binary_operator;
    if (auto idxOp = std::dynamic_pointer_cast<IndexOperator>(op)) {
      const auto &arrayReg = lhsReg;
      const auto &indexReg = rhsReg;
      const auto &resultReg = temporaryName(temporaryID++);
      assert(expr->right_expr->resultBasicType() == CactBasicType::Int32);
      return {.code =
      lhs.code + rhs.code
          + std::format("%{} = getelementptr inbounds {}, {}* %{}, i32 %{}\n",
                        resultReg,
                        basicTypeString(expr->left_expr->resultBasicType()),
                        basicTypeString(expr->right_expr->resultBasicType()),
                        arrayReg,
                        indexReg),
          .resultName = resultReg};
    }
    return {.code =
    lhs.code + rhs.code
        + std::format("%{} = {} {} {}, {}\n",
                      temporaryName(temporaryID++),
                      binaryToLLVMOp(*op, expr->resultBasicType()),
                      basicTypeString(expr->resultBasicType()),
                      lhsReg,
                      rhsReg),
        .resultName = temporaryName(temporaryID++)
    };
  }
  throw std::runtime_error("unsupported expression type");
}

void LLVMIRGenerator::allocateLocalVariables(CactParser::BlockContext *block, int depth) {
  for (auto item : block->blockItem())
    if (auto decl = item->declaration())
      if (auto varDecl = decl->variableDeclaration()) {
        for (auto varDef : varDecl->variableDefinition()) {
          const auto &originalName = varDef->Identifier()->getText();
          const auto &newName = renameLocalIdentifier(originalName, block);
          irCodeStream << std::format("{} = alloca {}\n", address(newName), basicTypeString(varDef->need_type));

        }
      }

  for (auto item : block->blockItem())
    if (auto stmt = item->statement())
      if (auto nestedBlock = stmt->block())
        allocateLocalVariables(nestedBlock, depth + 1);
}

void LLVMIRGenerator::allocateLocalVariables(CactParser::BlockContext *block) {
  allocateLocalVariables(block, 0);
}

}