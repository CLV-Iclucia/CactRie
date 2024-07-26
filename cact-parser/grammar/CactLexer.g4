lexer grammar CactLexer;

Int: 'int' ;
Float: 'float' ;
Double: 'double' ;
Bool: 'bool' ;
Void: 'void' ;
Const: 'const' ;
Return : 'return';
If : 'if';
Else : 'else';
While : 'while';
Break : 'break';
Continue : 'continue';
Equal: '=' ;
LogicalEqual: '==' ;
LogicalAnd: '&&' ;
LogicalOr: '||' ;
NotEqual: '!=' ;
Less: '<' ;
LessEqual: '<=' ;
Greater: '>' ;
GreaterEqual: '>=' ;
Period : '.' ;
Comma : ',' ;
Semicolon : ';' ;
Colon : ':' ;
LeftParenthesis : '(' ;
RightParenthesis : ')' ;
LeftBracket : '[' ;
RightBracket : ']' ;
LeftBrace : '{' ;
RightBrace : '}' ;
Plus: '+';
Minus: '-';
Pipe: '|';
ExclamationMark: '!';
Asterisk: '*';
Slash: '/';
Percent: '%';
Identifier: [a-zA-Z_][a-zA-Z0-9_]* ;
IntegerConstant: '0' | [1-9][0-9]* | '0'[0-7]+ | '0'[xX][0-9a-fA-F]+;
FloatConstant: '.'[0-9]+[fF]
              | [0-9]+'.'[fF]
              | [0-9]+'.'[0-9]+[fF];
DoubleConstant: '.'[0-9]+
              | [0-9]+'.'
              | [0-9]+'.'[0-9]+;
BooleanConstant: 'true'
             | 'false';

LineComment: '//' ~[\r\n]* -> skip;
BlockComment: '/*' .*? '*/' -> skip;
NewLine: ('\r' ('\n')? | '\n') -> skip;
WhiteSpaces : (' ' | '\t')+ -> skip;