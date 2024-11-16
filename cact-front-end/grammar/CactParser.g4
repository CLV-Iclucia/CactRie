parser grammar CactParser;
@header {
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/cact-constant-variable.h>
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/cact-functions.h>
#include <cact-front-end/cact-operator.h>
#include <cact-front-end/cact-type.h>
#include <cact-front-end/symbol-registry.h>
}
options {
tokenVocab=CactLexer;
}

/* declaration & defination */
// compilationUnit can be empty, or a list of declarations and function definitions
// compilation Unit -> many declaration s and function_definition s
compilationUnit: (declaration | functionDefinition)*;

// declaration decalres either a constant or a variable
// declaration -> constant_declaration | variable_declaration
declaration: constantDeclaration | variableDeclaration;

// constantDeclaration declares a constant
// constant_declaration -> const basic_type constant_definition (, constant_definition)* ;
constantDeclaration: Const dataType constantDefinition (Comma constantDefinition)* Semicolon;

// dataType is either Int32, Bool, Float, or Double
// basic_type -> Int32 | Bool | Float | Double
dataType: Int32 | Bool | Float | Double;

// constantDefinition can be either a single constant or a constant array
// (LeftBracket IntegerConstant RightBracket)* is for possible array definition
// constant_definition -> Identifier ([IntegerConstant])* = constant_initial_value
constantDefinition
    locals[
        CactBasicType need_type,
        CactConstant constant,
        std::vector<std::variant<int32_t, float, double, bool>> value,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* Equal constantInitialValue;

// initial value of a constant can be a constant expression or a list of constant values
// constant_initial_value -> constant_expression | { constant_initial_value (, constant_initial_value)* }
constantInitialValue
    locals[
        uint32_t current_dim,
        CactType type,
        bool flat_flag,
        std::vector<std::variant<int32_t, float, double, bool>> value,
    ]: constantExpression | LeftBrace (constantInitialValue (Comma constantInitialValue)*)? RightBrace;

// variable_declaration -> basic_type variable_definition (, variable_definition)* ;
variableDeclaration
    locals[
        CactBasicType need_type,
        std::vector<std::variant<int32_t, float, double, bool>> value,
    ]: dataType variableDefinition (Comma variableDefinition)* Semicolon;

// variable_definition -> Identifier ([IntegerConstant])* ( = constant_initial_value )?
variableDefinition
    locals[
        // observer_ptr<Scope> scope,
        CactBasicType need_type,
        CactVariable variable,
        std::vector<std::variant<int32_t, float, double, bool>> value,
    ]: Identifier (LeftBracket IntegerConstant RightBracket)* (Equal constantInitialValue)?;

// functionDefinition contains the function signature and the function body
// function_definition -> function_type Identifier ( (function_formal_params)? ) block
functionDefinition
    locals[
        observer_ptr<Scope> scope,
        observer_ptr<CactFunction> function,
    ]: functionType Identifier LeftParenthesis (functionParameters)? RightParenthesis block;

// function_type -> Void | Int32 | Float | Double | Bool
functionType: Void | Int32 | Float | Double | Bool;

// functionParameters is a list of functionParameter
// function_formal_params -> function_formal_param (, function_formal_param)*
functionParameters: functionParameter (Comma functionParameter)*;

// function_formal_param -> basic_type Identifier ([IntegerConstant]?)* ( [IntegerConstant] )*
functionParameter: dataType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant RightBracket)*)?;

/* statement & expression */
// a block is a list of declarations and statements enclosed by braces
// block -> { (blockItem)* }
block
    locals[
        observer_ptr<Scope> scope,
        bool has_return,
        bool in_func_def,
    ]: LeftBrace (blockItem)* RightBrace;

// blockItem -> declaration | statement
blockItem
    locals[
        bool has_return,
    ]: declaration | statement;

// replace the right hand side of the statement rule with different rules
statement
    locals[
        bool has_return,
    ]: assignStatement | expressionStatement | block | returnStatement | ifStatement | whileStatement | breakStatement | continueStatement;

// assign_statement -> left_value = expression ;
assignStatement: leftValue Equal expression Semicolon;

// expression_statement -> expression ;
expressionStatement: (expression)? Semicolon;

// return_statement -> return expression? ;
returnStatement
    locals[
        observer_ptr<CactFunction> ret_function,
    ]: Return expression? Semicolon;

// if_statement -> if ( condition ) statement (else statement)?
ifStatement
    locals[
        bool has_return,
    ]: If LeftParenthesis condition RightParenthesis statement (Else statement)?;

// while_statement -> while ( condition ) statement
whileStatement: While LeftParenthesis condition RightParenthesis statement;

