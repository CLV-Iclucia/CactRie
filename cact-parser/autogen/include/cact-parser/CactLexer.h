
// Generated from ./grammar/CactLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"


namespace cactparser {


class  CactLexer : public antlr4::Lexer {
public:
  enum {
    Int = 1, Float = 2, Double = 3, Bool = 4, Void = 5, Const = 6, Return = 7, 
    If = 8, Else = 9, While = 10, Break = 11, Continue = 12, Equal = 13, 
    LogicalEqual = 14, LogicalAnd = 15, LogicalOr = 16, NotEqual = 17, Less = 18, 
    LessEqual = 19, Greater = 20, GreaterEqual = 21, Period = 22, Comma = 23, 
    Semicolon = 24, Colon = 25, LeftParenthesis = 26, RightParenthesis = 27, 
    LeftBracket = 28, RightBracket = 29, LeftBrace = 30, RightBrace = 31, 
    Plus = 32, Minus = 33, Pipe = 34, ExclamationMark = 35, Asterisk = 36, 
    Slash = 37, Percent = 38, Identifier = 39, IntegerConstant = 40, FloatConstant = 41, 
    DoubleConstant = 42, BooleanConstant = 43, LineComment = 44, BlockComment = 45, 
    NewLine = 46, WhiteSpaces = 47
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
