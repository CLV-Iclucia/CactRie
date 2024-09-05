
// Generated from ./grammar/LLVMParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"


namespace llvm {


class  LLVMParser : public antlr4::Parser {
public:
  enum {
    Global = 1, External = 2, Define = 3, Align = 4, Unreachable = 5, Br = 6, 
    Ret = 7, Call = 8, Load = 9, Store = 10, Alloca = 11, Phi = 12, Add = 13, 
    Sub = 14, Mul = 15, Div = 16, And = 17, Or = 18, Xor = 19, Shl = 20, 
    Lshr = 21, Ashr = 22, Icmp = 23, Fcmp = 24, Sext = 25, Zext = 26, Trunc = 27, 
    Label = 28, Void = 29, Ptr = 30, I1 = 31, I32 = 32, I64 = 33, F32 = 34, 
    F64 = 35, Eq = 36, Ne = 37, Ugt = 38, Uge = 39, Ult = 40, Ule = 41, 
    Sgt = 42, Sge = 43, Slt = 44, Sle = 45, Equals = 46, Comma = 47, LeftParen = 48, 
    RightParen = 49, LeftBrace = 50, RightBrace = 51, At = 52, Percent = 53, 
    Asterisk = 54, Colon = 55, NumericIdentifier = 56, NamedIdentifier = 57, 
    IntegerLiteral = 58, FloatLiteral = 59, Whitespace = 60, Comment = 61
  };

  enum {
    RuleType = 0, RuleGlobalIdentifier = 1, RuleLocalIdentifier = 2, RuleUnamedIdentifier = 3, 
    RuleVariable = 4, RuleNumber = 5, RuleValue = 6, RuleModule = 7, RuleGlobalDeclaration = 8, 
    RuleFunctionDefinition = 9, RuleFunctionParameters = 10, RuleParameterList = 11, 
    RuleParameter = 12, RuleBlock = 13, RuleBasicBlock = 14, RuleInstruction = 15, 
    RuleReturnInstruction = 16, RuleBranchInstruction = 17, RuleCallInstruction = 18, 
    RuleArithmeticInstruction = 19, RuleMemoryInstruction = 20, RulePhiInstruction = 21, 
    RulePhiValue = 22, RuleComparisonInstruction = 23, RuleComparisonPredicate = 24
  };

  explicit LLVMParser(antlr4::TokenStream *input);

  LLVMParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~LLVMParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class TypeContext;
  class GlobalIdentifierContext;
  class LocalIdentifierContext;
  class UnamedIdentifierContext;
  class VariableContext;
  class NumberContext;
  class ValueContext;
  class ModuleContext;
  class GlobalDeclarationContext;
  class FunctionDefinitionContext;
  class FunctionParametersContext;
  class ParameterListContext;
  class ParameterContext;
  class BlockContext;
  class BasicBlockContext;
  class InstructionContext;
  class ReturnInstructionContext;
  class BranchInstructionContext;
  class CallInstructionContext;
  class ArithmeticInstructionContext;
  class MemoryInstructionContext;
  class PhiInstructionContext;
  class PhiValueContext;
  class ComparisonInstructionContext;
  class ComparisonPredicateContext; 

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *Ptr();
    antlr4::tree::TerminalNode *I1();
    antlr4::tree::TerminalNode *I32();
    antlr4::tree::TerminalNode *I64();
    antlr4::tree::TerminalNode *F32();
    antlr4::tree::TerminalNode *F64();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  GlobalIdentifierContext : public antlr4::ParserRuleContext {
  public:
    GlobalIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *At();
    antlr4::tree::TerminalNode *NamedIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalIdentifierContext* globalIdentifier();

  class  LocalIdentifierContext : public antlr4::ParserRuleContext {
  public:
    LocalIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Percent();
    antlr4::tree::TerminalNode *NamedIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocalIdentifierContext* localIdentifier();

  class  UnamedIdentifierContext : public antlr4::ParserRuleContext {
  public:
    UnamedIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Percent();
    antlr4::tree::TerminalNode *NumericIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnamedIdentifierContext* unamedIdentifier();

  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GlobalIdentifierContext *globalIdentifier();
    LocalIdentifierContext *localIdentifier();
    UnamedIdentifierContext *unamedIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableContext* variable();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *FloatLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumberContext* number();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    NumberContext *number();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueContext* value();

  class  ModuleContext : public antlr4::ParserRuleContext {
  public:
    ModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GlobalDeclarationContext *> globalDeclaration();
    GlobalDeclarationContext* globalDeclaration(size_t i);
    std::vector<FunctionDefinitionContext *> functionDefinition();
    FunctionDefinitionContext* functionDefinition(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleContext* module();

  class  GlobalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    GlobalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Global();
    TypeContext *type();
    GlobalIdentifierContext *globalIdentifier();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *Align();
    antlr4::tree::TerminalNode *IntegerLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalDeclarationContext* globalDeclaration();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Define();
    TypeContext *type();
    GlobalIdentifierContext *globalIdentifier();
    FunctionParametersContext *functionParameters();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionParametersContext : public antlr4::ParserRuleContext {
  public:
    FunctionParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ParameterListContext *parameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionParametersContext* functionParameters();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    LocalIdentifierContext *localIdentifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<BasicBlockContext *> basicBlock();
    BasicBlockContext* basicBlock(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  BasicBlockContext : public antlr4::ParserRuleContext {
  public:
    BasicBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Label();
    antlr4::tree::TerminalNode *Colon();
    std::vector<InstructionContext *> instruction();
    InstructionContext* instruction(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicBlockContext* basicBlock();

  class  InstructionContext : public antlr4::ParserRuleContext {
  public:
    InstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ReturnInstructionContext *returnInstruction();
    BranchInstructionContext *branchInstruction();
    CallInstructionContext *callInstruction();
    ArithmeticInstructionContext *arithmeticInstruction();
    MemoryInstructionContext *memoryInstruction();
    PhiInstructionContext *phiInstruction();
    ComparisonInstructionContext *comparisonInstruction();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstructionContext* instruction();

  class  ReturnInstructionContext : public antlr4::ParserRuleContext {
  public:
    ReturnInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ret();
    TypeContext *type();
    ValueContext *value();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnInstructionContext* returnInstruction();

  class  BranchInstructionContext : public antlr4::ParserRuleContext {
  public:
    BranchInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Br();
    antlr4::tree::TerminalNode *I1();
    ValueContext *value();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Label();
    antlr4::tree::TerminalNode* Label(size_t i);
    std::vector<UnamedIdentifierContext *> unamedIdentifier();
    UnamedIdentifierContext* unamedIdentifier(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BranchInstructionContext* branchInstruction();

  class  CallInstructionContext : public antlr4::ParserRuleContext {
  public:
    CallInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Call();
    TypeContext *type();
    GlobalIdentifierContext *globalIdentifier();
    FunctionParametersContext *functionParameters();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallInstructionContext* callInstruction();

  class  ArithmeticInstructionContext : public antlr4::ParserRuleContext {
  public:
    ArithmeticInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    antlr4::tree::TerminalNode *Equals();
    TypeContext *type();
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *Add();
    antlr4::tree::TerminalNode *Sub();
    antlr4::tree::TerminalNode *Mul();
    antlr4::tree::TerminalNode *Div();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArithmeticInstructionContext* arithmeticInstruction();

  class  MemoryInstructionContext : public antlr4::ParserRuleContext {
  public:
    MemoryInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VariableContext *> variable();
    VariableContext* variable(size_t i);
    antlr4::tree::TerminalNode *Equals();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);
    antlr4::tree::TerminalNode *Asterisk();
    antlr4::tree::TerminalNode *Load();
    antlr4::tree::TerminalNode *Store();
    antlr4::tree::TerminalNode *Align();
    antlr4::tree::TerminalNode *IntegerLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MemoryInstructionContext* memoryInstruction();

  class  PhiInstructionContext : public antlr4::ParserRuleContext {
  public:
    PhiInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Phi();
    TypeContext *type();
    std::vector<PhiValueContext *> phiValue();
    PhiValueContext* phiValue(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PhiInstructionContext* phiInstruction();

  class  PhiValueContext : public antlr4::ParserRuleContext {
  public:
    PhiValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    UnamedIdentifierContext *unamedIdentifier();
    antlr4::tree::TerminalNode *Comma();
    ValueContext *value();
    antlr4::tree::TerminalNode *RightBrace();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PhiValueContext* phiValue();

  class  ComparisonInstructionContext : public antlr4::ParserRuleContext {
  public:
    ComparisonInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComparisonPredicateContext *comparisonPredicate();
    TypeContext *type();
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *Icmp();
    antlr4::tree::TerminalNode *Fcmp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonInstructionContext* comparisonInstruction();

  class  ComparisonPredicateContext : public antlr4::ParserRuleContext {
  public:
    ComparisonPredicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Eq();
    antlr4::tree::TerminalNode *Ne();
    antlr4::tree::TerminalNode *Ugt();
    antlr4::tree::TerminalNode *Uge();
    antlr4::tree::TerminalNode *Ult();
    antlr4::tree::TerminalNode *Ule();
    antlr4::tree::TerminalNode *Sgt();
    antlr4::tree::TerminalNode *Sge();
    antlr4::tree::TerminalNode *Slt();
    antlr4::tree::TerminalNode *Sle();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonPredicateContext* comparisonPredicate();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace llvm
