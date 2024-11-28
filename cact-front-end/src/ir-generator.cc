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

  ifID.emplace_back(0);
  whileID.emplace_back(0);
  for (auto item : funcBody->blockItem()) {
    if (auto stmt = item->statement())
      irCodeStream << statementIRGen({}, stmt);
  }
  irCodeStream << "}\n";
  return {};
}

std::string LLVMIRGenerator::returnStatementIRGen(const std::string &labelPrefix,
                                                  CactParser::ReturnStatementContext *ctx) {
  if (ctx->expression()) {
    const auto &[code, regName] = evaluationCodeGen(ctx->expr);
    return code + std::format("ret {} %{}\n",
                              basicTypeString(ctx->expr->resultBasicType()),
                              regName);
  } else
    return std::format("ret void\n");
}

std::string LLVMIRGenerator::statementIRGen(const std::string &labelPrefix, CactParser::StatementContext *ctx) {
  if (auto ifCtx = ctx->ifStatement()) {
    auto reduced = reduceIfBranch(ifCtx);
    if (reduced)
      return statementIRGen(labelPrefix, reduced.value());
    const auto &ifLabel = std::format("{}.if{}", labelPrefix, ifID.back()++);
    return ifStatementIRGen(ifLabel, ifCtx);
  } else if (auto whileCtx = ctx->whileStatement()) {
    auto reduced = reduceWhileLoop(whileCtx);
    if (reduced)
      return statementIRGen(labelPrefix, reduced.value());
    const auto &whileLabel = std::format("{}.while{}", labelPrefix, whileID.back()++);
    return whileStatementIRGen(whileLabel, whileCtx);
  } else if (auto returnCtx = ctx->returnStatement()) {
    return returnStatementIRGen(labelPrefix, returnCtx);
  } else if (auto exprCtx = ctx->expressionStatement()) {
    const auto &[code, regName] = evaluationCodeGen(exprCtx->expr);
    return code;
  } else if (auto assignCtx = ctx->assignStatement()) {
    const auto &[lhsFetchCode, lvaluePtrRegName] = fetchAddressCodeGen(assignCtx->lvalue);
    const auto &[rhsEvalCode, rhsRegName] = evaluationCodeGen(assignCtx->expr);
    return lhsFetchCode + rhsEvalCode
        + std::format("store {} %{}, {}* %{}\n",
                      basicTypeString(assignCtx->expr->resultBasicType()),
                      rhsRegName,
                      basicTypeString(assignCtx->lvalue->resultBasicType()),
                      lvaluePtrRegName);
  } else if (ctx->breakStatement()) {
    return std::format("br label %{}\n", endingLabel(labelPrefix));
  } else if (ctx->continueStatement()) {
    return std::format("br label %{}\n", condCheckLabel(labelPrefix));
  } else if (ctx->block()) {
    ifID.emplace_back(0);
    whileID.emplace_back(0);
    for (auto item : ctx->block()->blockItem())
      if (auto stmt = item->statement())
        irCodeStream << statementIRGen({}, stmt);
    ifID.pop_back();
    whileID.pop_back();
  } else
    throw std::runtime_error("unsupported statement type");
  return "";
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
  auto thenBranch = ctx->statement(0);
  auto elseBranch = ctx->statement().size() == 2 ? ctx->statement(1) : nullptr;
  const auto &thenBranchCode = statementIRGen(thenBranchLabel(labelPrefix), thenBranch);
  if (!elseBranch)
    return condEvalCode
        + std::format("br i1 %{}, label %{}, label %{}\n", condRegName, thenBranchLabel(labelPrefix),
                      endingLabel(labelPrefix))
        + thenBranchLabel(labelPrefix) + ":\n"
        + thenBranchCode
        + std::format("br label %{}\n", endingLabel(labelPrefix));
  const auto &elseBranchCode = statementIRGen(elseBranchLabel(labelPrefix), elseBranch);
  return condEvalCode
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
  if (type == CactBasicType::Int32)
    return intOpMap.at(typeid(op));
  else
    return floatOpMap.at(typeid(op));
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::evaluationCodeGen(std::shared_ptr<CactExpr> expr) {
  if (expr == nullptr)
    return {};
  if (expr->isConstant()) {
    return {
        .code = "",
        .result = std::visit([](auto &&arg) {
          return std::to_string(arg);
        }, expr->getConstantValue())
    };
  } else if (expr->isBinaryExpression()) {
    const auto &lhs = evaluationCodeGen(expr->left_expr);
    const auto &rhs = evaluationCodeGen(expr->right_expr);
    const auto &lhsReg = lhs.result;
    const auto &rhsReg = rhs.result;
    const auto &op = expr->binary_operator;
    const auto &resultReg = assignReg();
    return {
        .code = lhs.code + rhs.code
            + std::format("%{} = {} {} %{}, %{}\n",
                          resultReg,
                          binaryToLLVMOp(*op, expr->resultBasicType()),
                          basicTypeString(expr->resultBasicType()),
                          lhsReg, rhsReg),
        .result = resultReg
    };
  } else if (expr->isVariable()) {
    return variableEvaluationCodeGen(expr->variable);
  } else if (expr->isFunctionCall()) {
    const auto &func = expr->function;
    const auto &args = expr->args;
    std::string argList;
    for (size_t i = 0; i < args.size(); ++i) {
      const auto &arg = args[i];
      const auto &argReg = evaluationCodeGen(arg).result;
      argList += std::format("{} %{}", basicTypeString(arg->resultBasicType()), argReg);
      if (i != args.size() - 1)
        argList += ", ";
    }
    const auto &resultReg = temporaryName(temporaryID++);
    return {
        .code = std::format("%{} = call {} @{}({})\n",
                            resultReg,
                            basicTypeString(func->return_type),
                            func->name,
                            argList),
        .result = resultReg
    };
  }

  if (expr->isUnaryExpression()) {
    const auto &unaryOp = expr->unary_operator;
    const auto &operand = evaluationCodeGen(expr->expr);
    const auto &operandReg = operand.result;
    const auto &resultReg = temporaryName(temporaryID++);
    return {
        .code = operand.code
            + std::format("%{} = {} {} %{}\n",
                          resultReg,
                          unaryOp->unaryOpString(),
                          basicTypeString(expr->resultBasicType()),
                          operandReg),
        .result = resultReg
    };
  }
  throw std::runtime_error("unsupported expression type");
}

void LLVMIRGenerator::allocateVariable(std::shared_ptr<CactConstVar> var, const std::string &newName) {
  // Handle array type variables
  if (var->type.isArray()) {
    irCodeStream << std::format("%{} = alloca {} {}\n", address(newName),
                                basicTypeString(var->type.basic_type),
                                var->type.size());

    if (var->isInitialized()) {
      for (size_t i = 0; i < var->init_values.size(); ++i) {
        const auto &ptrReg = temporaryName(temporaryID++);
        irCodeStream << std::format("%{} = getelementptr {} {}, {}* {}, i32 {}\n",
                                    ptrReg,
                                    basicTypeString(var->type.basic_type),
                                    basicTypeString(var->type.basic_type),
                                    address(newName),
                                    i);
        const auto &initValStr = std::visit([](auto &&arg) {
          return std::to_string(arg);
        }, var->init_values[i]);
        irCodeStream << std::format("store {} {}, {}* %{}\n",
                                    basicTypeString(var->type.basic_type),
                                    initValStr,
                                    basicTypeString(var->type.basic_type),
                                    ptrReg);
      }
    }
  } else {
    // handle scalar type variables
    irCodeStream << std::format("%{} = alloca {}\n", address(newName),
                                basicTypeString(var->type.basic_type));
    if (var->isInitialized()) {
      const auto &initValStr = std::visit([](auto &&arg) {
        return std::to_string(arg);
      }, var->init_values.at(0));
      irCodeStream << std::format("store {} {}, {}* %{}\n",
                                  basicTypeString(var->type.basic_type),
                                  initValStr,
                                  basicTypeString(var->type.basic_type),
                                  address(newName));
    }
  }
}

void LLVMIRGenerator::allocateLocalVariables(CactParser::BlockContext *block, int depth) {
  // Process variable declarations in the current block
  for (auto item : block->blockItem())
    if (auto decl = item->declaration())
      if (auto varDecl = decl->variableDeclaration())
        for (auto varDef : varDecl->variableDefinition())
          allocateVariable(varDef->variable, rename(varDef->variable));

  // Recursively handle nested blocks
  for (auto item : block->blockItem())
    if (auto stmt = item->statement())
      if (auto nestedBlock = stmt->block())
        allocateLocalVariables(nestedBlock, depth + 1);
}

void LLVMIRGenerator::allocateLocalVariables(CactParser::BlockContext *block) {
  allocateLocalVariables(block, 0);
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::indexOpCodeGen(std::shared_ptr<CactExpr> lhs,
                                                                         std::shared_ptr<CactExpr> rhs,
                                                                         IndexResolvingMode mode) {
  assert(lhs->isVariable());
  assert(rhs->resultBasicType() == CactBasicType::Int32);
  auto fetchStart = fetchAddressCodeGen(lhs);
  auto idxEval = evaluationCodeGen(rhs);
  const auto &startReg = fetchStart.result;
  const auto &idxReg = idxEval.result;

  const auto &ptrReg = assignReg();

  const auto &gepInst = std::format("%{} = getelementptr {}, {}* %{}, i32 %{}\n",
                                    ptrReg,
                                    basicTypeString(lhs->resultBasicType()),
                                    basicTypeString(rhs->resultBasicType()),
                                    startReg,
                                    idxReg);

  if (mode == Address)
    return {.code = fetchStart.code + idxEval.code + gepInst,
        .result = ptrReg};
  else if (mode == Value) {
    const auto &loadReg = assignReg();
    return {.code = fetchStart.code + idxEval.code + gepInst
        + std::format("%{} = load {}, {}* %{}\n",
                      loadReg,
                      basicTypeString(lhs->resultBasicType()),
                      basicTypeString(lhs->resultBasicType()),
                      ptrReg),
        .result = loadReg};
  } else
    throw std::runtime_error("unsupported mode");
}

// when this is visited, it must be global variable/constant
std::any LLVMIRGenerator::visitDeclaration(CactParser::DeclarationContext *ctx) {
  if (auto varDecl = ctx->variableDeclaration()) {
    for (auto varDef : varDecl->variableDefinition()) {
      const auto &var = varDef->variable;
      assert(registry->isGlobal(var));
      irCodeStream << std::format("@{} = global {} {}\n",
                                  var->name,
                                  basicTypeString(var->type.basic_type),
                                  var->isInitialized() ? std::visit([](auto &&arg) {
                                    return std::to_string(arg);
                                  }, var->init_values.at(0)) : "");
    }
  }
  return {};
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::fetchAddressCodeGen(std::shared_ptr<CactExpr> expr) {
  assert(expr->isVariable());
  const auto &var = expr->variable;
  if (!var->indexing_times) {
    return {
        .code = "",
        .result = addressOf(var->symbol)
    };
  }
  const auto &indexEval = evaluationCodeGen(var->offset);
  const auto &indexReg = indexEval.result;
  const auto &ptrReg = assignReg();
  const auto &gepInst = std::format("%{} = getelementptr {}, {}* {}, i32 {}\n",
                                    ptrReg,
                                    basicTypeString(var->symbol->type.basic_type),
                                    basicTypeString(var->offset->resultBasicType()),
                                    addressOf(var->symbol),
                                    indexReg);
  return {
      .code = indexEval.code + gepInst,
      .result = ptrReg
  };
}
LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::variableEvaluationCodeGen(std::shared_ptr<CactConstVarArray> var) {
  const auto &regName = assignReg();
  return {
      .code = std::format("%{} = load {}, {}\n",
                          regName,
                          basicTypeString(var->symbol->type.basic_type),
                          addressOf(var->symbol)),
      .result = regName
  };
}

}