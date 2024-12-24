lexer grammar LLVMLexer;

// The following is a list of token types:

options {
    language = Cpp;
}

Global: 'global';
ConstantStr: 'constant';
External: 'external';
Define: 'define';
Declare: 'declare';
Align: 'align';
Unreachable: 'unreachable';
Br: 'br';
Ret: 'ret';
Call: 'call';
Load: 'load';
Store: 'store';
Alloca: 'alloca';
GetElementPtr: 'getelementptr';
Phi: 'phi';
Add: 'add';
Sub: 'sub';
Mul: 'mul';
Div: 'div';
And: 'and';
Or: 'or';
Xor: 'xor';
Shl: 'shl';
Lshr: 'lshr';
Ashr: 'ashr';
Icmp: 'icmp';
Fcmp: 'fcmp';
Sext: 'sext';
Zext: 'zext';
Trunc: 'trunc';
Label: 'label';

Void: 'void';
Ptr: 'ptr';
I1: 'i1';
I32: 'i32';
I64: 'i64';
F32: 'f32';
F64: 'f64';
Eq: 'eq';
Ne: 'ne';
Ugt: 'ugt';
Uge: 'uge';
Ult: 'ult';
Ule: 'ule';
Sgt: 'sgt';
Sge: 'sge';
Slt: 'slt';
Sle: 'sle';

Equals: '=';
Comma: ',';
LeftParen: '(';
RightParen: ')';
LeftBrace: '{';
RightBrace: '}';
LeftBracket: '[';
RightBracket: ']';
At: '@';
Percent: '%';
Asterisk: '*';
Colon: ':';
Cross: 'x';
SourceFilename: 'source_filename';

NumericIdentifier: [0-9]+;
NamedIdentifier: [a-zA-Z_.][a-zA-Z0-9_.]*;

// Integer literals
IntegerLiteral: [1-9][0-9]*;

// Hex literals
HexLiteral: '0x'[0-9a-fA-F]+;

// Whitespace and Comments
Whitespace: [ \t\r\n]+ -> skip;
Comment: ';' ~[\r\n]* -> skip;

