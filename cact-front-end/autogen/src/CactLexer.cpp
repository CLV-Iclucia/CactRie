
// Generated from ./grammar/CactLexer.g4 by ANTLR 4.13.1


#include "CactLexer.h"


using namespace antlr4;

using namespace cactfrontend;


using namespace antlr4;

namespace {

struct CactLexerStaticData final {
  CactLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CactLexerStaticData(const CactLexerStaticData&) = delete;
  CactLexerStaticData(CactLexerStaticData&&) = delete;
  CactLexerStaticData& operator=(const CactLexerStaticData&) = delete;
  CactLexerStaticData& operator=(CactLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cactlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CactLexerStaticData *cactlexerLexerStaticData = nullptr;

void cactlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cactlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(cactlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CactLexerStaticData>(
    std::vector<std::string>{
      "Int32", "Float", "Double", "Bool", "Void", "Const", "Return", "If", 
      "Else", "While", "Break", "Continue", "Equal", "LogicalEqual", "LogicalAnd", 
      "LogicalOr", "NotEqual", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "Period", "Comma", "Semicolon", "Colon", "LeftParenthesis", "RightParenthesis", 
      "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "Plus", 
      "Minus", "Pipe", "ExclamationMark", "Asterisk", "Slash", "Percent", 
      "Identifier", "IntegerConstant", "FloatConstant", "DoubleConstant", 
      "BooleanConstant", "LineComment", "BlockComment", "NewLine", "WhiteSpaces"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'int'", "'float'", "'double'", "'bool'", "'void'", "'const'", 
      "'return'", "'if'", "'else'", "'while'", "'break'", "'continue'", 
      "'='", "'=='", "'&&'", "'||'", "'!='", "'<'", "'<='", "'>'", "'>='", 
      "'.'", "','", "';'", "':'", "'('", "')'", "'['", "']'", "'{'", "'}'", 
      "'+'", "'-'", "'|'", "'!'", "'*'", "'/'", "'%'"
    },
    std::vector<std::string>{
      "", "Int32", "Float", "Double", "Bool", "Void", "Const", "Return", 
      "If", "Else", "While", "Break", "Continue", "Equal", "LogicalEqual", 
      "LogicalAnd", "LogicalOr", "NotEqual", "Less", "LessEqual", "Greater", 
      "GreaterEqual", "Period", "Comma", "Semicolon", "Colon", "LeftParenthesis", 
      "RightParenthesis", "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", 
      "Plus", "Minus", "Pipe", "ExclamationMark", "Asterisk", "Slash", "Percent", 
      "Identifier", "IntegerConstant", "FloatConstant", "DoubleConstant", 
      "BooleanConstant", "LineComment", "BlockComment", "NewLine", "WhiteSpaces"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,47,489,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,1,0,1,0,1,0,1,0,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,
  	4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,
  	10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,
  	13,1,13,1,13,1,14,1,14,1,14,1,15,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,
  	18,1,18,1,18,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,
  	24,1,24,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,1,
  	31,1,31,1,32,1,32,1,33,1,33,1,34,1,34,1,35,1,35,1,36,1,36,1,37,1,37,1,
  	38,1,38,5,38,225,8,38,10,38,12,38,228,9,38,1,39,1,39,1,39,5,39,233,8,
  	39,10,39,12,39,236,9,39,1,39,1,39,4,39,240,8,39,11,39,12,39,241,1,39,
  	1,39,1,39,4,39,247,8,39,11,39,12,39,248,3,39,251,8,39,1,40,1,40,4,40,
  	255,8,40,11,40,12,40,256,1,40,1,40,4,40,261,8,40,11,40,12,40,262,1,40,
  	1,40,1,40,4,40,268,8,40,11,40,12,40,269,1,40,1,40,4,40,274,8,40,11,40,
  	12,40,275,1,40,1,40,1,40,4,40,281,8,40,11,40,12,40,282,1,40,1,40,3,40,
  	287,8,40,1,40,4,40,290,8,40,11,40,12,40,291,1,40,1,40,4,40,296,8,40,11,
  	40,12,40,297,1,40,1,40,3,40,302,8,40,1,40,4,40,305,8,40,11,40,12,40,306,
  	1,40,1,40,4,40,311,8,40,11,40,12,40,312,1,40,1,40,1,40,3,40,318,8,40,
  	1,40,4,40,321,8,40,11,40,12,40,322,1,40,1,40,4,40,327,8,40,11,40,12,40,
  	328,1,40,1,40,4,40,333,8,40,11,40,12,40,334,1,40,1,40,3,40,339,8,40,1,
  	40,4,40,342,8,40,11,40,12,40,343,1,40,3,40,347,8,40,1,41,1,41,4,41,351,
  	8,41,11,41,12,41,352,1,41,4,41,356,8,41,11,41,12,41,357,1,41,1,41,4,41,
  	362,8,41,11,41,12,41,363,1,41,1,41,4,41,368,8,41,11,41,12,41,369,1,41,
  	4,41,373,8,41,11,41,12,41,374,1,41,1,41,3,41,379,8,41,1,41,4,41,382,8,
  	41,11,41,12,41,383,1,41,1,41,4,41,388,8,41,11,41,12,41,389,1,41,1,41,
  	3,41,394,8,41,1,41,4,41,397,8,41,11,41,12,41,398,1,41,4,41,402,8,41,11,
  	41,12,41,403,1,41,1,41,1,41,3,41,409,8,41,1,41,4,41,412,8,41,11,41,12,
  	41,413,1,41,4,41,417,8,41,11,41,12,41,418,1,41,1,41,4,41,423,8,41,11,
  	41,12,41,424,1,41,1,41,3,41,429,8,41,1,41,4,41,432,8,41,11,41,12,41,433,
  	3,41,436,8,41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,3,42,447,8,
  	42,1,43,1,43,1,43,1,43,5,43,453,8,43,10,43,12,43,456,9,43,1,43,1,43,1,
  	44,1,44,1,44,1,44,5,44,464,8,44,10,44,12,44,467,9,44,1,44,1,44,1,44,1,
  	44,1,44,1,45,1,45,3,45,476,8,45,1,45,3,45,479,8,45,1,45,1,45,1,46,4,46,
  	484,8,46,11,46,12,46,485,1,46,1,46,1,465,0,47,1,1,3,2,5,3,7,4,9,5,11,
  	6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,
  	37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,
  	30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,40,81,41,
  	83,42,85,43,87,44,89,45,91,46,93,47,1,0,12,3,0,65,90,95,95,97,122,4,0,
  	48,57,65,90,95,95,97,122,1,0,49,57,1,0,48,57,1,0,48,55,2,0,88,88,120,
  	120,3,0,48,57,65,70,97,102,2,0,70,70,102,102,2,0,69,69,101,101,2,0,43,
  	43,45,45,2,0,10,10,13,13,2,0,9,9,32,32,547,0,1,1,0,0,0,0,3,1,0,0,0,0,
  	5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,
  	0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,
  	0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,
  	1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,
  	0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,
  	0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,
  	1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,
  	0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,
  	0,91,1,0,0,0,0,93,1,0,0,0,1,95,1,0,0,0,3,99,1,0,0,0,5,105,1,0,0,0,7,112,
  	1,0,0,0,9,117,1,0,0,0,11,122,1,0,0,0,13,128,1,0,0,0,15,135,1,0,0,0,17,
  	138,1,0,0,0,19,143,1,0,0,0,21,149,1,0,0,0,23,155,1,0,0,0,25,164,1,0,0,
  	0,27,166,1,0,0,0,29,169,1,0,0,0,31,172,1,0,0,0,33,175,1,0,0,0,35,178,
  	1,0,0,0,37,180,1,0,0,0,39,183,1,0,0,0,41,185,1,0,0,0,43,188,1,0,0,0,45,
  	190,1,0,0,0,47,192,1,0,0,0,49,194,1,0,0,0,51,196,1,0,0,0,53,198,1,0,0,
  	0,55,200,1,0,0,0,57,202,1,0,0,0,59,204,1,0,0,0,61,206,1,0,0,0,63,208,
  	1,0,0,0,65,210,1,0,0,0,67,212,1,0,0,0,69,214,1,0,0,0,71,216,1,0,0,0,73,
  	218,1,0,0,0,75,220,1,0,0,0,77,222,1,0,0,0,79,250,1,0,0,0,81,346,1,0,0,
  	0,83,435,1,0,0,0,85,446,1,0,0,0,87,448,1,0,0,0,89,459,1,0,0,0,91,478,
  	1,0,0,0,93,483,1,0,0,0,95,96,5,105,0,0,96,97,5,110,0,0,97,98,5,116,0,
  	0,98,2,1,0,0,0,99,100,5,102,0,0,100,101,5,108,0,0,101,102,5,111,0,0,102,
  	103,5,97,0,0,103,104,5,116,0,0,104,4,1,0,0,0,105,106,5,100,0,0,106,107,
  	5,111,0,0,107,108,5,117,0,0,108,109,5,98,0,0,109,110,5,108,0,0,110,111,
  	5,101,0,0,111,6,1,0,0,0,112,113,5,98,0,0,113,114,5,111,0,0,114,115,5,
  	111,0,0,115,116,5,108,0,0,116,8,1,0,0,0,117,118,5,118,0,0,118,119,5,111,
  	0,0,119,120,5,105,0,0,120,121,5,100,0,0,121,10,1,0,0,0,122,123,5,99,0,
  	0,123,124,5,111,0,0,124,125,5,110,0,0,125,126,5,115,0,0,126,127,5,116,
  	0,0,127,12,1,0,0,0,128,129,5,114,0,0,129,130,5,101,0,0,130,131,5,116,
  	0,0,131,132,5,117,0,0,132,133,5,114,0,0,133,134,5,110,0,0,134,14,1,0,
  	0,0,135,136,5,105,0,0,136,137,5,102,0,0,137,16,1,0,0,0,138,139,5,101,
  	0,0,139,140,5,108,0,0,140,141,5,115,0,0,141,142,5,101,0,0,142,18,1,0,
  	0,0,143,144,5,119,0,0,144,145,5,104,0,0,145,146,5,105,0,0,146,147,5,108,
  	0,0,147,148,5,101,0,0,148,20,1,0,0,0,149,150,5,98,0,0,150,151,5,114,0,
  	0,151,152,5,101,0,0,152,153,5,97,0,0,153,154,5,107,0,0,154,22,1,0,0,0,
  	155,156,5,99,0,0,156,157,5,111,0,0,157,158,5,110,0,0,158,159,5,116,0,
  	0,159,160,5,105,0,0,160,161,5,110,0,0,161,162,5,117,0,0,162,163,5,101,
  	0,0,163,24,1,0,0,0,164,165,5,61,0,0,165,26,1,0,0,0,166,167,5,61,0,0,167,
  	168,5,61,0,0,168,28,1,0,0,0,169,170,5,38,0,0,170,171,5,38,0,0,171,30,
  	1,0,0,0,172,173,5,124,0,0,173,174,5,124,0,0,174,32,1,0,0,0,175,176,5,
  	33,0,0,176,177,5,61,0,0,177,34,1,0,0,0,178,179,5,60,0,0,179,36,1,0,0,
  	0,180,181,5,60,0,0,181,182,5,61,0,0,182,38,1,0,0,0,183,184,5,62,0,0,184,
  	40,1,0,0,0,185,186,5,62,0,0,186,187,5,61,0,0,187,42,1,0,0,0,188,189,5,
  	46,0,0,189,44,1,0,0,0,190,191,5,44,0,0,191,46,1,0,0,0,192,193,5,59,0,
  	0,193,48,1,0,0,0,194,195,5,58,0,0,195,50,1,0,0,0,196,197,5,40,0,0,197,
  	52,1,0,0,0,198,199,5,41,0,0,199,54,1,0,0,0,200,201,5,91,0,0,201,56,1,
  	0,0,0,202,203,5,93,0,0,203,58,1,0,0,0,204,205,5,123,0,0,205,60,1,0,0,
  	0,206,207,5,125,0,0,207,62,1,0,0,0,208,209,5,43,0,0,209,64,1,0,0,0,210,
  	211,5,45,0,0,211,66,1,0,0,0,212,213,5,124,0,0,213,68,1,0,0,0,214,215,
  	5,33,0,0,215,70,1,0,0,0,216,217,5,42,0,0,217,72,1,0,0,0,218,219,5,47,
  	0,0,219,74,1,0,0,0,220,221,5,37,0,0,221,76,1,0,0,0,222,226,7,0,0,0,223,
  	225,7,1,0,0,224,223,1,0,0,0,225,228,1,0,0,0,226,224,1,0,0,0,226,227,1,
  	0,0,0,227,78,1,0,0,0,228,226,1,0,0,0,229,251,5,48,0,0,230,234,7,2,0,0,
  	231,233,7,3,0,0,232,231,1,0,0,0,233,236,1,0,0,0,234,232,1,0,0,0,234,235,
  	1,0,0,0,235,251,1,0,0,0,236,234,1,0,0,0,237,239,5,48,0,0,238,240,7,4,
  	0,0,239,238,1,0,0,0,240,241,1,0,0,0,241,239,1,0,0,0,241,242,1,0,0,0,242,
  	251,1,0,0,0,243,244,5,48,0,0,244,246,7,5,0,0,245,247,7,6,0,0,246,245,
  	1,0,0,0,247,248,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,251,1,0,0,
  	0,250,229,1,0,0,0,250,230,1,0,0,0,250,237,1,0,0,0,250,243,1,0,0,0,251,
  	80,1,0,0,0,252,254,5,46,0,0,253,255,7,3,0,0,254,253,1,0,0,0,255,256,1,
  	0,0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,258,1,0,0,0,258,347,7,7,0,0,
  	259,261,7,3,0,0,260,259,1,0,0,0,261,262,1,0,0,0,262,260,1,0,0,0,262,263,
  	1,0,0,0,263,264,1,0,0,0,264,265,5,46,0,0,265,347,7,7,0,0,266,268,7,3,
  	0,0,267,266,1,0,0,0,268,269,1,0,0,0,269,267,1,0,0,0,269,270,1,0,0,0,270,
  	271,1,0,0,0,271,273,5,46,0,0,272,274,7,3,0,0,273,272,1,0,0,0,274,275,
  	1,0,0,0,275,273,1,0,0,0,275,276,1,0,0,0,276,277,1,0,0,0,277,347,7,7,0,
  	0,278,280,5,46,0,0,279,281,7,3,0,0,280,279,1,0,0,0,281,282,1,0,0,0,282,
  	280,1,0,0,0,282,283,1,0,0,0,283,284,1,0,0,0,284,286,7,8,0,0,285,287,7,
  	9,0,0,286,285,1,0,0,0,286,287,1,0,0,0,287,289,1,0,0,0,288,290,7,3,0,0,
  	289,288,1,0,0,0,290,291,1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,292,293,
  	1,0,0,0,293,347,7,7,0,0,294,296,7,3,0,0,295,294,1,0,0,0,296,297,1,0,0,
  	0,297,295,1,0,0,0,297,298,1,0,0,0,298,299,1,0,0,0,299,301,7,8,0,0,300,
  	302,7,9,0,0,301,300,1,0,0,0,301,302,1,0,0,0,302,304,1,0,0,0,303,305,7,
  	3,0,0,304,303,1,0,0,0,305,306,1,0,0,0,306,304,1,0,0,0,306,307,1,0,0,0,
  	307,308,1,0,0,0,308,347,7,7,0,0,309,311,7,3,0,0,310,309,1,0,0,0,311,312,
  	1,0,0,0,312,310,1,0,0,0,312,313,1,0,0,0,313,314,1,0,0,0,314,315,5,46,
  	0,0,315,317,7,8,0,0,316,318,7,9,0,0,317,316,1,0,0,0,317,318,1,0,0,0,318,
  	320,1,0,0,0,319,321,7,3,0,0,320,319,1,0,0,0,321,322,1,0,0,0,322,320,1,
  	0,0,0,322,323,1,0,0,0,323,324,1,0,0,0,324,347,7,7,0,0,325,327,7,3,0,0,
  	326,325,1,0,0,0,327,328,1,0,0,0,328,326,1,0,0,0,328,329,1,0,0,0,329,330,
  	1,0,0,0,330,332,5,46,0,0,331,333,7,3,0,0,332,331,1,0,0,0,333,334,1,0,
  	0,0,334,332,1,0,0,0,334,335,1,0,0,0,335,336,1,0,0,0,336,338,7,8,0,0,337,
  	339,7,9,0,0,338,337,1,0,0,0,338,339,1,0,0,0,339,341,1,0,0,0,340,342,7,
  	3,0,0,341,340,1,0,0,0,342,343,1,0,0,0,343,341,1,0,0,0,343,344,1,0,0,0,
  	344,345,1,0,0,0,345,347,7,7,0,0,346,252,1,0,0,0,346,260,1,0,0,0,346,267,
  	1,0,0,0,346,278,1,0,0,0,346,295,1,0,0,0,346,310,1,0,0,0,346,326,1,0,0,
  	0,347,82,1,0,0,0,348,350,5,46,0,0,349,351,7,3,0,0,350,349,1,0,0,0,351,
  	352,1,0,0,0,352,350,1,0,0,0,352,353,1,0,0,0,353,436,1,0,0,0,354,356,7,
  	3,0,0,355,354,1,0,0,0,356,357,1,0,0,0,357,355,1,0,0,0,357,358,1,0,0,0,
  	358,359,1,0,0,0,359,436,5,46,0,0,360,362,7,3,0,0,361,360,1,0,0,0,362,
  	363,1,0,0,0,363,361,1,0,0,0,363,364,1,0,0,0,364,365,1,0,0,0,365,367,5,
  	46,0,0,366,368,7,3,0,0,367,366,1,0,0,0,368,369,1,0,0,0,369,367,1,0,0,
  	0,369,370,1,0,0,0,370,436,1,0,0,0,371,373,7,3,0,0,372,371,1,0,0,0,373,
  	374,1,0,0,0,374,372,1,0,0,0,374,375,1,0,0,0,375,376,1,0,0,0,376,378,7,
  	8,0,0,377,379,7,9,0,0,378,377,1,0,0,0,378,379,1,0,0,0,379,381,1,0,0,0,
  	380,382,7,3,0,0,381,380,1,0,0,0,382,383,1,0,0,0,383,381,1,0,0,0,383,384,
  	1,0,0,0,384,436,1,0,0,0,385,387,5,46,0,0,386,388,7,3,0,0,387,386,1,0,
  	0,0,388,389,1,0,0,0,389,387,1,0,0,0,389,390,1,0,0,0,390,391,1,0,0,0,391,
  	393,7,8,0,0,392,394,7,9,0,0,393,392,1,0,0,0,393,394,1,0,0,0,394,396,1,
  	0,0,0,395,397,7,3,0,0,396,395,1,0,0,0,397,398,1,0,0,0,398,396,1,0,0,0,
  	398,399,1,0,0,0,399,436,1,0,0,0,400,402,7,3,0,0,401,400,1,0,0,0,402,403,
  	1,0,0,0,403,401,1,0,0,0,403,404,1,0,0,0,404,405,1,0,0,0,405,406,5,46,
  	0,0,406,408,7,8,0,0,407,409,7,9,0,0,408,407,1,0,0,0,408,409,1,0,0,0,409,
  	411,1,0,0,0,410,412,7,3,0,0,411,410,1,0,0,0,412,413,1,0,0,0,413,411,1,
  	0,0,0,413,414,1,0,0,0,414,436,1,0,0,0,415,417,7,3,0,0,416,415,1,0,0,0,
  	417,418,1,0,0,0,418,416,1,0,0,0,418,419,1,0,0,0,419,420,1,0,0,0,420,422,
  	5,46,0,0,421,423,7,3,0,0,422,421,1,0,0,0,423,424,1,0,0,0,424,422,1,0,
  	0,0,424,425,1,0,0,0,425,426,1,0,0,0,426,428,7,8,0,0,427,429,7,9,0,0,428,
  	427,1,0,0,0,428,429,1,0,0,0,429,431,1,0,0,0,430,432,7,3,0,0,431,430,1,
  	0,0,0,432,433,1,0,0,0,433,431,1,0,0,0,433,434,1,0,0,0,434,436,1,0,0,0,
  	435,348,1,0,0,0,435,355,1,0,0,0,435,361,1,0,0,0,435,372,1,0,0,0,435,385,
  	1,0,0,0,435,401,1,0,0,0,435,416,1,0,0,0,436,84,1,0,0,0,437,438,5,116,
  	0,0,438,439,5,114,0,0,439,440,5,117,0,0,440,447,5,101,0,0,441,442,5,102,
  	0,0,442,443,5,97,0,0,443,444,5,108,0,0,444,445,5,115,0,0,445,447,5,101,
  	0,0,446,437,1,0,0,0,446,441,1,0,0,0,447,86,1,0,0,0,448,449,5,47,0,0,449,
  	450,5,47,0,0,450,454,1,0,0,0,451,453,8,10,0,0,452,451,1,0,0,0,453,456,
  	1,0,0,0,454,452,1,0,0,0,454,455,1,0,0,0,455,457,1,0,0,0,456,454,1,0,0,
  	0,457,458,6,43,0,0,458,88,1,0,0,0,459,460,5,47,0,0,460,461,5,42,0,0,461,
  	465,1,0,0,0,462,464,9,0,0,0,463,462,1,0,0,0,464,467,1,0,0,0,465,466,1,
  	0,0,0,465,463,1,0,0,0,466,468,1,0,0,0,467,465,1,0,0,0,468,469,5,42,0,
  	0,469,470,5,47,0,0,470,471,1,0,0,0,471,472,6,44,0,0,472,90,1,0,0,0,473,
  	475,5,13,0,0,474,476,5,10,0,0,475,474,1,0,0,0,475,476,1,0,0,0,476,479,
  	1,0,0,0,477,479,5,10,0,0,478,473,1,0,0,0,478,477,1,0,0,0,479,480,1,0,
  	0,0,480,481,6,45,0,0,481,92,1,0,0,0,482,484,7,11,0,0,483,482,1,0,0,0,
  	484,485,1,0,0,0,485,483,1,0,0,0,485,486,1,0,0,0,486,487,1,0,0,0,487,488,
  	6,46,0,0,488,94,1,0,0,0,48,0,226,234,241,248,250,256,262,269,275,282,
  	286,291,297,301,306,312,317,322,328,334,338,343,346,352,357,363,369,374,
  	378,383,389,393,398,403,408,413,418,424,428,433,435,446,454,465,475,478,
  	485,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cactlexerLexerStaticData = staticData.release();
}

}

CactLexer::CactLexer(CharStream *input) : Lexer(input) {
  CactLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *cactlexerLexerStaticData->atn, cactlexerLexerStaticData->decisionToDFA, cactlexerLexerStaticData->sharedContextCache);
}

CactLexer::~CactLexer() {
  delete _interpreter;
}

std::string CactLexer::getGrammarFileName() const {
  return "CactLexer.g4";
}

const std::vector<std::string>& CactLexer::getRuleNames() const {
  return cactlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CactLexer::getChannelNames() const {
  return cactlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CactLexer::getModeNames() const {
  return cactlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CactLexer::getVocabulary() const {
  return cactlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CactLexer::getSerializedATN() const {
  return cactlexerLexerStaticData->serializedATN;
}

const atn::ATN& CactLexer::getATN() const {
  return *cactlexerLexerStaticData->atn;
}




void CactLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cactlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(cactlexerLexerOnceFlag, cactlexerLexerInitialize);
#endif
}