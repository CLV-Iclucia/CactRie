//
// Created by creeper on 9/29/24.
//
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/module-builder.h>
#include <chiisai-llvm/mystl/castings.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/module.h>
namespace llvm {

std::any llvm::ModuleBuilder::visitModule(LLVMParser::ModuleContext *ctx) {

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
  if (elementType == Type::voidType(*llvmContext)) {
    // ERROR
    throw std::runtime_error("Array type cannot have void type as its element type");
  }
  ctx->typeRef = llvmContext->arrayType(elementType, size);
  return {};
}

std::any ModuleBuilder::visitPointerType(LLVMParser::PointerTypeContext *ctx) {
  auto elementTypeNode = ctx->basicType();
  visitBasicType(elementTypeNode);
  auto elementType = elementTypeNode->typeRef;
  if (elementType == Type::voidType(*llvmContext)) {
    // ERROR
  }
  ctx->typeRef = llvmContext->pointerType(elementType);
  return {};
}

Ref<Value> ModuleBuilder::resolveValueUsage(LLVMParser::ValueContext *ctx) {
  visitValue(ctx);
  if (ctx->number()) {
    auto type = llvmContext->stobt(ctx->number()->scalarType()->getText());
    const auto &str = ctx->number()->literal()->getText();
    return llvmContext->constant(type, str);
  } else {
    auto var = ctx->variable();
    return resolveVariableUsageAfterVisit(var);
  }
}

Ref<Value> ModuleBuilder::resolveVariableUsageAfterVisit(LLVMParser::VariableContext *ctx) const {
  if (ctx->isGlobal)
    return module->globalVariable(ctx->name);

  if (currentFunction->hasArg(ctx->name))
    return ref(currentFunction->arg(ctx->name));

  if (currentFunction->hasIdentifier(ctx->name))
    return ref(currentFunction->identifier(ctx->name));

  // ERROR: cannot find the symbol
  throw std::runtime_error("Cannot find the symbol");
}

Ref<Value> ModuleBuilder::resolveVariableUsage(LLVMParser::VariableContext *ctx) {
  visitVariable(ctx);
  return resolveVariableUsageAfterVisit(ctx);
}

static std::vector<CRef<Type>> formContainedTypes(CRef<Type> returnType, std::vector<CRef<Type>> &&argTypes) {
  std::vector<CRef<Type>> containedTypes;
  containedTypes.reserve(1 + argTypes.size());
  containedTypes.push_back(returnType);
  containedTypes.insert(containedTypes.end(), argTypes.begin(), argTypes.end());
  return containedTypes;
}

std::any ModuleBuilder::visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) {
  auto returnTypeCtx = ctx->type();
  auto funcName = ctx->globalIdentifier()->NamedIdentifier()->getText();

  if (module->hasFunction(funcName))
    throw std::runtime_error("Function name already exists in the module");
  if (module->hasGlobalVar(funcName))
    throw std::runtime_error("Global variable name already exists in the module");

  visitType(returnTypeCtx);
  auto returnType = returnTypeCtx->typeRef;
  auto args = ctx->functionArguments();
  visitFunctionArguments(args);
  // append argTypes and returnTypes together to form containedTypes
  std::vector<CRef<Type>> containedTypes = formContainedTypes(returnType, std::move(args->argTypes));
  auto functionType = llvmContext->functionType(containedTypes);
  const auto &basicBlocks = ctx->basicBlock();
  module->addFunction(std::make_unique<Function>(FunctionInfo{.name = funcName,
      .functionType = llvmContext->functionType(containedTypes),
      .argNames = std::move(args->argNames),
      .module = *module}));
  std::list<BasicBlock> basicBlocksList{};
  for (auto bb : basicBlocks)
    visitBasicBlock(bb);
  return {};
}

std::any ModuleBuilder::visitBasicBlock(LLVMParser::BasicBlockContext *ctx) {
  ctx->basicBlockInstance = std::make_unique<BasicBlock>(ctx->Label()->getText());
  const auto &instructions = ctx->instruction();
  for (auto inst : instructions)
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
  } else if (arrayTy) {
    assert(!pointerTy);
    visitArrayType(arrayTy);
  } else if (pointerTy) {
    visitPointerType(pointerTy);
  } else
    throw std::runtime_error("the type is neither basic, array nor pointer type, which is impossible");
  return {};
}

std::any ModuleBuilder::visitArithmeticInstruction(LLVMParser::ArithmeticInstructionContext *ctx) {
  auto lhs = ctx->unamedIdentifier();
  auto lhsName = variableName(lhs);
  if (currentFunction->hasArg(lhsName))
    throw std::runtime_error("Variable name already exists in the function arguments");
  const auto &operands = ctx->value();

  if (operands.size() != 2)
    throw std::runtime_error("Arithmetic instruction must have exactly two operands");

  auto operandLeftRef = resolveValueUsage(operands[0]);
  auto operandRightRef = resolveValueUsage(operands[1]);

  if (!Instruction::checkBinaryInstType(operandLeftRef, operandRightRef))
    throw std::runtime_error("Binary instruction operands must have the same type");

  auto opcode = stoinst(ctx->binaryOperation()->getText());
  IRBuilder(*currentBasicBlock).createBinaryInst(opcode,
                                                 {
                                                     .name = lhsName,
                                                     .type = operandLeftRef->type(),
                                                     .lhs = operandLeftRef,
                                                     .rhs = operandRightRef,
                                                 });

  return {};
}

