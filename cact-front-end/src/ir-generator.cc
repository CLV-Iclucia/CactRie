//
// Created by creeper on 11/24/24.
//
#include <typeindex>
#include <regex>
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

static std::string shortCircuitThenLabel(const std::string &label) {
  return std::format("{}.sc.then", label);
}

static std::string shortCircuitElseLabel(const std::string &label) {
  return std::format("{}.sc.else", label);
}

// for a label, find the label corresponding to the nearest inner while loop
static std::string innerWhileLabel(const std::string &label) {
  std::regex whileRegex(R"(while\d+)");
  size_t pos = label.size();

  while (pos != std::string::npos) {
    size_t prvPos = label.rfind('.', pos - 1);
    if (std::regex_match(label.substr(prvPos + 1, pos - prvPos - 1), whileRegex))
      return label.substr(0, pos);
    pos = prvPos;
  }
  return "";
}

static std::string innerIfLabel(const std::string &label) {
  std::regex ifRegex(R"(if\d+)");
  size_t pos = label.size();

  while (pos != std::string::npos) {
    size_t prvPos = label.rfind('.', pos - 1);
    if (std::regex_match(label.substr(prvPos + 1, pos - prvPos - 1), ifRegex))
      return label.substr(0, pos);
    pos = prvPos;
  }
  return "";
}

static std::string address(const std::string &name) {
  return std::format("%{}.addr", name);
}

std::string LLVMIRGenerator::addressOf(std::shared_ptr<CactConstVar> var) {
  auto currentFunc = registry->getFunction(currentFunctionName);
  assert(currentFunc);
  const auto &params = currentFunc->parameters;
  if (std::find_if(params.begin(), params.end(), [&var](const auto &param) { return param.name == var->name; })
      != params.end()) {
    auto param =
        std::find_if(params.begin(), params.end(), [&var](const auto &param) { return param.name == var->name; });
    if (param->type.isArray())
      return "%" + var->name;
    else
      return address(var->name);
  }
  return registry->isGlobal(var) ? "@" + var->name : address(rename(var));
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
  temporaryID = 0;
  currentFunctionName = ctx->Identifier()->getText();

  // alloca for all the params
  // and store the params

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
  for (auto &param : ctx->function->parameters) {
    auto type = param.type;
    if (type.isArray())
      continue;
    std::string typeStr = basicTypeString(type.basic_type);
    irCodeStream << std::format("{} = alloca {}\n", address(param.name), typeStr);
    irCodeStream << std::format("store {} %{}, {}* {}\n", typeStr, param.name, typeStr, address(param.name));
  }
  allocateLocalVariables(funcBody);

  ifID.emplace_back(0);
  whileID.emplace_back(0);
  for (auto item : funcBody->blockItem())
    if (auto stmt = item->statement())
      irCodeStream << statementIRGen({}, stmt);
  if (ctx->function->return_type == CactBasicType::Void)
    irCodeStream << "ret void\n";
  ifID.pop_back();
  whileID.pop_back();
  irCodeStream << "}\n\n";
  currentFunctionName = "";
  return {};
}

std::string LLVMIRGenerator::returnStatementIRGen(const std::string &labelPrefix,
                                                  CactParser::ReturnStatementContext *ctx) {
  if (ctx->expression()) {
    const auto &[code, regName] = evaluationCodeGen(ctx->expr);
    return code + std::format("ret {} {}\n",
                              basicTypeString(ctx->expr->resultBasicType()),
                              regName);
  } else
    return std::format("ret void\n");
}

