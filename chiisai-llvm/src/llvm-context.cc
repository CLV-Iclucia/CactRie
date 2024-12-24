//
// Created by creeper on 10/2/24.
//
#include <format>
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/instruction.h>
#include <chiisai-llvm/type-system.h>
#include <chiisai-llvm/constant-pool.h>
#include <chiisai-llvm/constant-scalar.h>
namespace llvm {

uint8_t stoinst(const std::string &str) {
  static std::unordered_map<std::string, uint8_t> map{
      {"add", Instruction::Add},
      {"fadd", Instruction::FAdd},
      {"sub", Instruction::Sub},
      {"fsub", Instruction::FSub},
      {"mul", Instruction::Mul},
      {"fmul", Instruction::FMul},
      {"sdiv", Instruction::SDiv},
      {"fdiv", Instruction::FDiv},
      {"srem", Instruction::SRem},
      {"xor", Instruction::Xor},
      {"shl", Instruction::Shl},
      {"lshr", Instruction::LShr},
      {"ashr", Instruction::AShr},
      {"and", Instruction::And},
      {"or", Instruction::Or},
      {"alloca", Instruction::Alloca},
      {"load", Instruction::Load},
      {"store", Instruction::Store},
      {"ret", Instruction::Ret},
      {"br", Instruction::Br},
      {"call", Instruction::Call},
  };
  return map[str];
}

LLVMContext::LLVMContext() : typeSystem(std::make_unique<TypeSystem>()) {}
LLVMContext::~LLVMContext() = default;

CRef<Type> LLVMContext::stobt(const std::string &str) const {
  return typeSystem->stobt(str);
}

CRef<ArrayType> LLVMContext::arrayType(CRef<Type> elementType, size_t size) const {
  return typeSystem->arrayType(elementType, size);
}

CRef<PointerType> LLVMContext::pointerType(CRef<Type> elementType) const {
  return typeSystem->pointerType(elementType);
}

CRef<FunctionType> LLVMContext::functionType(const std::vector<CRef<Type>> &containedTypes) const {
  return typeSystem->functionType(containedTypes);
}

CRef<Type> LLVMContext::voidType() const {
  return makeCRef(typeSystem->voidInstance);
}

CRef<Type> LLVMContext::floatType() const {
  return makeCRef(typeSystem->floatInstance);
}

CRef<Type> LLVMContext::doubleType() const {
  return makeCRef(typeSystem->doubleInstance);
}

CRef<IntegerType> LLVMContext::boolType() const {
  return makeCRef(typeSystem->boolInstance);
}

CRef<IntegerType> LLVMContext::intType() const {
  return makeCRef(typeSystem->intInstance);
}

CRef<IntegerType> LLVMContext::longType() const {
  return makeCRef(typeSystem->longInstance);
}

Ref<Constant> LLVMContext::constant(CRef<Type> type, const std::string &str) const {
  return constantPool->constant(type, str);
}

CRef<PointerType> LLVMContext::castFromArrayType(CRef<ArrayType> arrayType) const {
  return typeSystem->pointerType(arrayType->elementType());
}

Scalar LLVMContext::evalConstScalar(CRef<ConstantScalar> constScalar) const {
  if (constScalar->type() == intType())
    return {std::stoi(constScalar->name())};
  if (constScalar->type() == longType())
    return {std::stoll(constScalar->name())};
  if (constScalar->type() == floatType())
    return {std::stof(constScalar->name())};
  if (constScalar->type() == doubleType())
    return {std::stod(constScalar->name())};
  if (constScalar->type() == boolType()) {
    auto intVal = std::stoi(constScalar->name());
    if (intVal == 0)
      return {false};
    if (intVal == 1)
      return {true};
    throw std::runtime_error("Invalid boolean value");
  }
  throw std::runtime_error("Invalid constant scalar type");
}
CRef<ConstantScalar> LLVMContext::constantZero(CRef<Type> type) const {
  return constantPool->constantZero(type);
}
CRef<Constant> LLVMContext::builtinVoidValue() const {
  return constantPool->constant(voidType(), "__builtin_void_typed_value");
}
CRef<Type> LLVMContext::labelType() const {
  return makeCRef(typeSystem->labelInstance);
}

}  // namespace llvm