std::any ModuleBuilder::visitComparisonInstruction(LLVMParser::ComparisonInstructionContext *ctx) {
  auto cmpOp = ctx->comparisonOperation()->getText();
  auto predicateStr = ctx->comparisonPredicate()->getText();
  auto lhsRef = resolveValueUsage(ctx->value(0));
  auto rhsRef = resolveValueUsage(ctx->value(1));
  IRBuilder(*currentBasicBlock).createCmpInst(stoinst(cmpOp), {
      .ctx = *llvmContext,
      .name = ctx->unamedIdentifier()->getText(),
      .lhs = lhsRef,
      .rhs = rhsRef,
      .predicate = stopdct(predicateStr)
  });
  return {};
}

std::any ModuleBuilder::visitLoadInstruction(LLVMParser::LoadInstructionContext *ctx) {
  auto dest = ctx->unamedIdentifier();
  visitUnamedIdentifier(dest);
  auto destName = variableName(dest);

  if (currentFunction->hasIdentifier(destName))
    throw std::runtime_error("Variable name already exists in the function locals");
  if (currentFunction->hasArg(destName))
    throw std::runtime_error("Variable name already exists in the function arguments");

  auto src = resolveVariableUsage(ctx->variable());
  IRBuilder(*currentBasicBlock).createLoadInst(
      {
          .name = destName,
          .type = src->type(),
          .pointer = src
      });
  return {};
}

std::any ModuleBuilder::visitStoreInstruction(LLVMParser::StoreInstructionContext *ctx) {

}

std::any ModuleBuilder::visitAllocaInstruction(LLVMParser::AllocaInstructionContext *ctx) {
  auto varType = ctx->type();
  visitType(varType);
  auto varName = variableName(ctx->localIdentifier());
  int hasAlign = ctx->Align() != nullptr;
  // ctx should have hasAlign integer literals, if there is more, it should have size
  int hasSize = ctx->IntegerLiteral().size() > hasAlign;
  size_t size = hasSize ? std::stoul(ctx->IntegerLiteral(0)->getText()) : 1;
  // 0 means no alignment required
  size_t alignment = hasAlign ? std::stoul(ctx->IntegerLiteral().back()->getText()) : 0;
  if (currentFunction->hasArg(varName)) {
    // ERROR
    throw std::runtime_error("Variable name already exists in the function arguments");
  }
  IRBuilder(*currentBasicBlock).createAllocaInst({
                                                     .name = varName,
                                                     .type = llvmContext->pointerType(varType->typeRef),
                                                     .size = size,
                                                     .alignment = alignment
                                                 });
  return {};
}
std::any ModuleBuilder::visitValue(LLVMParser::ValueContext *ctx) {
  auto var = ctx->variable();
  auto number = ctx->number();
  if (var) {
    visitVariable(var);
    ctx->isConstant = false;
    ctx->isGlobal = var->isGlobal;
  } else if (number) {
    visitNumber(number);
    ctx->isConstant = true;
  } else
    throw std::runtime_error("Value must be either a variable or a number");
  return {};
}

std::any ModuleBuilder::visitGepInstruction(LLVMParser::GepInstructionContext *ctx) {
  auto gepVal = ctx->unamedIdentifier();
  visitUnamedIdentifier(gepVal);
  auto gepValName = variableName(gepVal);
  if (currentFunction->hasIdentifier(gepValName))
    throw std::runtime_error("Variable name already exists in the function identifiers");
  if (currentFunction->hasArg(gepValName))
    throw std::runtime_error("Variable name already exists in the function arguments");
  auto var = resolveVariableUsage(ctx->variable());
  auto indices = ctx->value();
  std::vector<Ref<Value>> indicesRef;
  indicesRef.reserve(indices.size());
  for (auto index : indices)
    indicesRef.push_back(resolveValueUsage(index));

  CRef<PointerType> pointerType{};
  if (var->type()->isPointer())
    pointerType = dyn_cast_ref<PointerType>(var->type());
  else if (var->type()->isArray())
    pointerType = llvmContext->castFromArrayType(dyn_cast_ref<ArrayType>(var->type()));
  else
    throw std::runtime_error("GEP instruction must have a pointer or an array type as the first operand");
  IRBuilder(*currentBasicBlock).createGepInst(
      {
          .name = gepValName,
          .type = pointerType,
          .pointer = var,
          .indices = std::move(indicesRef)
      });
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
    if (!type->isInteger())
      throw std::runtime_error("Invalid type for integer literal");
    ctx->constant = llvmContext->constant(type, ctx->IntegerLiteral()->getText());
  }
  if (ctx->FloatLiteral()) {
    visitScalarType(ctx->scalarType());
    auto type = ctx->scalarType()->typeRef;
    if (!type->isInteger())
      throw std::runtime_error("Invalid type for integer literal");
    ctx->constant = llvmContext->constant(type, ctx->FloatLiteral()->getText());
  }
  if (ctx->constantArray()) {
    auto constArrayCtx = ctx->constantArray();
    visitConstantArray(constArrayCtx);
    ctx->constant = constArrayCtx->constArray;
  }
  throw std::runtime_error("Initializer must be either an integer literal, a float literal or a constant array");
}

std::any ModuleBuilder::visitConstantArray(LLVMParser::ConstantArrayContext *ctx) {
  auto arrayTypeCtx = ctx->arrayType();
  visitArrayType(arrayTypeCtx);
  auto arrayType = arrayTypeCtx->typeRef;
  for (auto init : ctx->initializer()) {
    visitInitializer(init);
    if (init->constant->type() != arrayType->elementType())
      throw std::runtime_error("Initializer type does not match the array element type");
  }
  return {};
}

std::any ModuleBuilder::visitScalarType(LLVMParser::ScalarTypeContext *ctx) {
  ctx->typeRef = llvmContext->stobt(ctx->getText());
  return {};
}

}