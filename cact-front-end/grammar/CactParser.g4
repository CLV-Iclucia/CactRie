parser grammar CactParser;
@header {
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/symbol-registry.h>
}
options {
tokenVocab=CactLexer;
}

compilationUnit: (declaration | functionDefinition)*;
declaration
    locals[
        observer_ptr<Scope> scope,
    ]: constantDeclaration | variableDeclaration;
constantDeclaration
    locals[
        observer_ptr<Scope> scope,
    ]: Const basicType constantDefinition (Comma constantDefinition)* Semicolon;
basicType: Int32 | Bool | Float | Double;
constantDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;
constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;
variableDeclaration
    locals[
        observer_ptr<Scope> scope,
    ]: basicType variableDefinition (Comma variableDefinition)* Semicolon;
variableDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;
functionDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: functionType Identifier LeftParenthesis (functionFormalParams)? RightParenthesis block;
functionType: Void | Int32 | Float | Double | Bool;
functionFormalParams: functionFormalParam (Comma functionFormalParam)*;
functionFormalParam
    locals[
        observer_ptr<Scope> scope,
    ]: basicType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;
block
    locals[
        observer_ptr<Scope> scope,
    ]: LeftBrace (blockItem)* RightBrace;
blockItem: declaration | statement;

// replace the right hand side of the statement rule with different rules
statement
    locals[
        std::optional<bool> reachable,
    ]: assignStatement | expressionStatement | block | returnStatement | ifStatement | whileStatement | breakStatement | continueStatement;
assignStatement
    locals[
        observer_ptr<Scope> scope,
    ]: leftValue Equal expression Semicolon;
expressionStatement: (expression)? Semicolon;
returnStatement: Return expression? Semicolon;
ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?;
whileStatement: While LeftParenthesis condition RightParenthesis statement;
breakStatement: Break Semicolon;
continueStatement: Continue Semicolon;

expression: addExpression | BooleanConstant;
constantExpression: number | BooleanConstant;
condition
    locals [
        std::optional<bool> compileTimeResult,
    ]: logicalOrExpression;
leftValue
    locals [
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket expression RightBracket)*;
primaryExpression
    locals [
        ExpressionResult expressionResult,
        observer_ptr<Scope> scope,
    ]: LeftParenthesis expression RightParenthesis | leftValue | number;
number: IntegerConstant | FloatConstant | DoubleConstant;
unaryExpression
    locals [
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (functionRealParams)? RightParenthesis;
functionRealParams: expression (Comma expression)*;
mulExpression
    locals [
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;
addExpression
    locals [
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: mulExpression | addExpression (Plus | Minus) mulExpression;
relationalExpression
    locals[
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: addExpression | relationalExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;
logicalEqualExpression
    locals[
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: relationalExpression | logicalEqualExpression (LogicalEqual | NotEqual) relationalExpression;
logicalAndExpression
    locals[
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;
logicalOrExpression
    locals[
        ExpressionResult expressionResult,
        int tmpResultID,
    ]: BooleanConstant | logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;


