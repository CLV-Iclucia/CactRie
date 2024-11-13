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
  - **simply get `value` from `constantExpression`:**
    - if **`currentDim == dim.size()`**,
    - check whether the type of `constantExpression` matches `needType`,
  - **complex case: check initial value for array constant:**
    - `constantInitialValue.(dim,currentDim,needType) = (dim,currentDim+1,needType)`,
    - consider 3 cases of the number of `constantInitialValue` in the brace:
      - it is ***exactly*** `dim[currentDim]` and **`currentDim < dim.size()-1`**,
      - it is ***no more than*** `dim[currentDim]` and **`currentDim == dim.size()-1`**,
      - it is ***no more than*** `\Pi_i dim[i]` and **`currentDim==0`**,
        - now the initial value is a flattened array,
        - **modify** attributes for children, `constantInitialValue.currentDim = dim.size()`,
    - (use zero to fulfill the rest of the array in the future)
    - visit all the children,
    - record `value` from `constantInitialValue`s,
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
  - check whether this left value is valid to be assigned,
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


