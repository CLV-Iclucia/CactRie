//
// Created by creeper on 9/29/24.
//
#include <antlr-runtime/ANTLRInputStream.h>
#include <antlr-runtime/CommonTokenStream.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/autogen/LLVMLexer.h>
#include <chiisai-llvm/autogen/LLVMParser.h>
#include <chiisai-llvm/global-variable.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/module-builder.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/pointer-type.h>
#include <minilog/logger.h>
#include <mystl/castings.h>
#include <ranges>

namespace llvm {

std::any ModuleBuilder::visitModule(LLVMParser::ModuleContext *ctx) {
  for (auto child : ctx->children) {
    if (auto globalDecl =
            dynamic_cast<LLVMParser::GlobalDeclarationContext *>(child))
      visitGlobalDeclaration(globalDecl);
    if (auto funcDecl =
            dynamic_cast<LLVMParser::FunctionDeclarationContext *>(child))
      visitFunctionDeclaration(funcDecl);
    if (auto funcDef =
            dynamic_cast<LLVMParser::FunctionDefinitionContext *>(child))
      visitFunctionDefinition(funcDef);
  }
  return {};
}
std::any ModuleBuilder::visitGlobalDeclaration(
    LLVMParser::GlobalDeclarationContext *ctx) {
  const auto &globalName = ctx->globalIdentifier()->getText();
  if (module->hasGlobalVar(globalName))
    throw std::runtime_error(
        "Global variable name already exists in the module");
  bool isConstant = ctx->ConstantStr() != nullptr;
  visitInitializer(ctx->initializer());
  auto initializer = ctx->initializer()->constant;
  if (ctx->initializer()->constant)
    module->addGlobalVariable(std::make_unique<GlobalVariable>(
        GlobalVariableDetails{.name = globalName,
                              .initializer = initializer,
                              .isConstant = isConstant}));
  else
    module->addGlobalVariable(std::make_unique<GlobalVariable>(
        globalName, ctx->initializer()->typeRef));
  return {};
}

std::any ModuleBuilder::visitBasicType(LLVMParser::BasicTypeContext *ctx) {
  auto typeStr = ctx->getText();
  ctx->typeRef = llvmContext->stobt(typeStr);
  return {};
}

std::any ModuleBuilder::visitArrayType(LLVMParser::ArrayTypeContext *ctx) {
  auto elementTypeNode = ctx->type();
  visitType(ctx->type());
  size_t size = std::stoul(ctx->IntegerLiteral()->getText());
  auto elementType = elementTypeNode->typeRef;
  if (elementType == Type::voidType(*llvmContext))
    throw std::runtime_error(
        "Array type cannot have void type as its element type");
  ctx->typeRef = llvmContext->arrayType(elementType, size);
  return {};
}

std::any ModuleBuilder::visitPointerType(LLVMParser::PointerTypeContext *ctx) {
  auto elementTypeNode = ctx->basicType();
  visitBasicType(elementTypeNode);
  auto elementType = elementTypeNode->typeRef;
  if (elementType == Type::voidType(*llvmContext))
    throw std::runtime_error(
        "Pointer type cannot have void type as its element type");
  ctx->typeRef = llvmContext->pointerType(elementType);
  return {};
}

Ref<Value> ModuleBuilder::resolveImmediateValueUsage(
    CRef<Type> type, LLVMParser::ImmediatelyUsableValueContext *ctx) {
  visitImmediatelyUsableValue(ctx);
  if (ctx->isConstant) {
    const auto &str = ctx->literal()->getText();
    return llvmContext->constant(type, str);
  }
  auto var = ctx->localIdentifier();
  if (currentBasicBlock->hasIdentifier(variableName(var)))
    return makeRef(currentBasicBlock->identifier(variableName(var)));
  if (!currentFunction->hasIdentifier(variableName(var)))
    throw std::runtime_error("Cannot find the identifier" + variableName(var) +
                             " in function " + currentFunction->name());
  return makeRef(currentFunction->identifier(variableName(var)));
}

Ref<Value>
ModuleBuilder::resolveVariableUsage(LLVMParser::VariableContext *ctx) {
  visitVariable(ctx);
  if (ctx->isGlobal) {
    if (!module->hasGlobalVar(variableName(ctx)))
      throw std::runtime_error("Cannot find the global variable");
    return module->globalVariable(variableName(ctx));
  }
  if (currentBasicBlock->hasIdentifier(variableName(ctx)))
    return makeRef(currentBasicBlock->identifier(variableName(ctx)));
  if (currentFunction->hasIdentifier(variableName(ctx)))
    return makeRef(currentFunction->identifier(variableName(ctx)));
  throw std::runtime_error("Cannot find the identifier " + variableName(ctx) +
                           " in function " + currentFunction->name());
}

static std::vector<CRef<Type>>
formContainedTypes(CRef<Type> returnType, std::vector<CRef<Type>> &&argTypes) {
  std::vector<CRef<Type>> containedTypes;
  containedTypes.reserve(1 + argTypes.size());
  containedTypes.push_back(returnType);
  containedTypes.insert(containedTypes.end(), argTypes.begin(), argTypes.end());
  return containedTypes;
}

std::any ModuleBuilder::visitFunctionDeclaration(
    LLVMParser::FunctionDeclarationContext *ctx) {
  auto returnTypeCtx = ctx->type();
  auto funcName = ctx->globalIdentifier()->NamedIdentifier()->getText();

  if (module->hasFunction(funcName))
    throw std::runtime_error("Function name already exists in the module");
  if (module->hasGlobalVar(funcName))
    throw std::runtime_error(
        "Global variable name already exists in the module");

  visitType(returnTypeCtx);
  auto returnType = returnTypeCtx->typeRef;
  auto args = ctx->functionArguments();
  visitFunctionArguments(args);
  // append argTypes and returnTypes together to form containedTypes
  std::vector<CRef<Type>> containedTypes =
      formContainedTypes(returnType, std::move(args->argTypes));
  auto functionType = llvmContext->functionType(containedTypes);
  module->addFunction(std::make_unique<Function>(
      FunctionInfo{.name = funcName,
                   .functionType = functionType,
                   .argNames = std::move(args->argNames),
                   .module = *module}));
  return {};
}

static void moveAllocasInEntryBlock(BasicBlock &entryBlock) {
  CRef<Instruction> currentInsertionPoint{};
  std::vector<CRef<Instruction>> allocas{};
  for (auto inst : entryBlock.instructions)
    if (isa<AllocaInst>(inst))
      allocas.emplace_back(inst);
  currentInsertionPoint = makeCRef(entryBlock.instructions.front());
  for (auto inst : allocas) {
    entryBlock.moveInstAfter(inst, currentInsertionPoint);
    currentInsertionPoint = inst;
  }
}

std::any ModuleBuilder::visitFunctionDefinition(
    LLVMParser::FunctionDefinitionContext *ctx) {
  auto returnTypeCtx = ctx->type();
  auto funcName = ctx->globalIdentifier()->NamedIdentifier()->getText();

  if (module->hasFunction(funcName))
    throw std::runtime_error("Function name already exists in the module");
  if (module->hasGlobalVar(funcName))
    throw std::runtime_error(
        "Global variable name already exists in the module");

  visitType(returnTypeCtx);
  auto returnType = returnTypeCtx->typeRef;
  auto args = ctx->functionArguments();
  visitFunctionArguments(args);

  for (const auto &argName : args->argNames)
    if (argName.empty())
      throw std::runtime_error(
          "Function definition must have argument names specified");
  // append argTypes and returnTypes together to form containedTypes
  std::vector<CRef<Type>> containedTypes =
      formContainedTypes(returnType, std::move(args->argTypes));
  auto functionType = llvmContext->functionType(containedTypes);
  const auto &basicBlocks = ctx->basicBlock();
  module->addFunction(std::make_unique<Function>(
      FunctionInfo{.name = funcName,
                   .functionType = functionType,
                   .argNames = std::move(args->argNames),
                   .module = *module,
                   .isImplemented = true}));
  auto newFunc = module->function(funcName);
  currentFunction = newFunc;
  for (auto bb : basicBlocks) {
    auto blockName = bb->NamedIdentifier()->getText();
    currentFunction->addBasicBlock(
        std::make_unique<BasicBlock>(blockName, llvmContext->labelType(), newFunc));
  }
  for (auto bb : basicBlocks)
    visitBasicBlock(bb);
  moveAllocasInEntryBlock(newFunc->basicBlock("entry"));
  return {};
}
std::any ModuleBuilder::visitBasicBlock(LLVMParser::BasicBlockContext *ctx) {
  currentBasicBlock =
      makeRef(currentFunction->basicBlock(ctx->NamedIdentifier()->getText()));
  for (const auto &instructions = ctx->instruction(); auto inst : instructions)
    visitInstruction(inst);
  return {};
}

std::any ModuleBuilder::visitType(LLVMParser::TypeContext *ctx) {
  auto basicTy = ctx->basicType();
  auto arrayTy = ctx->arrayType();
  auto pointerTy = ctx->pointerType();
  if (basicTy) {
    assert(!arrayTy && !pointerTy);
    visitBasicType(basicTy);
    ctx->typeRef = basicTy->typeRef;
  } else if (arrayTy) {
    assert(!pointerTy);
    visitArrayType(arrayTy);
    ctx->typeRef = arrayTy->typeRef;
  } else if (pointerTy) {
    visitPointerType(pointerTy);
    ctx->typeRef = pointerTy->typeRef;
  } else
    throw std::runtime_error("the type is neither basic, array nor pointer "
                             "type, which is impossible");
  return {};
}

std::any ModuleBuilder::visitArithmeticInstruction(
    LLVMParser::ArithmeticInstructionContext *ctx) {
  auto lhs = ctx->localIdentifier();
  visitType(ctx->type());
  auto lhsName = variableName(lhs);
  if (currentFunction->hasArg(lhsName))
    throw std::runtime_error(
        "Variable name already exists in the function arguments");
  const auto &operands = ctx->immediatelyUsableValue();

  if (operands.size() != 2)
    throw std::runtime_error(
        "Arithmetic instruction must have exactly two operands");

  auto operandLeftRef =
      resolveImmediateValueUsage(ctx->type()->typeRef, operands[0]);
  auto operandRightRef =
      resolveImmediateValueUsage(ctx->type()->typeRef, operands[1]);

  if (!Instruction::checkBinaryInstType(operandLeftRef, operandRightRef))
    throw std::runtime_error("Binary instruction operands must have the same "
                             "type and is computable");

  auto opcode = stoinst(ctx->binaryOperation()->getText());
  auto binaryInst =
      IRBuilder(*currentBasicBlock)
          .createBinaryInst(opcode, {
                                        .name = lhsName,
                                        .type = operandLeftRef->type(),
                                        .lhs = operandLeftRef,
                                        .rhs = operandRightRef,
                                    });
  logger->info("Created binary instruction in block {}: {}",
               currentBasicBlock->name(), binaryInst->toString());
  return {};
}

std::any ModuleBuilder::visitComparisonInstruction(
    LLVMParser::ComparisonInstructionContext *ctx) {
  auto cmpOp = ctx->comparisonOperation()->getText();
  auto predicateStr = ctx->comparisonPredicate()->getText();
  visitType(ctx->type());
  auto lhsRef = resolveImmediateValueUsage(ctx->type()->typeRef,
                                           ctx->immediatelyUsableValue(0));
  auto rhsRef = resolveImmediateValueUsage(ctx->type()->typeRef,
                                           ctx->immediatelyUsableValue(1));
  Instruction::OtherOps cmpOpCode;
  if (cmpOp == "icmp")
    cmpOpCode = Instruction::ICmp;
  else if (cmpOp == "fcmp")
    cmpOpCode = Instruction::FCmp;
  else
    throw std::runtime_error("Invalid comparison operation: " + cmpOp);
  auto cmpInst =
      IRBuilder(*currentBasicBlock)
          .createCmpInst(cmpOpCode, {.ctx = *llvmContext,
                                     .name = ctx->localIdentifier()->getText(),
                                     .lhs = lhsRef,
                                     .rhs = rhsRef,
                                     .predicate = stopdct(predicateStr)});
  logger->info("Created comparison instruction in block {}: {}",
               currentBasicBlock->name(), cmpInst->toString());
  return {};
}

std::any
ModuleBuilder::visitLoadInstruction(LLVMParser::LoadInstructionContext *ctx) {
  auto dest = ctx->localIdentifier();
  auto destName = variableName(dest);
  visitType(ctx->type(0));
  if (currentFunction->hasIdentifier(destName))
    throw std::runtime_error(
        "Variable name already exists in the function locals");
  if (currentFunction->hasArg(destName))
    throw std::runtime_error(
        "Variable name already exists in the function arguments");

  auto src = resolveVariableUsage(ctx->variable());
  auto loadInst = IRBuilder(*currentBasicBlock)
                      .createLoadInst({.name = destName,
                                       .type = ctx->type(0)->typeRef,
                                       .pointer = src});
  logger->info("Created load instruction in block {}: {}",
               currentBasicBlock->name(), loadInst->toString());
  return {};
}

static std::string genStoreInstName() {
  static int id{};
  return std::format("__store_{}", id++);
}

std::any
ModuleBuilder::visitStoreInstruction(LLVMParser::StoreInstructionContext *ctx) {
  auto dest = ctx->variable();
  auto src = ctx->immediatelyUsableValue();
  auto destRef = resolveVariableUsage(dest);
  visitType(ctx->type(0));
  visitType(ctx->type(1));
  assert(llvmContext->pointerType(ctx->type(1)->typeRef) == destRef->type() ||
         (isa<GlobalVariable>(destRef) &&
          destRef->type() == ctx->type(1)->typeRef));
  auto srcRef = resolveImmediateValueUsage(ctx->type(0)->typeRef, src);
  auto storeInst = IRBuilder(*currentBasicBlock)
                       .createStoreInst({.name = genStoreInstName(),
                                         .type = destRef->type(),
                                         .pointer = destRef,
                                         .value = srcRef});
  logger->info("Created store instruction in block {}: {}",
               currentBasicBlock->name(), storeInst->toString());
  return {};
}

std::any ModuleBuilder::visitAllocaInstruction(
    LLVMParser::AllocaInstructionContext *ctx) {
  auto varType = ctx->type();
  visitType(varType);
  auto varName = variableName(ctx->localIdentifier());
  int hasAlign = ctx->Align() != nullptr;
  // ctx should have hasAlign integer literals, if there is more, it should have
  // size
  int hasSize = ctx->IntegerLiteral().size() > hasAlign;
  if (hasSize)
    assert(!ctx->IntegerLiteral().empty());
  size_t size = hasSize ? std::stoul(ctx->IntegerLiteral(0)->getText()) : 1;
  // 0 means no alignment required
  size_t alignment =
      hasAlign ? std::stoul(ctx->IntegerLiteral().back()->getText()) : 0;
  if (currentFunction->hasArg(varName)) {
    // ERROR
    throw std::runtime_error(
        "Variable name already exists in the function arguments");
  }
  auto allocaInst =
      IRBuilder(*currentBasicBlock)
          .createAllocaInst({.name = varName,
                             .type = llvmContext->pointerType(varType->typeRef),
                             .size = size,
                             .alignment = alignment});
  logger->info("Created alloca instruction in block {}: {}",
               currentBasicBlock->name(), allocaInst->toString());
  return {};
}
std::any ModuleBuilder::visitImmediatelyUsableValue(
    LLVMParser::ImmediatelyUsableValueContext *ctx) {
  auto var = ctx->localIdentifier();
  auto literal = ctx->literal();
  if (var) {
    ctx->isConstant = false;
  } else if (literal) {
    ctx->isConstant = true;
  } else
    throw std::runtime_error("Value must be either a variable or a number");
  return {};
}

std::any
ModuleBuilder::visitGepInstruction(LLVMParser::GepInstructionContext *ctx) {
  auto gepVal = ctx->localIdentifier();
  auto gepValName = variableName(gepVal);
  if (currentFunction->hasIdentifier(gepValName))
    throw std::runtime_error(
        "Variable name already exists in the function identifiers");
  if (currentFunction->hasArg(gepValName))
    throw std::runtime_error(
        "Variable name already exists in the function arguments");
  auto var = resolveVariableUsage(ctx->variable());
  auto indices = ctx->immediatelyUsableValue();
  Ref<Value> indexRef{};
  if (ctx->immediatelyUsableValue()) {
    assert(ctx->scalarType());
    indexRef = resolveImmediateValueUsage(
        llvmContext->stobt(ctx->scalarType()->getText()),
        ctx->immediatelyUsableValue());
  }
  CRef<PointerType> pointerType{};
  if (var->type()->isPointer())
    pointerType = dyn_cast_ref<PointerType>(var->type());
  else if (var->type()->isArray())
    pointerType = llvmContext->castFromArrayType(cast<ArrayType>(var->type()));
  else
    throw std::runtime_error("GEP instruction must have a pointer or an array "
                             "type as the first operand");
  auto gepInst = IRBuilder(*currentBasicBlock)
                     .createGepInst({.name = gepValName,
                                     .type = pointerType,
                                     .pointer = makeRef(*var),
                                     .index = indexRef});
  logger->info("Created GEP instruction in block {}: {}",
               currentBasicBlock->name(), gepInst->toString());
  return {};
}

BuildResult ModuleBuilder::build(LLVMParser::ModuleContext *ctx) {
  llvmContext = std::make_unique<LLVMContext>();
  module = std::make_unique<Module>();
  visitModule(ctx);
  return {std::move(module), std::move(llvmContext)};
}

std::any ModuleBuilder::visitInitializer(LLVMParser::InitializerContext *ctx) {
  if (ctx->IntegerLiteral()) {
    visitScalarType(ctx->scalarType());
    auto type = ctx->scalarType()->typeRef;
    ctx->typeRef = type;
    if (!type->isInteger())
      throw std::runtime_error("Invalid type for integer literal");
    ctx->constant =
        llvmContext->constant(type, ctx->IntegerLiteral()->getText());
    return {};
  }
  if (ctx->HexLiteral()) {
    visitScalarType(ctx->scalarType());
    auto type = ctx->scalarType()->typeRef;
    ctx->typeRef = type;
    if (!type->isFloatingPoint())
      throw std::runtime_error("Invalid type for floating literal");
    ctx->constant = llvmContext->constant(type, ctx->HexLiteral()->getText());
    return {};
  }
  if (ctx->constantArray()) {
    auto constArrayCtx = ctx->constantArray();
    visitConstantArray(constArrayCtx);
    ctx->typeRef = constArrayCtx->arrayType()->typeRef;
    ctx->constant = constArrayCtx->constArray;
    return {};
  }
  throw std::runtime_error("Initializer must be either an integer literal, a "
                           "float literal or a constant array");
}

std::any
ModuleBuilder::visitConstantArray(LLVMParser::ConstantArrayContext *ctx) {
  auto arrayTypeCtx = ctx->arrayType();
  visitArrayType(arrayTypeCtx);
  auto arrayType = arrayTypeCtx->typeRef;
  for (auto init : ctx->initializer()) {
    visitInitializer(init);
    if (init->constant->type() != arrayType->elementType())
      throw std::runtime_error(
          "Initializer type does not match the array element type");
  }
  return {};
}

std::any ModuleBuilder::visitScalarType(LLVMParser::ScalarTypeContext *ctx) {
  ctx->typeRef = llvmContext->stobt(ctx->getText());
  return {};
}

std::any ModuleBuilder::visitReturnInstruction(
    LLVMParser::ReturnInstructionContext *ctx) {
  CRef<RetInst> retInst{};
  if (ctx->immediatelyUsableValue()) {
    auto type = ctx->type();
    visitType(type);
    auto value = resolveImmediateValueUsage(type->typeRef,
                                            ctx->immediatelyUsableValue());
    if (value->type() != type->typeRef)
      throw std::runtime_error(
          "Return value type does not match the specified type");
    if (value->type() != currentFunction->returnType())
      throw std::runtime_error(
          "Return value type does not match the function return type");
    retInst = IRBuilder(*currentBasicBlock).createRetInst(value);
  } else {
    if (currentFunction->returnType() != Type::voidType(*llvmContext))
      throw std::runtime_error("Return value type does not match the function "
                               "return type: void expected");
    retInst = IRBuilder(*currentBasicBlock).createRetInst({});
  }
  logger->info("Return instruction created in block {}: {}",
               currentBasicBlock->name(), retInst->toString());
  return {};
}

std::any ModuleBuilder::visitBranchInstruction(
    LLVMParser::BranchInstructionContext *ctx) {
  if (ctx->I1()) {
    auto cond = resolveImmediateValueUsage(Type::boolType(*llvmContext),
                                           ctx->immediatelyUsableValue());
    if (cond->type() != Type::boolType(*llvmContext))
      throw std::runtime_error("Branch condition must be of boolean type");
    auto &thenBranch = currentFunction->basicBlock(
        ctx->localIdentifier(0)->getText().substr(1));
    auto &elseBranch = currentFunction->basicBlock(
        ctx->localIdentifier(1)->getText().substr(1));
    auto brInst = IRBuilder(*currentBasicBlock)
                      .createBrInst(BrInstDetails{
                          .cond = cond,
                          .thenBranch = makeRef(thenBranch),
                          .elseBranch = makeRef(elseBranch),
                      });
    logger->info("Branch instruction created : {}", brInst->toString());
  } else {
    IRBuilder(*currentBasicBlock)
        .createBrInst(currentFunction->basicBlock(
            ctx->localIdentifier(0)->getText().substr(1)));
  }
  return {};
}

std::any
ModuleBuilder::visitCallInstruction(LLVMParser::CallInstructionContext *ctx) {
  static int id{};
  const auto &funcName = ctx->globalIdentifier()->getText().substr(1);
  if (!module->hasFunction(funcName))
    throw std::runtime_error("Function name not found in the module");
  auto func = module->function(funcName);
  auto realArgCtx = ctx->functionArguments();
  if (!ctx->type())
    throw std::runtime_error("Call instruction must have a return type");
  visitType(ctx->type());

  auto retType = func->returnType();
  if (retType != Type::voidType(*llvmContext)) {
    if (!ctx->Equals())
      logger->warn("Warning: Return value is discarded");
    if (ctx->type()->typeRef != retType)
      throw std::runtime_error(
          "Return type does not match the function return type");
  } else
    if (ctx->Equals())
      throw std::runtime_error(
          "Function with void return type cannot have a return value");
  if (func->returnType() != ctx->type()->typeRef)
    throw std::runtime_error(
        "Return type does not match the function return type");
  visitFunctionArguments(realArgCtx);

  const auto &realArgTypes = realArgCtx->argTypes;
  const auto &realArgNames = realArgCtx->argNames;
  std::vector<Ref<Value>> args(realArgTypes.size());
  for (size_t i = 0; i < realArgTypes.size(); ++i) {
    auto arg = resolveValueUsage(realArgTypes.at(i), realArgNames.at(i));
    if (arg->type() != realArgTypes.at(i))
      throw std::runtime_error(
          "Argument type does not match the function argument type");
    args[i] = arg;
  }
  auto resultName = ctx->Equals() ? ctx->localIdentifier()->getText()
                                  : "__call_void_ret_" + std::to_string(id++);
  auto callInst = IRBuilder(*currentBasicBlock)
                      .createCallInst({
                          .name = resultName,
                          .type = func->returnType(),
                          .function = func,
                          .realArgs = std::move(args),
                      });
  logger->info("Call instruction created in block {}: {}",
               currentBasicBlock->name(), callInst->toString());
  return {};
}

std::any
ModuleBuilder::visitPhiInstruction(LLVMParser::PhiInstructionContext *ctx) {
  auto mergeValCtx = ctx->localIdentifier();
  const auto &mergeValName = variableName(mergeValCtx);
  if (currentFunction->hasIdentifier(mergeValName))
    throw std::runtime_error(
        "Variable name already exists in the function identifiers");
  auto type = ctx->type();
  visitType(type);
  auto phiType = type->typeRef;
  auto phiValues = ctx->phiValue();
  std::vector<PhiValue> values(phiValues.size());
  for (size_t i = 0; i < phiValues.size(); ++i) {
    auto phiValCtx = phiValues[i];
    phiValCtx->typeRef = phiType;
    visitPhiValue(phiValCtx);
    auto incomingBlock = phiValCtx->block;
    auto incomingVal = phiValCtx->value;
    values.at(i) = PhiValue{incomingBlock, incomingVal};
    if (i && values.at(i).value->type() != values.at(i - 1).value->type())
      throw std::runtime_error("Phi values must have the same type");
  }
  auto phiInst = IRBuilder(*currentBasicBlock)
                     .createPhiInst({.name = mergeValName,
                                     .type = values.front().value->type(),
                                     .incomingPhiValues = std::move(values)});
  logger->info("Phi instruction created in block {} : {}",
               currentBasicBlock->name(), phiInst->toString());
  return {};
}

std::any ModuleBuilder::visitPhiValue(LLVMParser::PhiValueContext *ctx) {
  const auto &label = ctx->localIdentifier()->getText();
  auto value =
      resolveImmediateValueUsage(ctx->typeRef, ctx->immediatelyUsableValue());
  ctx->block = makeRef(currentFunction->basicBlock(label));
  ctx->value = value;
  return {};
}
Ref<Value> ModuleBuilder::resolveValueUsage(CRef<Type> type,
                                            const std::string &name) const {
  if (name.at(0) == '%') {
    auto argRef = currentFunction->hasArg(name)
                      ? makeRef(currentFunction->arg(name))
                      : makeRef(currentFunction->identifier(name));
    if (argRef->type() != type)
      throw std::runtime_error(
          "Argument type does not match the specified type");
    return argRef;
  }
  return llvmContext->constant(type, name);
}

BuildResult buildModule(const std::filesystem::path &path) {
  std::ifstream stream(path);
  if (!stream)
    throw std::runtime_error("Failed to open file: " + path.string());
  try {
    antlr4::ANTLRInputStream input(stream);
    LLVMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LLVMParser parser(&tokens);
    return ModuleBuilder().build(parser.module());
  } catch (const std::exception &ex) {
    std::cerr << "Building failed: " << ex.what() << std::endl;
    std::terminate();
  }
}

} // namespace llvm
