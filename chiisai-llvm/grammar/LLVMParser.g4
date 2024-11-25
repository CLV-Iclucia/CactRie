parser grammar LLVMParser;
@header {
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/ref.h>
    #include <chiisai-llvm/type.h>
    #include <chiisai-llvm/basic-block.h>
    #include <chiisai-llvm/constant.h>
    #include <chiisai-llvm/array-type.h>
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

localIdentifier: Percent (NamedIdentifier | NumericIdentifier);

variable
    locals[
    bool isGlobal,
]: globalIdentifier | localIdentifier;

literal : IntegerLiteral | FloatLiteral;

number: scalarType literal;

immediatelyUsableValue
    locals[
    bool isConstant,
]: localIdentifier | number;

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

returnInstruction: Ret (type immediatelyUsableValue)?;

branchInstruction: Br I1 localIdentifier Comma Label localIdentifier Comma Label localIdentifier
                | Br Label localIdentifier;

callInstruction: (localIdentifier Equals)? Call type globalIdentifier functionArguments;

arithmeticInstruction
    : localIdentifier Equals binaryOperation type immediatelyUsableValue Comma immediatelyUsableValue
    ;

loadInstruction
    : localIdentifier Equals Load type Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

storeInstruction
    : Store type immediatelyUsableValue Comma type Asterisk variable (Comma Align IntegerLiteral)?
    ;

phiInstruction
    : localIdentifier Equals Phi type phiValue (Comma phiValue)*
    ;

phiValue
    locals [
        CRef<BasicBlock> block,
        Ref<Value> value,
    ]: LeftBrace localIdentifier Comma immediatelyUsableValue RightBrace;

comparisonOperation : Icmp | Fcmp;

comparisonInstruction
    : localIdentifier Equals comparisonOperation comparisonPredicate type immediatelyUsableValue Comma immediatelyUsableValue
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

// GetElementPtr instruction
// currently, we don't support multiple indices
// multidimensional arrays should be flattened
gepInstruction
    : localIdentifier Equals GetElementPtr type Comma type Asterisk variable (Comma immediatelyUsableValue)?
    ;