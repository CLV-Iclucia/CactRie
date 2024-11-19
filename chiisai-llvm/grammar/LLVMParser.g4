parser grammar LLVMParser;
@header {
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/ref.h>
    #include <chiisai-llvm/type.h>
    #include <chiisai-llvm/basic-block.h>
    #include <chiisai-llvm/constants.h>
}
options {
    tokenVocab=LLVMLexer;
}

scalarType
    locals [
    CRef<Type> typeRef,
]: I1 | I32 | I64 | F32 | F64;

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
    CRef<ArrayType> typeRef,
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

pointee
    locals[
    bool isGlobal,
    bool isConstant,
]: variable | number;

module: (globalDeclaration | functionDefinition)*;

initializer
locals[
    CRef<Constant> constant,
]: scalarType IntegerLiteral | scalarType FloatLiteral | constantArray;

constantArray
locals[
    CRef<ConstantArray> constArray,
]: arrayType LeftBracket initializer (Comma initializer)* RightBracket;

globalDeclaration : globalIdentifier Equals (Global | Constant) initializer (Comma Align IntegerLiteral)?;

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
]:  callInstruction
    | arithmeticInstruction
    | loadInstruction
    | storeInstruction
    | phiInstruction
    | comparisonInstruction
    | allocaInstruction
    | terminatorInstruction
    | gepInstruction
    ;

returnInstruction: Ret type pointee?;

branchInstruction: Br I1 variable Comma Label localVariable Comma Label localVariable
                | Br Label localVariable;

callInstruction: (unamedIdentifier Equals)? Call type globalIdentifier functionArguments;

arithmeticInstruction
    : unamedIdentifier Equals binaryOperation type pointee Comma pointee
    ;

loadInstruction
    : unamedIdentifier Equals Load type Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

storeInstruction
    : Store type pointee Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

phiInstruction
    : Phi type phiValue (Comma phiValue)*
    ;

phiValue: LeftBrace unamedIdentifier Comma pointee RightBrace;

comparisonOperation : Icmp | Fcmp;

comparisonInstruction
    : unamedIdentifier Equals comparisonOperation comparisonPredicate type pointee Comma pointee
    ;

allocaInstruction
    : localIdentifier Equals Alloca type (Comma IntegerLiteral)? (Comma Align IntegerLiteral)?
    ;

binaryOperation
    : Add | Sub | Mul | Div
    ;

comparisonPredicate
    : Eq | Ne | Ugt | Uge | Ult | Ule | Sgt | Sge | Slt | Sle
    ;

terminatorInstruction
    : returnInstruction
    | branchInstruction
    ;

gepInstruction
    : unamedIdentifier Equals GetElementPtr type Comma type Asterisk variable Comma pointee (Comma pointee)*
    ;