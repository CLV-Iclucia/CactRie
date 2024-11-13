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
cact-rie/cact-rie <input-file>
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


#0  cactfrontend::SymbolRegistrationErrorCheckVisitor::visitAddExpression (this=0x7fffffffd650, ctx=0x555555796e60)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:712
#3  0x000055555557b40d in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitRelationalExpression (this=0x7fffffffd650, ctx=0x555555786df0)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:757
#6  0x000055555557b8f3 in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitLogicalEqualExpression (this=0x7fffffffd650, ctx=0x55555578ce00)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:787
#9  0x000055555557be57 in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitLogicalAndExpression (this=0x7fffffffd650, ctx=0x55555578cd50)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:822
#12 0x000055555557c137 in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitLogicalOrExpression (this=0x7fffffffd650, ctx=0x55555578cca0)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:847
#15 0x0000555555575460 in cactfrontend::CactParserBaseVisitor::visitCondition (this=0x7fffffffd650, ctx=0x555555782510)
    at /home/junxiong/cplab/CactRie/cact-front-end/autogen/include/cact-front-end/CactParserBaseVisitor.h:123
#18 0x0000555555578bda in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitWhileStatement (this=0x7fffffffd650, ctx=0x555555786110)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:445
#21 0x000055555557848d in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitStatement (this=0x7fffffffd650, ctx=0x555555789bc0)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:363
#24 0x00005555555783b0 in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitBlockItem (this=0x7fffffffd650, ctx=0x555555789b60)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:352
#27 0x000055555557820d in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitBlock (this=0x7fffffffd650, ctx=0x555555783b80)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:332
#30 0x0000555555577673 in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitFunctionDefinition (this=0x7fffffffd650, ctx=0x555555783450)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:249
#33 0x0000555555575c6a in cactfrontend::SymbolRegistrationErrorCheckVisitor::visitCompilationUnit (this=0x7fffffffd650, ctx=0x55555577dbe0)
    at /home/junxiong/cplab/CactRie/cact-front-end/include/cact-front-end/symbol-registration-visitor.h:37
#34 0x00005555555995a2 in cactfrontend::CactParser::CompilationUnitContext::accept (this=0x55555577dbe0, visitor=0x7fffffffd650)
--Type <RET> for more, q to quit, c to continue without paging--
    at /home/junxiong/cplab/CactRie/cact-front-end/autogen/src/CactParser.cpp:284
#35 0x000055555556fdf2 in antlr4::tree::AbstractParseTreeVisitor::visit (this=0x7fffffffd650, tree=0x55555577dbe0)
    at /home/junxiong/cplab/CactRie/deps/antlr-runtime/antlr-runtime/tree/AbstractParseTreeVisitor.h:19
#36 0x000055555556f0b8 in main (argc=2, argv=0x7fffffffded8) at /home/junxiong/cplab/CactRie/cact-rie/apps/cact-rie.cc:44