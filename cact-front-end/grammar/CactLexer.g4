lexer grammar CactLexer;

// Keywords
BooleanConstant: 'true' | 'false' ;
Const: 'const' ;
Int32: 'int' ;
Bool: 'bool' ;
Float: 'float' ;
Double: 'double' ;
Void: 'void' ;
If : 'if';
Else : 'else';
While : 'while';
Break : 'break';
Continue : 'continue';
Return : 'return';

// Operators by precedence
LeftBracket : '[' ;
RightBracket : ']' ;
LeftParenthesis : '(' ;
RightParenthesis : ')' ;

// Binary Plus and Minus are also used as unary operators
ExclamationMark: '!';

Asterisk: '*';
Slash: '/';
Percent: '%';

Minus: '-';
Plus: '+';

Less: '<' ;
LessEqual: '<=' ;
Greater: '>' ;
GreaterEqual: '>=' ;

LogicalEqual: '==' ;
NotEqual: '!=' ;

LogicalAnd: '&&' ;
LogicalOr: '||' ;

// Other tokens
LeftBrace : '{' ;
RightBrace : '}' ;
Equal: '=' ;
// Period : '.' ;
Comma : ',' ;
Semicolon : ';' ;
// Colon : ':' ;
// Pipe : '|' ;

// Identifier and constants
Identifier: [a-zA-Z_][a-zA-Z0-9_]* ;
IntegerConstant: [+-]?('0' | [1-9][0-9]* | '0'[0-7]+ | '0'[xX][0-9a-fA-F]+);
FloatConstant: [+-]?(       '.'[0-9]+                  |
                     [0-9]+ '.'[0-9]*                  |
                            '.'[0-9]+  [eE][+-]?[0-9]+ |
                     [0-9]+('.'[0-9]*)?[eE][+-]?[0-9]+  )[fF];
DoubleConstant: [+-]?(       '.'[0-9]+                  |
                      [0-9]+ '.'[0-9]*                  |
                             '.'[0-9]+  [eE][+-]?[0-9]+ |
                      [0-9]+('.'[0-9]*)?[eE][+-]?[0-9]+  );

// Comments and white spaces
LineComment: '//' ~[\r\n]* -> skip;
BlockComment: '/*' .*? '*/' -> skip;
NewLine: ('\r' ('\n')? | '\n') -> skip;
WhiteSpaces : (' ' | '\t')+ -> skip;
