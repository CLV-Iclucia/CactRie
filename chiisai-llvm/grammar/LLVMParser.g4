parser grammar LLVMParser;

options {
    tokenVocab=LLVMLexer;
}

type: Void | Ptr | I1 | I32 | I64 | F32 | F64;

globalIdentifier: At NamedIdentifier;

localIdentifier: Percent NamedIdentifier;

unamedIdentifier: Percent NumericIdentifier;

variable: globalIdentifier | localIdentifier | unamedIdentifier;

number: IntegerLiteral | FloatLiteral;

value: variable | number;

module: (globalDeclaration | functionDefinition)*;

globalDeclaration: Global type globalIdentifier (Comma Align IntegerLiteral)?;

functionDefinition: Define type globalIdentifier functionParameters block;

functionParameters: LeftParen parameterList? RightParen;

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

callInstruction: Call type globalIdentifier functionParameters;

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