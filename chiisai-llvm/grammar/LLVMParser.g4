parser grammar LLVMParser;
@header {
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/literal.h>
    #include <chiisai-llvm/llvm-ir.h>
}
options {
    tokenVocab=LLVMLexer;
}

basicType
    locals[
    LLVMType llvmType,
]: Void | I1 | I32 | I64 | F32 | F64;

type
    locals[
    LLVMType llvmType,
]: basicType | pointerType | arrayType;

pointerType
    locals[
    LLVMType llvmType,
]: basicType Asterisk+ | pointerType Asterisk+ | arrayType Asterisk+;

arrayType
    locals[
    LLVMType llvmType,
]: LeftBracket IntegerLiteral Cross type RightBracket;

globalIdentifier: At NamedIdentifier;

localIdentifier: Percent NamedIdentifier;

unamedIdentifier: Percent NumericIdentifier;

variable: globalIdentifier | localIdentifier | unamedIdentifier;

number: IntegerLiteral | FloatLiteral;

value: variable | number;

module: (globalDeclaration | functionDefinition)*;

literal
locals[
    Literal result,
]: IntegerLiteral | FloatLiteral;

globalDeclaration
 locals [
    Variable globalVar,
]: Global type globalIdentifier (Comma Align literal)?;

functionDefinition
 locals [
    std::unique_ptr<Function> function,
]: Define type globalIdentifier functionArguments block;

functionArguments: LeftParen parameterList? RightParen;

parameterList: parameter (Comma parameter)*;

parameter: type localIdentifier;

block: LeftBrace basicBlock* RightBrace;

basicBlock: Label Colon instruction*;

instruction: returnInstruction
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
    : variable Equals (Add | Sub | Mul | Div) type value Comma value
    ;

memoryInstruction
    : variable Equals (Load | Store) type Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

phiInstruction
    : Phi type phiValue (Comma phiValue)*
    ;

phiValue: LeftBrace unamedIdentifier Comma value RightBrace;

comparisonInstruction
    : (Icmp | Fcmp) comparisonPredicate type value Comma value
    ;

comparisonPredicate
    : Eq | Ne | Ugt | Uge | Ult | Ule | Sgt | Sge | Slt | Sle
    ;