std::string LLVMIRGenerator::statementIRGen(const std::string &labelPrefix, CactParser::StatementContext *ctx) {
  if (auto ifCtx = ctx->ifStatement()) {
    auto reduced = reduceIfBranch(ifCtx);
    if (reduced)
      return reduced.value() ? statementIRGen(labelPrefix, reduced.value()) : "";
    const auto &ifLabel = std::format("{}.if{}", labelPrefix, ifID.back()++);
    return ifStatementIRGen(ifLabel, ifCtx);
  } else if (auto whileCtx = ctx->whileStatement()) {
    auto reduced = reduceWhileLoop(whileCtx);
    if (reduced)
      return reduced.value() ? statementIRGen(labelPrefix, reduced.value()) : "";
    const auto &whileLabel = std::format("{}.while{}", labelPrefix, whileID.back()++);
    return whileStatementIRGen(whileLabel, whileCtx->cond_expr, whileCtx->statement());
  } else if (auto returnCtx = ctx->returnStatement()) {
    return returnStatementIRGen(labelPrefix, returnCtx);
  } else if (auto exprCtx = ctx->expressionStatement()) {
    const auto &[code, regName] = evaluationCodeGen(exprCtx->expr);
    return code;
  } else if (auto assignCtx = ctx->assignStatement()) {
    const auto &[lhsFetchCode, lvaluePtrRegName] = fetchAddressCodeGen(assignCtx->lvalue);
    const auto &[rhsEvalCode, rhsRegName] = evaluationCodeGen(assignCtx->expr);
    return lhsFetchCode + rhsEvalCode
        + std::format("store {} {}, {}* {}\n",
                      basicTypeString(assignCtx->expr->resultBasicType()),
                      rhsRegName,
                      basicTypeString(assignCtx->lvalue->resultBasicType()),
                      lvaluePtrRegName);
  } else if (ctx->breakStatement()) {
    const auto &whileLabel = innerWhileLabel(labelPrefix);
    assert(!whileLabel.empty());
    return std::format("br label %{}\n", endingLabel(whileLabel));
  } else if (ctx->continueStatement()) {
    const auto &whileLabel = innerWhileLabel(labelPrefix);
    return std::format("br label %{}\n", condCheckLabel(whileLabel));
  } else if (ctx->block()) {
    ifID.emplace_back(0);
    whileID.emplace_back(0);
    std::string code;
    for (auto item : ctx->block()->blockItem())
      if (auto stmt = item->statement())
        code += statementIRGen(labelPrefix, stmt);
    ifID.pop_back();
    whileID.pop_back();
    return code;
  } else
    throw std::runtime_error("unsupported statement type");
  return {};
}

std::string LLVMIRGenerator::whileStatementIRGen(const std::string &labelPrefix,
                                                 const std::shared_ptr<CactExpr> &cond,
                                                 CactParser::StatementContext *loopBodyCtx) {
  assert(!cond->isConstant() || std::get<bool>(cond->getConstantValue()));
  // while (a && b) { ... }
  // -> br label %condCheck
  //    condCheck:
  //    eval(a)
  //    br i1 %a, label circuit(true), label end
  //    circuit(true):
  //    eval(b)
  //    br i1 %b, label %loopBody, label %end
  //    loopBody:
  //    ...
  //    br label %condCheck
  return std::format("br label %{}\n", condCheckLabel(labelPrefix))
      + condCheckLabel(labelPrefix) + ":\n"
      + shortCircuitConditionalJumpIRGen(condCheckLabel(labelPrefix), cond, loopBodyLabel(labelPrefix), endingLabel(labelPrefix))
      + loopBodyLabel(labelPrefix) + ":\n"
      + statementIRGenWithJump(labelPrefix, loopBodyCtx, condCheckLabel(labelPrefix))
      + endingLabel(labelPrefix) + ":\n";
}

std::string LLVMIRGenerator::statementIRGenWithJump(const std::string& labelPrefix, CactParser::StatementContext* ctx, const std::string& jumpLabel) {
  const auto& stmtCode = statementIRGen(labelPrefix, ctx);
  if (stmtCode.empty())
    return std::format("br label %{}\n", jumpLabel);
  else {
    // get the last line of code in stmtCode, which should be between the last two '\n'
    auto lastLine = stmtCode.substr(stmtCode.rfind('\n', stmtCode.size() - 2) + 1);
    if (lastLine.find("ret") != std::string::npos || lastLine.find("br") != std::string::npos)
      return stmtCode;
    else
      return stmtCode + std::format("br label %{}\n", jumpLabel);
  }
}

