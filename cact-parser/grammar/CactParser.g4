parser grammar CactParser;
options {
tokenVocab=CactLexer;
}

compilationUnit: (declaration | functionDefinition)*;
declaration: constantDeclaration | variableDeclaration;
constantDeclaration: Const basicType constantDefinition (Comma constantDefinition)* Semicolon;
basicType: Int | Bool | Float | Double;
constantDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;
variableDeclaration: basicType variableDefinition (Comma variableDefinition)* Semicolon;
variableDefinition: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantExpression)?;
functionDefinition: functionType Identifier LeftParenthesis (functionFormalParams)? RightParenthesis block;
functionType: Void | Int | Float | Double | Bool;
functionFormalParams: functionFormalParam (Comma functionFormalParam)*;
functionFormalParam: basicType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;

block: LeftBrace (blockItem)* RightBrace;
blockItem: declaration | statement;
statement: leftValue Equal expression Semicolon
        |  (expression)? Semicolon
        |  block
        | Return expression? Semicolon
        | If LeftParenthesis condition RightParenthesis statement (Else statement)?
        | While LeftParenthesis condition RightParenthesis statement
        | Break Semicolon
        | Continue Semicolon;

expression: addExpression | BooleanConstant;
constantExpression: number | BooleanConstant;
condition: logicalOrExpression;
leftValue: Identifier (LeftBracket expression RightBracket)*;
primaryExpression: LeftParenthesis expression RightParenthesis | leftValue | number;
number: IntegerConstant | FloatConstant | DoubleConstant;
unaryExpression: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (functionRealParams)? RightParenthesis;
functionRealParams: expression (Comma expression)*;
mulExpression: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;
addExpression: mulExpression | addExpression (Plus | Minus) mulExpression;
relationalExpression: addExpression | relationalExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;
logicalEqualExpression: relationalExpression | logicalEqualExpression (LogicalEqual | NotEqual) relationalExpression;
logicalAndExpression: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;
logicalOrExpression: BooleanConstant | logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;