// break_statement -> break ;
breakStatement
    locals[
        observer_ptr<WhileStatementContext> loop_to_break,
    ]: Break Semicolon;

// continue_statement -> continue ;
continueStatement
    locals[
        observer_ptr<WhileStatementContext> loop_to_continue,
    ]: Continue Semicolon;

// addExpression has the lowest precedence, so it's on the top of the parse tree above any other operators
// expression -> logical_or_expression
expression
    locals[
        CactType type,
    ]: addExpression | BooleanConstant;

// constantExpression is an expression that can be evaluated at compile time
// constant_expression -> number | BooleanConstant
constantExpression
    locals[
        CactBasicType basic_type,
    ]: number | BooleanConstant;

// condition is an expression that evaluates to a boolean value
// logicalOrExpression has the lowest precedence
// condition -> logical_or_expression
condition
    locals[
        std::optional<bool> compile_time_result,
    ]: logicalOrExpression;

// leftValue is the value that can be put on the left hand side of an assignment
// so they have an address in the memory
// it can either be a variable or an array element
// left_value -> Identifier ([expression])*
leftValue
    locals[
        CactType type,
        bool modifiable_left_value,
        observer_ptr<Scope> scope,
    ]: Identifier (LeftBracket expression RightBracket)*;

// primaryExpression is the most basic expression
// is either enclosed by parentheses, or a leftValue, or a number
// since it has the highest precedence, it should be deeper in the parse tree
// primary_expression -> ( Identifier ) | left_value | number
primaryExpression
    locals[
        CactType type,
        ExpressionResult expression_result,
        // observer_ptr<Scope> scope,
    ]: LeftParenthesis expression RightParenthesis | leftValue | number;

// number -> IntegerConstant | FloatConstant | DoubleConstant
number
    locals[
        CactBasicType basic_type,
    ]: IntegerConstant | FloatConstant | DoubleConstant;

// unaryExpression is an expression with unary operators
// or it can be a function call
// it has the second highest precedence, so it can derive primaryExpression
// unary_expression -> primary_expression | (+ | - | !) unary_expression | Identifier ( (function_real_params)? )
unaryExpression
    locals[
        CactType type,
        ExpressionResult expression_result,
        observer_ptr<UnaryOperator> unary_operator,
    ]: primaryExpression | (Plus | Minus | ExclamationMark) unaryExpression
                | Identifier LeftParenthesis (functionArguments)? RightParenthesis;

// function_real_params -> expression (, expression)*
functionArguments
    locals[
        FuncParameters need_params,
    ]: expression (Comma expression)*;

// mulExpression is an expression with multiplication, division, or modulo operators
// if there isn't any operator, mulExpression is viewed as a unaryExpression
// mul_expression -> unary_expression | mul_expression (* | / | %) unary_expression
mulExpression
    locals[
        CactType type,
        ExpressionResult expression_result,
        observer_ptr<BinaryOperator> binary_operator,
    ]: unaryExpression | mulExpression (Asterisk | Slash | Percent) unaryExpression;

// addExpression is an expression with addition or subtraction operators
// if there isn't any operator, addExpression is viewed as a mulExpression
// add_expression -> mul_expression | add_expression (+ | -) mul_expression
addExpression
    locals[
        CactType type,
        ExpressionResult expression_result,
        observer_ptr<BinaryOperator> binary_operator,
    ]: mulExpression | addExpression (Plus | Minus) mulExpression;

// relational_expression -> add_expression | relational_expression (< | <= | > | >=) add_expression
relationalExpression
    locals[
        CactBasicType basic_type,
        ExpressionResult expression_result,
        observer_ptr<BinaryOperator> binary_operator,
    ]: BooleanConstant | addExpression | addExpression (Less | LessEqual | Greater | GreaterEqual) addExpression;

// logical_equal_expression -> relational_expression | logical_equal_expression (== | !=) relational_expression
logicalEqualExpression
    locals[
        ExpressionResult expression_result,
        observer_ptr<BinaryOperator> binary_operator,
    ]: relationalExpression | relationalExpression (LogicalEqual | NotEqual) relationalExpression;

// logical_and_expression -> logical_equal_expression | logical_and_expression && logical_equal_expression
logicalAndExpression
    locals[
        ExpressionResult expression_result,
        observer_ptr<BinaryOperator> binary_operator,
    ]: logicalEqualExpression | logicalAndExpression LogicalAnd logicalEqualExpression;

// logical_or_expression -> Boolean_constant | logical_and_expression | logical_or_expression || logical_and_expression
logicalOrExpression
    locals[
        ExpressionResult expression_result,
        observer_ptr<BinaryOperator> binary_operator,
    ]: logicalAndExpression | logicalOrExpression LogicalOr logicalAndExpression;
