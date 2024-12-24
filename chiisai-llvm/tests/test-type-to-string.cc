//
// Created by creeper on 12/24/24.
//
#include <chiisai-llvm/llvm-context.h>
#include <chiisai-llvm/type.h>
#include <gtest/gtest.h>
using namespace llvm;

TEST(TypeToString, BasicTypes) {
  auto ctx = std::make_unique<LLVMContext>();
  EXPECT_EQ(ctx->stobt("i32")->toString(), "i32");
  EXPECT_EQ(ctx->intType()->toString(), "i32");
  EXPECT_EQ(ctx->stobt("i64")->toString(), "i64");
  EXPECT_EQ(ctx->longType()->toString(), "i64");
  EXPECT_EQ(ctx->stobt("i1")->toString(), "i1");
  EXPECT_EQ(ctx->boolType()->toString(), "i1");
  EXPECT_EQ(ctx->stobt("void")->toString(), "void");
  EXPECT_EQ(ctx->voidType()->toString(), "void");
  EXPECT_EQ(ctx->stobt("float")->toString(), "float");
  EXPECT_EQ(ctx->floatType()->toString(), "float");
  EXPECT_EQ(ctx->stobt("double")->toString(), "double");
  EXPECT_EQ(ctx->doubleType()->toString(), "double");
}

TEST(TypeToString, PointerType) {
  auto ctx = std::make_unique<LLVMContext>();
  auto i32 = ctx->intType();
  auto i32Ptr = ctx->pointerType(i32);
  EXPECT_EQ(i32Ptr->toString(), "i32*");
  auto i64 = ctx->longType();
  auto i64Ptr = ctx->pointerType(i64);
  EXPECT_EQ(i64Ptr->toString(), "i64*");
  auto i32PtrPtr = ctx->pointerType(i32Ptr);
  EXPECT_EQ(i32PtrPtr->toString(), "i32**");
}

TEST(TypeToString, ArrayType) {
  auto ctx = std::make_unique<LLVMContext>();
  auto i32 = ctx->intType();
  auto i32Array = ctx->arrayType(i32, 10);
  EXPECT_EQ(i32Array->toString(), "[10 x i32]");
  auto i64 = ctx->longType();
  auto i64Array = ctx->arrayType(i64, 20);
  EXPECT_EQ(i64Array->toString(), "[20 x i64]");
  auto i32ArrayArray = ctx->arrayType(i32Array, 30);
  EXPECT_EQ(i32ArrayArray->toString(), "[30 x [10 x i32]]");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
