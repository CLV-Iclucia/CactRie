
// Generated from /home/creeper/CLionProjects/CactRie/chiisai-llvm/grammar/LLVMLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  LLVMLexer : public antlr4::Lexer {
public:
  enum {
    Global = 1, External = 2, Define = 3, Align = 4, Unreachable = 5, Br = 6, 
    Ret = 7, Call = 8, Load = 9, Store = 10, Alloca = 11, Phi = 12, Add = 13, 
    Sub = 14, Mul = 15, Div = 16, And = 17, Or = 18, Xor = 19, Shl = 20, 
    Lshr = 21, Ashr = 22, Icmp = 23, Fcmp = 24, Sext = 25, Zext = 26, Trunc = 27, 
    Label = 28, Void = 29, Ptr = 30, I1 = 31, I32 = 32, I64 = 33, F32 = 34, 
    F64 = 35, Equals = 36, Comma = 37, LeftParen = 38, RightParen = 39, 
    LeftBrace = 40, RightBrace = 41, At = 42, Percent = 43, Asterisk = 44, 
    NumericIdentifier = 45, NamedIdentifier = 46, IntegerLiteral = 47, FloatLiteral = 48, 
    Whitespace = 49, Comment = 50
  };

  explicit LLVMLexer(antlr4::CharStream *input);

  ~LLVMLexer() override;


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

