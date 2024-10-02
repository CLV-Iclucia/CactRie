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

basicType
    locals[
    CRef<Type> typeRef,
]: Void | I1 | I32 | I64 | F32 | F64;

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

variable: globalIdentifier | localVariable;

number: IntegerLiteral | FloatLiteral;

value: variable | number;

module: (globalDeclaration | functionDefinition)*;

initializer
locals[
    Literal result,
]: IntegerLiteral | FloatLiteral | constantArray;

constantArray
locals[
    std::vector<Literal> elements,
]: LeftBracket type IntegerLiteral Cross value (Comma value)* RightBracket;

globalDeclaration
 locals [
    Variable globalVar,
]: Global type globalIdentifier (Comma Align initializer)?;

functionDefinition
 locals [
    std::unique_ptr<Function> function,
]: Define type globalIdentifier functionArguments block;

functionArguments: LeftParen parameterList? RightParen;

parameterList: parameter (Comma parameter)*;

parameter: type localIdentifier;

block: LeftBrace basicBlock* RightBrace;

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
    | memoryInstruction
    | phiInstruction
    | comparisonInstruction
    ;

returnInstruction: Ret type value?;

branchInstruction: Br I1 value Comma Label unamedIdentifier Comma Label unamedIdentifier
                | Br Label unamedIdentifier;

callInstruction: Call type globalIdentifier functionArguments;

arithmeticInstruction
    : localVariable Equals binaryOperation type value Comma value
    ;

memoryInstruction
    : localVariable Equals (Load | Store) type Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

phiInstruction
    : Phi type phiValue (Comma phiValue)*
    ;

phiValue: LeftBrace unamedIdentifier Comma value RightBrace;

comparisonInstruction
    : (Icmp | Fcmp) comparisonPredicate type value Comma value
    ;

binaryOperation
    : Add | Sub | Mul | Div
    ;

comparisonPredicate
    : Eq | Ne | Ugt | Uge | Ult | Ule | Sgt | Sge | Slt | Sle
    ;