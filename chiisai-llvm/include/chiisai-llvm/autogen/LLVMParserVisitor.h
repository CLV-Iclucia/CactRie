
// Generated from ./grammar/LLVMParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "LLVMParser.h"


namespace llvm {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by LLVMParser.
 */
class  LLVMParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LLVMParser.
   */
    virtual std::any visitType(LLVMParser::TypeContext *context) = 0;

    virtual std::any visitGlobalIdentifier(LLVMParser::GlobalIdentifierContext *context) = 0;

    virtual std::any visitLocalIdentifier(LLVMParser::LocalIdentifierContext *context) = 0;

    virtual std::any visitUnamedIdentifier(LLVMParser::UnamedIdentifierContext *context) = 0;

    virtual std::any visitVariable(LLVMParser::VariableContext *context) = 0;

    virtual std::any visitNumber(LLVMParser::NumberContext *context) = 0;

    virtual std::any visitValue(LLVMParser::ValueContext *context) = 0;

    virtual std::any visitModule(LLVMParser::ModuleContext *context) = 0;

    virtual std::any visitGlobalDeclaration(LLVMParser::GlobalDeclarationContext *context) = 0;

    virtual std::any visitFunctionDefinition(LLVMParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitFunctionParameters(LLVMParser::FunctionParametersContext *context) = 0;

    virtual std::any visitParameterList(LLVMParser::ParameterListContext *context) = 0;

    virtual std::any visitParameter(LLVMParser::ParameterContext *context) = 0;

    virtual std::any visitBlock(LLVMParser::BlockContext *context) = 0;

    virtual std::any visitBasicBlock(LLVMParser::BasicBlockContext *context) = 0;

    virtual std::any visitInstruction(LLVMParser::InstructionContext *context) = 0;

    virtual std::any visitReturnInstruction(LLVMParser::ReturnInstructionContext *context) = 0;

    virtual std::any visitBranchInstruction(LLVMParser::BranchInstructionContext *context) = 0;

    virtual std::any visitCallInstruction(LLVMParser::CallInstructionContext *context) = 0;

    virtual std::any visitArithmeticInstruction(LLVMParser::ArithmeticInstructionContext *context) = 0;

    virtual std::any visitMemoryInstruction(LLVMParser::MemoryInstructionContext *context) = 0;

    virtual std::any visitPhiInstruction(LLVMParser::PhiInstructionContext *context) = 0;

    virtual std::any visitPhiValue(LLVMParser::PhiValueContext *context) = 0;

    virtual std::any visitComparisonInstruction(LLVMParser::ComparisonInstructionContext *context) = 0;

    virtual std::any visitComparisonPredicate(LLVMParser::ComparisonPredicateContext *context) = 0;


};

}  // namespace llvm
