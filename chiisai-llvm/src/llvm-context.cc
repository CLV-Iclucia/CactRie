//
// Created by creeper on 10/2/24.
//
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/ref.h>
#include <chiisai-llvm/type.h>
#include <chiisai-llvm/integer-type.h>
#include <chiisai-llvm/array-type.h>
#include <chiisai-llvm/pointer-type.h>
#include <chiisai-llvm/mystl/manager_vector.h>
#include <chiisai-llvm/instruction.h>
namespace llvm {

uint8_t stoinst(std::string_view str) {
  static std::unordered_map<std::string_view, uint8_t> map{
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
      {"invoke", Instruction::Invoke},
  };
  return map[str];
}

class LLVMContextImpl : NonMovable {
public:
  LLVMContextImpl() {
    basicTypeMap["void"] = cref(voidInstance);
    basicTypeMap["float"] = cref(floatInstance);
    basicTypeMap["double"] = cref(doubleInstance);
    basicTypeMap["i1"] = cref(boolInstance);
    basicTypeMap["i32"] = cref(intInstance);
    basicTypeMap["i64"] = cref(longInstance);
  }

  CRef<Type> stobt(std::string_view str) {
    return basicTypeMap[str];
  }

  CRef<ArrayType> arrayType(CRef<Type> elementType, size_t size) {
    auto it = arrayTypeMap.find({elementType, size});
    if (it != arrayTypeMap.end())
      return it->second;
    return createArrayType(elementType, size).arrayTypes.back();
  }

  CRef<PointerType> pointerType(CRef<Type> elementType) {
    auto it = pointerTypeMap.find(elementType);
    if (it != pointerTypeMap.end())
      return it->second;
    return createPointerType(elementType).pointerTypes.back();
  }

private:
  Type voidInstance{Type::TypeEnum::Void}, floatInstance{Type::TypeEnum::Float},
      doubleInstance{Type::TypeEnum::Double};
  IntegerType boolInstance{1}, intInstance{32}, longInstance{64};
  mystl::manager_vector<ArrayType> arrayTypes{};
  mystl::manager_vector<PointerType> pointerTypes{};
  std::unordered_map<std::string_view, CRef<Type>> basicTypeMap{};

  using ArrayTypeKey = std::pair<CRef<Type>, size_t>;
  using PointerTypeKey = CRef<Type>;
  std::unordered_map<ArrayTypeKey, CRef<ArrayType>> arrayTypeMap{};
  std::unordered_map<PointerTypeKey, CRef<PointerType>> pointerTypeMap{};

  LLVMContextImpl &createArrayType(CRef<Type> elementType, size_t size) {
    arrayTypes.emplace_back(elementType, size);
    return *this;
  }

  LLVMContextImpl &createPointerType(CRef<Type> elementType) {
    pointerTypes.emplace_back(elementType);
    return *this;
  }
};

LLVMContext::LLVMContext() : impl(std::make_unique<LLVMContextImpl>()) {}

LLVMContext::~LLVMContext() = default;

CRef<Type> LLVMContext::stobt(std::string_view str) const {
  return impl->stobt(str);
}

CRef<ArrayType> LLVMContext::arrayType(CRef<Type> elementType, size_t size) const {
  return impl->arrayType(elementType, size);
}

CRef<PointerType> LLVMContext::pointerType(CRef<Type> elementType) const {
  return impl->pointerType(elementType);
}

}  // namespace llvm
