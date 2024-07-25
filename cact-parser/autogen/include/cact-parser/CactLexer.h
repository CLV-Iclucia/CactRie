
// Generated from ./grammar/CactLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"


namespace cactparser {


class  CactLexer : public antlr4::Lexer {
public:
  enum {
    Int = 1, Float = 2, Double = 3, Bool = 4, Void = 5, Const = 6, True = 7, 
    False = 8, Return = 9, If = 10, Else = 11, While = 12, Break = 13, Continue = 14, 
    Equal = 15, LogicalEqual = 16, LogicalAnd = 17, LogicalOr = 18, NotEqual = 19, 
    Less = 20, LessEqual = 21, Greater = 22, GreaterEqual = 23, Period = 24, 
    Comma = 25, Semicolon = 26, Colon = 27, LeftParenthesis = 28, RightParenthesis = 29, 
    LeftBracket = 30, RightBracket = 31, LeftBrace = 32, RightBrace = 33, 
    Plus = 34, Minus = 35, Pipe = 36, ExclamationMark = 37, Asterisk = 38, 
    Slash = 39, Percent = 40, Identifier = 41, DecimalConstant = 42, OctalConstant = 43, 
    HexadecimalConstant = 44, IntegerConstant = 45, FloatConstant = 46, 
    DoubleConstant = 47, BooleanConstant = 48, LineComment = 49, BlockComment = 50, 
    NewLine = 51, WhiteSpaces = 52
  };

  explicit CactLexer(antlr4::CharStream *input);

  ~CactLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace cactparser
