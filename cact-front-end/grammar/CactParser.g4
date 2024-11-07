parser grammar CactParser;
@header {
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/symbol-registry.h>
}
options {
tokenVocab=CactLexer;
}

// compilationUnit can be empty, or a list of declarations and function definitions
compilationUnit: (declaration | functionDefinition)*;

// declaration decalres either a constant or a variable
declaration
    locals[
        observer_ptr<Scope> scope,
    ]: constantDeclaration | variableDeclaration;

// constantDeclaration declares a constant
constantDeclaration
    locals[
        observer_ptr<Scope> scope,
    ]: Const basicType constantDefinition (Comma constantDefinition)* Semicolon;

// basicType is either Int32, Bool, Float, or Double
basicType: Int32 | Bool | Float | Double;

// constantDefinition can be either a single constant or a constant array
// (LeftBracket IntegerConstant RightBracket)* is for possible array definition
constantDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;

// initial value of a constant can be a constant expression or a list of constant values
constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;

variableDeclaration
    locals[
        observer_ptr<Scope> scope,
    ]: basicType variableDefinition (Comma variableDefinition)* Semicolon;

variableDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;

// functionDefinition contains the function signature and the function body
functionDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: functionType Identifier LeftParenthesis (functionFormalParams)? RightParenthesis block;
functionType: Void | Int32 | Float | Double | Bool;
// functionFormalParams is a list of functionFormalParam
functionFormalParams: functionFormalParam (Comma functionFormalParam)*;
functionFormalParam
    locals[
        observer_ptr<Scope> scope,
    ]: basicType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;
// a block is a list of declarations and statements enclosed by braces
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

// addExpression has the lowest precedence, so it's on the top of the parse tree above any other operators
expression: addExpression | BooleanConstant;
// constantExpression is an expression that can be evaluated at compile time
constantExpression: number | BooleanConstant;

// condition is an expression that evaluates to a boolean value
// logicalOrExpression has the lowest precedence
condition
    locals [
        std::optional<bool> compileTimeResult,
    ]: logicalOrExpression;

// leftValue is the value that can be put on the left hand side of an assignment
// so they have an address in the memory
// it can either be a variable or an array element
leftValue
    locals [
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket expression RightBracket)*;

// primaryExpression is the most basic expression
// is either enclosed by parentheses, or a leftValue, or a number
// since it has the highest precedence, it should be deeper in the parse tree
primaryExpression
    locals [
        ExpressionResult expressionResult,
        observer_ptr<Scope> scope,
    ]: LeftParenthesis expression RightParenthesis | leftValue | number;
number: IntegerConstant | FloatConstant | DoubleConstant;

// unaryExpression is an expression with unary operators
// or it can be a function call
// it has the second highest precedence, so it can derive primaryExpression
unaryExpression
    locals [
        ExpressionResult expressionResult,
    ]: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (functionRealParams)? RightParenthesis;
functionRealParams: expression (Comma expression)*;

// mulExpression is an expression with multiplication, division, or modulo operators
// if there isn't any operator, mulExpression is viewed as a unaryExpression
mulExpression
    locals [
        ExpressionResult expressionResult,
    ]: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;

// addExpression is an expression with addition or subtraction operators
// if there isn't any operator, addExpression is viewed as a mulExpression
addExpression
    locals [
        ExpressionResult expressionResult,
    ]: mulExpression | addExpression (Plus | Minus) mulExpression;

relationalExpression
    locals[
        ExpressionResult expressionResult,
    ]: addExpression | relationalExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;
logicalEqualExpression
    locals[
        ExpressionResult expressionResult,
    ]: relationalExpression | logicalEqualExpression (LogicalEqual | NotEqual) relationalExpression;
logicalAndExpression
    locals[
        ExpressionResult expressionResult,
    ]: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;
logicalOrExpression
    locals[
        ExpressionResult expressionResult,
    ]: BooleanConstant | logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;