std::string LLVMIRGenerator::ifStatementIRGen(const std::string &labelPrefix, CactParser::IfStatementContext *ctx) {
  assert(!ctx->cond_expr->isConstant());
  if (ctx->statement().size() == 1) {
    const auto &thenLabel = thenBranchLabel(labelPrefix);
    return shortCircuitConditionalJumpIRGen(labelPrefix, ctx->cond_expr, thenLabel, endingLabel(labelPrefix))
        + thenLabel + ":\n"
        + statementIRGenWithJump(labelPrefix, ctx->statement(0), endingLabel(labelPrefix))
        + endingLabel(labelPrefix) + ":\n";
  } else if (ctx->statement().size() == 2) {
    const auto &thenLabel = thenBranchLabel(labelPrefix);
    const auto &elseLabel = elseBranchLabel(labelPrefix);
    return shortCircuitConditionalJumpIRGen(labelPrefix, ctx->cond_expr, thenLabel, elseLabel)
        + thenLabel + ":\n"
        + statementIRGenWithJump(labelPrefix, ctx->statement(0), endingLabel(labelPrefix))
        + elseLabel + ":\n"
        + statementIRGenWithJump(labelPrefix, ctx->statement(1), endingLabel(labelPrefix))
        + endingLabel(labelPrefix) + ":\n";
  }
  throw std::runtime_error("if statement has more than 2 branches");
}

std::string LLVMIRGenerator::shortCircuitConditionalJumpIRGen(const std::string &labelPrefix,
                                                              const std::shared_ptr<CactExpr> &cond,
                                                              const std::string &thenBranchLabel,
                                                              const std::string &elseBranchLabel) {
  assert(cond->resultBasicType() == CactBasicType::Bool);
  if (cond->isConstant()) {
    if (std::get<bool>(cond->getConstantValue()))
      return std::format("br label %{}\n", thenBranchLabel);
    else
      return std::format("br label %{}\n", elseBranchLabel);
  }
  if (!cond->isLogicalOp()) {
    const auto &[condEvalCode, condRegName] = evaluationCodeGen(cond);
    return condEvalCode + std::format("br i1 {}, label %{}, label %{}\n",
                                      condRegName, thenBranchLabel, elseBranchLabel);
  }
  if (auto logicalAnd = dynamic_pointer_cast<LogicalAndOperator>(cond->binary_operator)) {
    const auto &thenLabel = shortCircuitThenLabel(labelPrefix);

    if (cond->left_expr->isConstant() && !std::get<bool>(cond->left_expr->getConstantValue()))
      return std::format("br label %{}\n", elseBranchLabel);
    else if (cond->left_expr->isConstant() && std::get<bool>(cond->left_expr->getConstantValue()))
      return shortCircuitConditionalJumpIRGen(labelPrefix, cond->right_expr, thenBranchLabel, elseBranchLabel);
    return shortCircuitConditionalJumpIRGen(labelPrefix, cond->left_expr, thenLabel, elseBranchLabel)
        + thenLabel + ":\n"
        + shortCircuitConditionalJumpIRGen(thenLabel, cond->right_expr, thenBranchLabel, elseBranchLabel);
  } else if (auto logicalOr = dynamic_pointer_cast<LogicalOrOperator>(cond->binary_operator)) {
    const auto &elseLabel = shortCircuitElseLabel(labelPrefix);

    if (cond->left_expr->isConstant() && std::get<bool>(cond->left_expr->getConstantValue()))
      return std::format("br label %{}\n", thenBranchLabel);
    else if (cond->left_expr->isConstant() && !std::get<bool>(cond->left_expr->getConstantValue()))
      return shortCircuitConditionalJumpIRGen(labelPrefix, cond->right_expr, thenBranchLabel, elseBranchLabel);
    return shortCircuitConditionalJumpIRGen(labelPrefix, cond->left_expr, thenBranchLabel, elseLabel)
        + elseLabel + ":\n"
        + shortCircuitConditionalJumpIRGen(elseLabel, cond->right_expr, thenBranchLabel, elseBranchLabel);
  } else
    throw std::runtime_error("unsupported logical operator");
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
  else if (type == CactBasicType::Float || type == CactBasicType::Double)
    return floatOpMap.at(typeid(op));
  throw std::runtime_error("unsupported binary operator");
}

