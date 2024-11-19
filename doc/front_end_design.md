# Design Documetation

## Lexical Analysis

The lexical analysis is implemented in `cact-front-end/grammar/CactLexer.g4`, by defining the tokens and their regular expressions using ANTLR.

## Syntax Analysis

The syntax-analysis grammar is written as defined in Cact specification in `cact-front-end/grammar/CactParser.g4`, briefly summarized as follows:

```antlr
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

## Semantic Analysis

### Phase 1: Variable Registration

When a variable is declared, it should be registered in the symbol table. The symbol table is a tree of scopes, where each scope is a map from variable names to variable information, including its type: constant or variable, array or scalar, and its basic type. The symbol table is implemented in `cact-front-end/include/symbol-registry.h`.

During the 1st pass of the semantic analysis, the symbol table is built. Different scopes are created for different grammar rules, such as function definition, block, and loop. When a variable is declared, it is registered in the current scope. When a variable is used, it is looked up in the symbol table. If it is not found, an error is reported.

Now we list some grammar variables related to the symbol table.

#### Declaration & Defination

- `compilationUnit: (declaration | functionDefinition)*`:
  - a global scope
- `declaration: constantDeclaration | variableDeclaration`: *nothing to do*
- `constantDeclaration: Const dataType constantDefinition (Comma constantDefinition)* Semicolon`:
  <!-- - `type=dataType.type`, -->
  - `constantDefinition.type = visit(dataType)`,
  - visit `constantDefinition`,
  <!-- - register variables by `regVar(type, name, dim, initialized=true, value)`, -->
- `dataType: Int32 | Bool | Float | Double`:
  - return `type` for the variable,
- `constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue`:
  - record `name`, `dim` (a vector),
  - `constantInitialValue.(dim,currentDim,type) = (dim,0,type)`,
  <!-- - `value = constantInitialValue.value`, -->
  - register variables by `regVar(type, name, dim, initialized=true)`,
- `constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace`:
  - **simply get `pointee` from `constantExpression`:**
    - if **`currentDim == dim.size()`**,
    - check whether the type of `constantExpression` matches `needType`,
  - **complex case: check initial pointee for array constant:**
    - `constantInitialValue.(dim,currentDim,needType) = (dim,currentDim+1,needType)`,
    - consider 3 cases of the number of `constantInitialValue` in the brace:
      - it is ***no more than*** `dim[currentDim]`,
      - it is ***no more than*** `\Pi_i dim[i]` and **`currentDim==0`**,
        - now the initial pointee is a flattened array,
        - **modify** attributes for children, `constantInitialValue.currentDim = dim.size()`,
    - (use zero to fulfill the rest of the array in the future)
    - visit all the children,
    - record `pointee` from `constantInitialValue`s,
- `variableDeclaration: dataType variableDefinition (Comma variableDefinition)* Semicolon`:
  <!-- - `type=dataType.type`, -->
  - `variableDefinition.type = visit(dataType)`,
  - visit `variableDefinition`,
  <!-- - register variables by `regVar(type, name, dim, initialized, value)`, -->
- `variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?`
  - record `name`, `dim` (a vector), `initialized`,
  - if `constantInitialValue` exists (`initialized==true`):
    - `constantInitialValue.(dim,currentDim,needType) = (dim,0,needType)`,
    <!-- - `value = constantInitialValue.value`, -->
  - register variables by `regVar(type, name, dim, initialized=true)`,
- `functionDefinition: functionType Identifier LeftParenthesis (FunctionParams)? RightParenthesis block`
  - **create a new scope**,
  - record `retType`, `name`,
  - if `FunctionParams` exists:
    - visit it and get `params=FunctionParams.params` (a vector),
  - if not:
    - `params=Vec()`,
  - **register** all formal parameters,
  - **create function** by `createFunc(retType, name, params)`,
  - `block.scope.parent = scope`,
- `functionType: Void | Int32 | Float | Double | Bool`:
  - record `retType` for the variable,
- `FunctionParams: FunctionParam (Comma FunctionParam)*`:
  - push back all `FunctionParam.param` into `params`,
- `FunctionParam: dataType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?`
  - record `name` and `type`,
  - set `dim = Vec(IntegerConstant)`s, and set `dim[0]=0` if not specified (only `dim[0]` is allowed to be zero), 
  - set `param=(type, name, dim)`,

#### Statement & Expression

- `block: LeftBrace (blockItem)* RightBrace`:
  - create a new `scope`,
- `blockItem: declaration | statement`: *nothing to do*
- `statement: assignStatement | expressionStatement | block | returnStatement | ifStatement | whileStatement | breakStatement | continueStatement`:
  - `block.scope.parent = scope`,
  - check the legality of different statements here, e.g. `break/continueStatement` can only appear in a loop,
    - it is relatively complex to check, because the loop might not be the direct parent of the statement,
- `assignStatement: leftValue Equal expression Semicolon`:
  - check whether the type of `expression` matches `leftValue`,
- `expressionStatement: (expression)? Semicolon`: *nothing to do*
- `returnStatement: Return expression? Semicolon`:
  - check whether the type of `expression` matches the return type of the function,
- `ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?`: *nothing to do*
- `whileStatement: While LeftParenthesis condition RightParenthesis statement`: *nothing to do*
- `breakStatement: Break Semicolon`: *nothing to do*
- `continueStatement: Continue Semicolon`: *nothing to do*
- `expression: addExpression | BooleanConstant`:
  - record the `type`,
- `constantExpression: number | BooleanConstant`:
  - record the `type`,
- `condition: logicalOrExpression`:
  - check whether `condition` is valid,
- `leftValue: Identifier (LeftBracket expression RightBracket)*`:
  - record the `type` from `Identifier`,
  - check whether brackets match the dimension of the variable (no overflow is guaranteed by programmer),
  - check whether this left pointee is valid to be assigned,
- `primaryExpression: LeftParenthesis expression RightParenthesis | leftValue | number`:
  - the `type` is the same as the `expression` or `leftValue` or `number`,
- `number: IntegerConstant | FloatConstant | DoubleConstant`:
  - record the `type`,
- `unaryExpression: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression | Identifier LeftParenthesis (FunctionArgs)? RightParenthesis`:
  - record the `type`,
- `FunctionArgs: expression (Comma expression)*`:
  - record the `type`,
- `mulExpression: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression`:
  - record the `type`,
- `addExpression: mulExpression | addExpression (Plus | Minus) mulExpression`:
  - record the `type`,
- `relationalExpression: addExpression | relationalExpression (Less | LessEqual | Greater | GreaterEqual) addExpression`:
  - record the `type`,
- `logicalEqualExpression: relationalExpression | logicalEqualExpression (LogicalEqual | NotEqual) relationalExpression`:
  - record the `type`,
- `logicalAndExpression: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression`:
  - record the `type`,
- `logicalOrExpression: BooleanConstant | logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression`:
  - record the `type`.

### Phase 2: Constant Evaluation and Expression Tree Construction

During the 2nd pass of the semantic analysis, the constant expressions are evaluated and the expression tree is constructed. The expression tree is a tree of expression nodes, where each node represents an operation or a value. The expression tree is implemented in `cact-front-end/include/const-eval-and-expression-generation.h`.

The design is like generating new trees from the original tree for each expressions.

```g4
// declaration & defination
compilationUnit: (declaration | functionDefinition)*; // visit "declaration" or "functionDefinition"
declaration: constantDeclaration | variableDeclaration; // visit "constantDeclaration" or "variableDeclaration"
constantDeclaration: Const dataType constantDefinition (Comma constantDefinition)* Semicolon; // visit "constantDefinition"s
dataType:  // {NO NEED}
constantDefinition // [NEW] {observer_ptr<CactConstVar> constant}
constantInitialValue // {NO NEED}
variableDeclaration: dataType variableDefinition (Comma variableDefinition)* Semicolon; // visit "variableDefinition"s
variableDefinition // [NEW] {observer_ptr<CactConstVar> variable}
functionDefinition: functionType Identifier LeftParenthesis (functionParameters)? RightParenthesis block; // visit "block" [NEW] {observer_ptr<CactFunction> function}
functionType // {NO NEED}
functionParameters: functionParameter (Comma functionParameter)*; // visit "functionParameter"s
functionParameter // [NEW] {observer_ptr<CactConstVar> parameter}

// statement & expression
block: LeftBrace (blockItem)* RightBrace; // visit "blockItem"s
blockItem: declaration | statement; // visit "declaration" or "statement"
statement: assignStatement | expressionStatement | block | returnStatement | ifStatement
         | whileStatement | breakStatement | continueStatement; // visit any statement
assignStatement // [NEW] {CactExpr lvalue, expr}
expressionStatement // {DO NOTHING}
returnStatement // [NEW] {CactExpr expr}  IMPORTANT: "MIGHT BE nullptr"
ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?; // visit "statement"s. [NEW] {CactExpr cond_expr}
whileStatement: While LeftParenthesis condition RightParenthesis statement; // visit "statement". [NEW] {CactExpr cond_expr}
breakStatement // [NEW] {observer_ptr<WhileStatementContext> to_which_loop}
continueStatement // [NEW] {observer_ptr<WhileStatementContext> to_which_loop}
expression, constantExpression, condition, leftValue, primaryExpression, unaryExpression, functionArguments, mulExpression, addExpression, relationalExpression, logicalEqualExpression, logicalAndExpression, logicalOrExpression // {NO NEED}
```
