parser grammar LLVMParser;
@header {
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/ref.h>
    #include <chiisai-llvm/type.h>
    #include <chiisai-llvm/basic-block.h>
}
options {
    tokenVocab=LLVMLexer;
}

scalarType : I1 | I32 | I64 | F32 | F64;

basicType
    locals[
    CRef<Type> typeRef,
]: Void | scalarType;

type
    locals[
    CRef<Type> typeRef,
]: basicType | pointerType | arrayType;

pointerType
    locals[
    CRef<Type> typeRef,
]: basicType Asterisk+ | pointerType Asterisk+ | arrayType Asterisk+;

arrayType
    locals[
    CRef<Type> typeRef,
]: LeftBracket IntegerLiteral Cross type RightBracket;

globalIdentifier: At NamedIdentifier;

localIdentifier: Percent NamedIdentifier;

unamedIdentifier: Percent NumericIdentifier;

localVariable: localIdentifier | unamedIdentifier;

variable
    locals[
    bool isGlobal,
    std::string name,
]: globalIdentifier | localVariable;

literal : IntegerLiteral | FloatLiteral;

number: scalarType literal;

value
    locals[
    bool isGlobal,
    bool isConstant,
]: variable | number;

module: (globalDeclaration | functionDefinition)*;

initializer
locals[
    Literal result,
]: IntegerLiteral | FloatLiteral | constantArray;

constantArray
locals[
    CRef<ConstantArray> constArray,
]: LeftBracket type IntegerLiteral Cross value (Comma value)* RightBracket;

globalDeclaration : Global type globalIdentifier (Comma Align initializer)?;

functionDefinition
 locals [
    std::unique_ptr<Function> function,
    std::vector<CRef<Type>> argTypes,
    std::vector<std::string> argNames,
]: Define type globalIdentifier functionArguments LeftBrace basicBlock* RightBrace;

functionArguments
 locals [
    std::vector<CRef<Type>> argTypes,
    std::vector<std::string> argNames,
]: LeftParen parameterList? RightParen;

parameterList
 locals[
    std::vector<CRef<Type>> argTypes,
    std::vector<std::string> argNames,
]: parameter (Comma parameter)*;

parameter
  locals [
     CRef<Type> argType,
     std::string argName,
]: type localIdentifier;

basicBlock
  locals [
      std::unique_ptr<BasicBlock> basicBlockInstance,
]: Label Colon instruction*;

instruction
  locals [
      std::unique_ptr<Instruction> inst,
]: returnInstruction
    | branchInstruction
    | callInstruction
    | arithmeticInstruction
    | loadInstruction
    | storeInstruction
    | phiInstruction
    | comparisonInstruction
    | allocaInstruction
    ;

returnInstruction: Ret type value?;

branchInstruction: Br I1 value Comma Label unamedIdentifier Comma Label unamedIdentifier
                | Br Label unamedIdentifier;

callInstruction: Call type globalIdentifier functionArguments;

arithmeticInstruction
    : unamedIdentifier Equals binaryOperation type value Comma value
    ;

loadInstruction
    : unamedIdentifier Equals Load type Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

storeInstruction
    : Store type value Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

phiInstruction
    : Phi type phiValue (Comma phiValue)*
    ;

phiValue: LeftBrace unamedIdentifier Comma value RightBrace;

comparisonOperation : Icmp | Fcmp;

comparisonInstruction
    : unamedIdentifier Equals comparisonOperation comparisonPredicate type value Comma value
    ;

allocaInstruction
    : localIdentifier Equals Alloca type
    ;

binaryOperation
    : Add | Sub | Mul | Div
    ;

comparisonPredicate
    : Eq | Ne | Ugt | Uge | Ult | Ule | Sgt | Sge | Slt | Sle
    ;