static std::string binaryToLLVMPredicate(const BinaryOperator &op, CactBasicType type) {
  assert(type != CactBasicType::Void && type != CactBasicType::Unknown);
  static std::map<std::type_index, std::string> intPredMap = {
      {typeid(LessOperator), "slt"},
      {typeid(LessEqualOperator), "sle"},
      {typeid(GreaterOperator), "sgt"},
      {typeid(GreaterEqualOperator), "sge"},
      {typeid(EqualOperator), "eq"},
      {typeid(NotEqualOperator), "ne"},
  };
  static std::map<std::type_index, std::string> floatPredMap = {
      {typeid(LessOperator), "olt"},
      {typeid(LessEqualOperator), "ole"},
      {typeid(GreaterOperator), "ogt"},
      {typeid(GreaterEqualOperator), "oge"},
      {typeid(EqualOperator), "oeq"},
      {typeid(NotEqualOperator), "one"},
  };
  if (type == CactBasicType::Int32)
    return intPredMap.at(typeid(op));
  else
    return floatPredMap.at(typeid(op));
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::unaryOpCodegen(const std::shared_ptr<CactExpr> &unary) {
  auto unaryOp = unary->unary_operator;
  auto expr = unary->expr;
  if (dynamic_pointer_cast<NegOperator>(unaryOp)) {
    return evaluationCodeGen(make_shared<CactBinaryExpr>(std::make_shared<SubOperator>(),
                                                         std::make_shared<CactExpr>(0),
                                                         expr));
  } else if (dynamic_pointer_cast<PlusOperator>(unaryOp) || dynamic_pointer_cast<UnaryNopOperator>(unaryOp)) {
    return evaluationCodeGen(expr);
  } else if (dynamic_pointer_cast<LogicalNotOperator>(unaryOp)) {
    const auto &[code, regName] = evaluationCodeGen(expr);
    const auto &resultReg = assignReg();
    return {
        .code = code
            + std::format("{} = xor i1 {}, 1\n",
                          resultReg, regName),
        .result = resultReg
    };
  }
  throw std::runtime_error("unsupported unary operator");
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::evaluationCodeGen(const std::shared_ptr<CactExpr> &expr) {
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
    if (expr->isPredicate())
      return predicateBinaryOpCodeGen(expr);
    else if (expr->isLogicalOp())
      return logicalOpCodeGen(expr);
    else
      return arithmeticBinaryOpCodeGen(expr);
  } else if (expr->isVariable())
    return variableEvaluationCodeGen(expr);
  else if (expr->isFunctionCall())
    return functionCallCodegen(expr);
  else if (expr->isUnaryExpression())
    return unaryOpCodegen(expr);
  throw std::runtime_error("unsupported expression type");
}

void LLVMIRGenerator::emitAlloca(const std::string &name, const CactType &type, size_t arraySize = 0) {
  if (arraySize > 0)
    irCodeStream << std::format("{} = alloca {}, {}\n", address(name),
                                basicTypeString(type.basic_type), arraySize);
  else
    irCodeStream << std::format("{} = alloca {}\n", address(name), basicTypeString(type.basic_type));
}

void LLVMIRGenerator::emitStore(const std::string &dest, const CactType &type, const std::string &value) {
  irCodeStream << std::format("store {} {}, {}* {}\n",
                              basicTypeString(type.basic_type), value,
                              basicTypeString(type.basic_type), dest);
}

void LLVMIRGenerator::initializeArray(const std::string &name, const CactType &type,
                                      const std::vector<ConstEvalResult> &initValues) {
  for (size_t i = 0; i < initValues.size(); ++i) {
    const auto &ptrReg = assignReg();
    irCodeStream << std::format("{} = getelementptr {}, {}* {}, i32 {}\n",
                                ptrReg, basicTypeString(type.basic_type),
                                basicTypeString(type.basic_type), address(name), i);

    const auto &initValStr = std::visit([](auto &&arg) { return std::to_string(arg); }, initValues[i]);
    emitStore(ptrReg, type, initValStr);
  }
}

void LLVMIRGenerator::allocateVariable(const std::shared_ptr<CactConstVar> &var, const std::string &newName) {
  if (var->type.isArray()) {
    assert(var->type.size() % sizeOf(var->type.basic_type) == 0);
    const size_t arraySize = var->type.size() / sizeOf(var->type.basic_type);
    emitAlloca(newName, var->type, arraySize);

    if (var->isInitialized())
      initializeArray(newName, var->type, var->init_values);
  } else {
    emitAlloca(newName, var->type);
    if (var->isInitialized()) {
      const auto &initValStr = std::visit([](auto &&arg) { return std::to_string(arg); }, var->init_values.at(0));
      emitStore(address(newName), var->type, initValStr);
    }
  }
}

void LLVMIRGenerator::emitGlobalVariable(const std::shared_ptr<CactConstVar> &var, bool isConstant) {
  const std::string globalKind = isConstant ? "constant" : "global";
  if (!var->type.isArray()) {
    const std::string initValStr = var->isInitialized()
                                   ? std::visit([](auto &&arg) { return std::to_string(arg); }, var->init_values.at(0))
                                   : "";
    irCodeStream << std::format("@{} = {} {} {}\n", var->name, globalKind,
                                basicTypeString(var->type.basic_type), initValStr);
  } else {
    irCodeStream << std::format("@{} = {} [{} x {}] [", var->name, globalKind,
                                var->type.size() / sizeOf(var->type.basic_type),
                                basicTypeString(var->type.basic_type));
    for (size_t i = 0; i < var->init_values.size(); ++i) {
      irCodeStream << std::visit([](auto &&arg) { return std::to_string(arg); }, var->init_values[i]);
      if (i != var->init_values.size() - 1) {
        irCodeStream << ", ";
      }
    }
    irCodeStream << "]\n";
  }
}

std::any LLVMIRGenerator::visitDeclaration(CactParser::DeclarationContext *ctx) {
  if (auto varDecl = ctx->variableDeclaration()) {
    for (auto varDef : varDecl->variableDefinition()) {
      const auto &var = varDef->variable;
      assert(registry->isGlobal(var));
      emitGlobalVariable(var, false);
    }
  } else if (auto constDecl = ctx->constantDeclaration()) {
    for (auto constDef : constDecl->constantDefinition()) {
      const auto &constant = constDef->constant;
      assert(registry->isGlobal(constant));
      emitGlobalVariable(constant, true);
    }
  } else {
    assert(false);
  }
  return {};
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

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::fetchAddressCodeGen(const std::shared_ptr<CactExpr> &expr) {
  assert(expr->isVariable());
  const auto &var = expr->variable;
  if (!var->indexing_times) {
    return {
        .code = "",
        .result = addressOf(var->symbol)
    };
  }
  const auto &indexEval = evaluationCodeGen(var->flattenedIndex);
  const auto &indexReg = indexEval.result;
  const auto &ptrReg = assignReg();
  const auto &gepInst = std::format("{} = getelementptr {}, {}* {}, i32 {}\n",
                                    ptrReg,
                                    basicTypeString(var->symbol->type.basic_type),
                                    basicTypeString(var->symbol->type.basic_type),
                                    addressOf(var->symbol),
                                    indexReg);
  return {
      .code = indexEval.code + gepInst,
      .result = ptrReg
  };
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::variableEvaluationCodeGen(const std::shared_ptr<CactExpr> &expr) {
  const auto &var = expr->variable;
  if (!var->indexing_times) {
    const auto &regName = assignReg();
    return {
        .code = std::format("{} = load {}, {}* {}\n",
                            regName,
                            basicTypeString(var->symbol->type.basic_type),
                            basicTypeString(var->symbol->type.basic_type),
                            addressOf(var->symbol)),
        .result = regName
    };
  }
  const auto &[addrCode, addrReg] = fetchAddressCodeGen(expr);
  const auto &regName = assignReg();
  return {
      .code = addrCode + std::format("{} = load {}, {}* {}\n",
                                     regName,
                                     basicTypeString(var->symbol->type.basic_type),
                                     basicTypeString(var->symbol->type.basic_type),
                                     addrReg),
      .result = regName
  };
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::arithmeticBinaryOpCodeGen(const std::shared_ptr<CactExpr> &expr) {
  auto binaryOp = expr->binary_operator;
  auto left = expr->left_expr;
  auto right = expr->right_expr;
  const auto &[leftEvalCode, leftRegName] = evaluationCodeGen(left);
  const auto &[rightEvalCode, rightRegName] = evaluationCodeGen(right);
  const auto &resultReg = assignReg();
  return {
      .code = leftEvalCode + rightEvalCode
          + std::format("{} = {} {} {}, {}\n",
                        resultReg,
                        binaryToLLVMOp(*binaryOp, expr->resultBasicType()),
                        basicTypeString(expr->resultBasicType()),
                        leftRegName,
                        rightRegName),
      .result = resultReg
  };
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::predicateBinaryOpCodeGen(const std::shared_ptr<CactExpr> &expr) {
  auto binaryOp = expr->binary_operator;
  assert(binaryOp->isPredicate());
  auto left = expr->left_expr;
  auto right = expr->right_expr;
  const auto &[leftEvalCode, leftRegName] = evaluationCodeGen(left);
  const auto &[rightEvalCode, rightRegName] = evaluationCodeGen(right);
  const auto &resultReg = assignReg();
  const auto &cmpInst = expr->left_expr->resultBasicType() == CactBasicType::Int32
                        ? std::format("icmp {} i32 {}, {}\n",
                                      binaryToLLVMPredicate(*binaryOp, expr->resultBasicType()),
                                      leftRegName,
                                      rightRegName)
                        : std::format("fcmp {} {} {}, {}\n",
                                      basicTypeString(expr->resultBasicType()),
                                      binaryToLLVMPredicate(*binaryOp, expr->resultBasicType()),
                                      leftRegName, rightRegName);
  return {
      .code = leftEvalCode + rightEvalCode + cmpInst,
      .result = resultReg
  };
}

LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::functionCallCodegen(const std::shared_ptr<CactExpr> &expr) {
  const auto &func = expr->function;
  const auto &args = expr->args;
  std::string argList{};
  std::string argEvalCode{};
  for (size_t i = 0; i < args.size(); ++i) {
    const auto &arg = args[i];
    const auto &argCodegenResult = evaluationCodeGen(arg);
    argEvalCode += argCodegenResult.code;
    const auto &argReg = argCodegenResult.result;
    argList += std::format("{} {}", basicTypeString(arg->resultBasicType()), argReg);
    if (i != args.size() - 1)
      argList += ", ";
  }
  const auto &resultReg = assignReg();
  return {
      .code = argEvalCode + std::format("{} = call {} @{}({})\n",
                                        resultReg,
                                        basicTypeString(func->return_type),
                                        func->name,
                                        argList),
      .result = resultReg
  };
}

void LLVMIRGenerator::declareExternalFunctions() {
  irCodeStream << "declare void @print_int(i32)\n";
  irCodeStream << "declare void @print_float(float)\n";
  irCodeStream << "declare void @print_double(double)\n";
  irCodeStream << "declare void @print_bool(i1)\n";
  irCodeStream << "declare i32 @get_int()\n";
  irCodeStream << "declare float @get_float()\n";
  irCodeStream << "declare double @get_double()\n";
}
LLVMIRGenerator::EvaluationCodegenResult LLVMIRGenerator::logicalOpCodeGen(const std::shared_ptr<CactExpr> &cond) {
  assert(cond->isLogicalOp());
  const auto &resultReg = assignReg();
  const auto &evalLabel = std::format("{}.eval", resultReg.substr(1));
  const auto &trueLabel = std::format("{}.true", resultReg.substr(1));
  const auto &falseLabel = std::format("{}.false", resultReg.substr(1));
  const auto &endLabel = std::format("{}.eval.end", resultReg.substr(1));
  // short-circuit evaluation
  // a && b
  // ->
  // eval(a)
  // br i1 %a, label circuit(true, x.eval), label x.false
  // circuit(true, x.eval):
  // eval(b)
  // br i1 %b, label x.true, label x.false
  // x.true:
  // br x.eval.end
  // x.false:
  // br x.eval.end
  // x.eval.end:
  // newReg = phi i1 [x.true, 1], [x.false, 0]
  return {
      .code = shortCircuitConditionalJumpIRGen(evalLabel, cond, trueLabel, falseLabel)
          + trueLabel + ":\n"
          + std::format("br label %{}\n", endLabel)
          + falseLabel + ":\n"
          + std::format("br label %{}\n", endLabel)
          + endLabel + ":\n"
          + std::format("{} = phi i1 [1, {}], [0, {}]\n",
                        resultReg, trueLabel, falseLabel),
      .result = resultReg
  };
}

}