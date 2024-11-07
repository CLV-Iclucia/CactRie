parser grammar CactParser;
@header {
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/symbol-registry.h>
}
options {
tokenVocab=CactLexer;
}

/* declaration & defination */
// compilation Unit -> many declaration s and function_definition s
compilationUnit: (declaration | functionDefinition)*;

// declaration -> constant_declaration | variable_declaration
declaration
    locals[
        observer_ptr<Scope> scope,
    ]: constantDeclaration | variableDeclaration;

// constant_declaration -> const basic_type constant_definition (, constant_definition)* ;
constantDeclaration
    locals[
        observer_ptr<Scope> scope,
    ]: Const basicType constantDefinition (Comma constantDefinition)* Semicolon;

// basic_type -> Int32 | Bool | Float | Double
basicType: Int32 | Bool | Float | Double;

// constant_definition -> Identifier ([IntegerConstant])* = constant_initial_value
constantDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;

// constant_initial_value -> constant_expression | { constant_initial_value (, constant_initial_value)* }
constantInitialValue: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;

// variable_declaration -> basic_type variable_definition (, variable_definition)* ;
variableDeclaration
    locals[
        observer_ptr<Scope> scope,
    ]: basicType variableDefinition (Comma variableDefinition)* Semicolon;

// variable_definition -> Identifier ([IntegerConstant])* ( = constant_initial_value )?
variableDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;

// function_definition -> function_type Identifier ( (function_formal_params)? ) block
functionDefinition
    locals[
        observer_ptr<Scope> scope,
    ]: functionType Identifier LeftParenthesis (functionFormalParams)? RightParenthesis block;

// function_type -> Void | Int32 | Float | Double | Bool
functionType: Void | Int32 | Float | Double | Bool;

// function_formal_params -> function_formal_param (, function_formal_param)*
functionFormalParams: functionFormalParam (Comma functionFormalParam)*;

// function_formal_param -> basic_type Identifier ([IntegerConstant]?)* ( [IntegerConstant] )*
functionFormalParam
    locals[
        observer_ptr<Scope> scope,
    ]: basicType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;

/* statement & expression */
// block -> { (blockItem)* }
block
    locals[
        observer_ptr<Scope> scope,
    ]: LeftBrace (blockItem)* RightBrace;

// blockItem -> declaration | statement
blockItem: declaration | statement;

// replace the right hand side of the statement rule with different rules
statement
    locals[
        std::optional<bool> reachable,
    ]: assignStatement | expressionStatement | block | returnStatement | ifStatement | whileStatement | breakStatement | continueStatement;

// assign_statement -> left_value = expression ;
assignStatement
    locals[
        observer_ptr<Scope> scope,
    ]: leftValue Equal expression Semicolon;

// expression_statement -> expression ;
expressionStatement: (expression)? Semicolon;

// return_statement -> return expression? ;
returnStatement: Return expression? Semicolon;

// if_statement -> if ( condition ) statement (else statement)?
ifStatement: If LeftParenthesis condition RightParenthesis statement (Else statement)?;

// while_statement -> while ( condition ) statement
whileStatement: While LeftParenthesis condition RightParenthesis statement;

// break_statement -> break ;
breakStatement: Break Semicolon;

// continue_statement -> continue ;
continueStatement: Continue Semicolon;

// expression -> logical_or_expression
expression: addExpression | BooleanConstant;

// constant_expression -> number | BooleanConstant
constantExpression: number | BooleanConstant;

// condition -> logical_or_expression
condition
    locals [
        std::optional<bool> compileTimeResult,
    ]: logicalOrExpression;

// left_value -> Identifier ([expression])*
leftValue
    locals [
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket expression RightBracket)*;

// primary_expression -> ( Identifier ) | left_value | number
primaryExpression
    locals [
        ExpressionResult expressionResult,
        observer_ptr<Scope> scope,
    ]: LeftParenthesis expression RightParenthesis | leftValue | number;

// number -> IntegerConstant | FloatConstant | DoubleConstant
number: IntegerConstant | FloatConstant | DoubleConstant;

// unary_expression -> primary_expression | (+ | - | !) unary_expression | Identifier ( (function_real_params)? )
unaryExpression
    locals [
        ExpressionResult expressionResult,
    ]: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (functionRealParams)? RightParenthesis;

// function_real_params -> expression (, expression)*
functionRealParams: expression (Comma expression)*;

// mul_expression -> unary_expression | mul_expression (* | / | %) unary_expression
mulExpression
    locals [
        ExpressionResult expressionResult,
    ]: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;

// add_expression -> mul_expression | add_expression (+ | -) mul_expression
addExpression
    locals [
        ExpressionResult expressionResult,
    ]: mulExpression | addExpression (Plus | Minus) mulExpression;

// relational_expression -> add_expression | relational_expression (< | <= | > | >=) add_expression
relationalExpression
    locals[
        ExpressionResult expressionResult,
    ]: addExpression | relationalExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;

// logical_equal_expression -> relational_expression | logical_equal_expression (== | !=) relational_expression
logicalEqualExpression
    locals[
        ExpressionResult expressionResult,
    ]: relationalExpression | logicalEqualExpression (LogicalEqual | NotEqual) relationalExpression;

// logical_and_expression -> logical_equal_expression | logical_and_expression && logical_equal_expression
logicalAndExpression
    locals[
        ExpressionResult expressionResult,
    ]: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;

// logical_or_expression -> Boolean_constant | logical_and_expression | logical_or_expression || logical_and_expression
logicalOrExpression
    locals[
        ExpressionResult expressionResult,
    ]: BooleanConstant | logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;


