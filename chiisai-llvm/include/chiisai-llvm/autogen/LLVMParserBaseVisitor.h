
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/literal.h>
    #include <chiisai-llvm/llvm-ir.h>


// Generated from ./grammar/LLVMParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "LLVMParserVisitor.h"


namespace llvm {

/**
 * This class provides an empty implementation of LLVMParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LLVMParserBaseVisitor : public LLVMParserVisitor {
public:

  virtual std::any visitBasicType(LLVMParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(LLVMParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerType(LLVMParser::PointerTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(LLVMParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalIdentifier(LLVMParser::GlobalIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLocalIdentifier(LLVMParser::LocalIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnamedIdentifier(LLVMParser::UnamedIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable(LLVMParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(LLVMParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(LLVMParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModule(LLVMParser::ModuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(LLVMParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalDeclaration(LLVMParser::GlobalDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionArguments(LLVMParser::FunctionArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(LLVMParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(LLVMParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(LLVMParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicBlock(LLVMParser::BasicBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstruction(LLVMParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnInstruction(LLVMParser::ReturnInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBranchInstruction(LLVMParser::BranchInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallInstruction(LLVMParser::CallInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArithmeticInstruction(LLVMParser::ArithmeticInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemoryInstruction(LLVMParser::MemoryInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPhiInstruction(LLVMParser::PhiInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPhiValue(LLVMParser::PhiValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonInstruction(LLVMParser::ComparisonInstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonPredicate(LLVMParser::ComparisonPredicateContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace llvm
