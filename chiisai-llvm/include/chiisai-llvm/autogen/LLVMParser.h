
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/ref.h>
    #include <chiisai-llvm/type.h>
    #include <chiisai-llvm/basic-block.h>


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
    RightParen = 49, LeftBrace = 50, RightBrace = 51, LeftBracket = 52, 
    RightBracket = 53, At = 54, Percent = 55, Asterisk = 56, Colon = 57, 
    Cross = 58, NumericIdentifier = 59, NamedIdentifier = 60, IntegerLiteral = 61, 
    FloatLiteral = 62, Whitespace = 63, Comment = 64
  };

  enum {
    RuleBasicType = 0, RuleType = 1, RulePointerType = 2, RuleArrayType = 3, 
    RuleGlobalIdentifier = 4, RuleLocalIdentifier = 5, RuleUnamedIdentifier = 6, 
    RuleVariable = 7, RuleNumber = 8, RuleValue = 9, RuleModule = 10, RuleInitializer = 11, 
    RuleConstantArray = 12, RuleGlobalDeclaration = 13, RuleFunctionDefinition = 14, 
    RuleFunctionArguments = 15, RuleParameterList = 16, RuleParameter = 17, 
    RuleBlock = 18, RuleBasicBlock = 19, RuleInstruction = 20, RuleReturnInstruction = 21, 
    RuleBranchInstruction = 22, RuleCallInstruction = 23, RuleArithmeticInstruction = 24, 
    RuleMemoryInstruction = 25, RulePhiInstruction = 26, RulePhiValue = 27, 
    RuleComparisonInstruction = 28, RuleBinaryOperation = 29, RuleComparisonPredicate = 30
  };

  explicit LLVMParser(antlr4::TokenStream *input);

  LLVMParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~LLVMParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class BasicTypeContext;
  class TypeContext;
  class PointerTypeContext;
  class ArrayTypeContext;
  class GlobalIdentifierContext;
  class LocalIdentifierContext;
  class UnamedIdentifierContext;
  class VariableContext;
  class NumberContext;
  class ValueContext;
  class ModuleContext;
  class InitializerContext;
  class ConstantArrayContext;
  class GlobalDeclarationContext;
  class FunctionDefinitionContext;
  class FunctionArgumentsContext;
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
  class BinaryOperationContext;
  class ComparisonPredicateContext; 

  class  BasicTypeContext : public antlr4::ParserRuleContext {
  public:
    CRef<Type> typeRef;
    BasicTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *I1();
    antlr4::tree::TerminalNode *I32();
    antlr4::tree::TerminalNode *I64();
    antlr4::tree::TerminalNode *F32();
    antlr4::tree::TerminalNode *F64();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicTypeContext* basicType();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    CRef<Type> typeRef;
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    PointerTypeContext *pointerType();
    ArrayTypeContext *arrayType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  PointerTypeContext : public antlr4::ParserRuleContext {
  public:
    CRef<Type> typeRef;
    PointerTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    std::vector<antlr4::tree::TerminalNode *> Asterisk();
    antlr4::tree::TerminalNode* Asterisk(size_t i);
    ArrayTypeContext *arrayType();
    PointerTypeContext *pointerType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PointerTypeContext* pointerType();
  PointerTypeContext* pointerType(int precedence);
  class  ArrayTypeContext : public antlr4::ParserRuleContext {
  public:
    CRef<Type> typeRef;
    ArrayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *Cross();
    TypeContext *type();
    antlr4::tree::TerminalNode *RightBracket();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayTypeContext* arrayType();

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

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    Literal result;
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *FloatLiteral();
    ConstantArrayContext *constantArray();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerContext* initializer();

  class  ConstantArrayContext : public antlr4::ParserRuleContext {
  public:
    std::vector<Literal> elements;
    ConstantArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    TypeContext *type();
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *Cross();
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    antlr4::tree::TerminalNode *RightBracket();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantArrayContext* constantArray();

  class  GlobalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    Variable globalVar;
    GlobalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Global();
    TypeContext *type();
    GlobalIdentifierContext *globalIdentifier();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *Align();
    InitializerContext *initializer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalDeclarationContext* globalDeclaration();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    std::unique_ptr<Function> function;
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Define();
    TypeContext *type();
    GlobalIdentifierContext *globalIdentifier();
    FunctionArgumentsContext *functionArguments();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionArgumentsContext : public antlr4::ParserRuleContext {
  public:
    FunctionArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ParameterListContext *parameterList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionArgumentsContext* functionArguments();

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
    std::unique_ptr<BasicBlock> basicBlockInstance;
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
    std::unique_ptr<Instruction> inst;
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
    FunctionArgumentsContext *functionArguments();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallInstructionContext* callInstruction();

  class  ArithmeticInstructionContext : public antlr4::ParserRuleContext {
  public:
    ArithmeticInstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    antlr4::tree::TerminalNode *Equals();
    BinaryOperationContext *binaryOperation();
    TypeContext *type();
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);
    antlr4::tree::TerminalNode *Comma();


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

  class  BinaryOperationContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Add();
    antlr4::tree::TerminalNode *Sub();
    antlr4::tree::TerminalNode *Mul();
    antlr4::tree::TerminalNode *Div();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BinaryOperationContext* binaryOperation();

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


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool pointerTypeSempred(PointerTypeContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace llvm