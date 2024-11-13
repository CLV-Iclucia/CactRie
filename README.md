# Cact-Rie: A Tsundere Cact Compiler for UCAS Compiler Lab!

## Introduction

Cact-Rie is a compiler for Cact, a simple C-like language designed for UCAS Compiler Lab. It is written in C++ and uses chiisai-LLVM as its backend.

## Build

```bash
mkdir build
cd build
cmake ..
# compiler the whole project
make
# compile the first stage
make cact-rie
```

## Dependencies

- cmake >= 3.29
- g++ high-enough
- ...

## Structure

### Frontend

- `cact-front-end/grammar/CactLexer.g4`: Lexer
- `cact-front-end/grammar/CactParser.g4`: Syntax Parser
- `cact-front-end/include/*`: Header files
- `cact-front-end/src/*`: Source files
- `cact-rie/apps/cact-rie.cc`: Main function
- `cact-rie/tests/*`: Test files

- `cact-front-end/include/cact-expr.h`: Expression-related attributes and functions
- `cact-front-end/include/cact-function.h`: Function-related attributes for semantic analysis
- `cact-front-end/include/cact-operator.h`: Operator definitions for semantic analysis
- `cact-front-end/include/cact-syntax-error-listener.h`: Syntax error listener, used in **syntax analysis**
- `cact-front-end/include/cact-type.h`: Type definitions for semantic analysis
- `cact-front-end/include/cact-variable.h`: Variable-related attributes for semantic analysis
- `cact-front-end/include/ir-generation.h`: IR generation (a pass)
- `cact-front-end/include/symbol-registration-visitor.h`: Symbol registration visitor (a pass)
- `cact-front-end/include/symbol-registry.h`: Symbol registry class for semantic analysis
- `cact-front-end/include/type-check-and-const-eval.h`: Type check and constant evaluation (a pass)

#### Syntax Analysis

```
/* declaration & defination */
compilationUnit: (declaration | functionDefinition)*;
declaration: constantDeclaration | variableDeclaration;
constantDeclaration: Const dataType constantDefinition (Comma constantDefinition)* Semicolon;
dataType: Int32 | Bool | Float | Double;
constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;
variableDeclaration: dataType variableDefinition (Comma variableDefinition)* Semicolon;
variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;
functionDefinition: functionType Identifier LeftParenthesis (FunctionParams)? RightParenthesis block;
functionType: Void | Int32 | Float | Double | Bool;
FunctionParams: FunctionParam (Comma FunctionParam)*;
FunctionParam: dataType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;

/* statement & expression */
block: LeftBrace (blockItem)* RightBrace;
blockItem: declaration | statement;
statement: assignStatement | expressionStatement | block | returnStatement | ifStatement | whileStatement | breakStatement | continueStatement;
assignStatement: leftValue Equal expression Semicolon;
expressionStatement: (expression)? Semicolon;
returnStatement: Return expression? Semicolon;
ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?;
whileStatement: While LeftParenthesis condition RightParenthesis statement;
breakStatement: Break Semicolon;
continueStatement: Continue Semicolon;
expression: addExpression | BooleanConstant;
constantExpression: number | BooleanConstant;
condition: logicalOrExpression;
leftValue: Identifier (LeftBracket expression RightBracket)*;
primaryExpression: LeftParenthesis expression RightParenthesis | leftValue | number;
number: IntegerConstant | FloatConstant | DoubleConstant;
unaryExpression: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (FunctionArgs)? RightParenthesis;
FunctionArgs: expression (Comma expression)*;
mulExpression: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;
addExpression: mulExpression | addExpression (Plus | Minus) mulExpression;
relationalExpression: addExpression | relationalExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;
logicalEqualExpression: relationalExpression | logicalEqualExpression (LogicalEqual | NotEqual) relationalExpression;
logicalAndExpression: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;
logicalOrExpression: BooleanConstant | logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;
```

/* declaration & defination */
compilationUnit
declaration
constantDeclaration
dataType
constantDefinition
constantInitialValue
variableDeclaration
variableDefinition
functionDefinition
functionType
FunctionParams
FunctionParam

/* statement & expression */
block
blockItem
statement
assignStatement
expressionStatement
returnStatement
ifStatement
whileStatement
breakStatement
continueStatement
expression
constantExpression
condition
leftValue
primaryExpression
number
unaryExpression
FunctionArgs
mulExpression
addExpression
relationalExpression
logicalEqualExpression
logicalAndExpression
logicalOrExpression
