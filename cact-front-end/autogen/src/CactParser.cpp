
#include <cact-front-end/cact-expr.h>
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/symbol-registry.h>


// Generated from ./grammar/CactParser.g4 by ANTLR 4.13.1


#include "CactParserVisitor.h"

#include "CactParser.h"


using namespace antlrcpp;
using namespace cactfrontend;

using namespace antlr4;

namespace {

struct CactParserStaticData final {
  CactParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CactParserStaticData(const CactParserStaticData&) = delete;
  CactParserStaticData(CactParserStaticData&&) = delete;
  CactParserStaticData& operator=(const CactParserStaticData&) = delete;
  CactParserStaticData& operator=(CactParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cactparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CactParserStaticData *cactparserParserStaticData = nullptr;

void cactparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cactparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(cactparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CactParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "declaration", "constantDeclaration", "basicType", 
      "constantDefinition", "constantInitialValue", "variableDeclaration", 
      "variableDefinition", "functionDefinition", "functionType", "functionFormalParams", 
      "functionFormalParam", "block", "blockItem", "statement", "assignStatement", 
      "expressionStatement", "returnStatement", "ifStatement", "whileStatement", 
      "breakStatement", "continueStatement", "expression", "constantExpression", 
      "condition", "leftValue", "primaryExpression", "number", "unaryExpression", 
      "functionRealParams", "mulExpression", "addExpression", "relationalExpression", 
      "logicalEqualExpression", "logicalAndExpression", "logicalOrExpression"
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
  	4,1,47,362,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,1,0,1,0,5,0,75,8,0,10,0,12,0,78,9,0,1,1,1,1,3,1,82,8,1,1,2,1,2,1,2,
  	1,2,1,2,5,2,89,8,2,10,2,12,2,92,9,2,1,2,1,2,1,3,1,3,1,4,1,4,1,4,1,4,5,
  	4,102,8,4,10,4,12,4,105,9,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,115,8,
  	5,10,5,12,5,118,9,5,3,5,120,8,5,1,5,3,5,123,8,5,1,6,1,6,1,6,1,6,5,6,129,
  	8,6,10,6,12,6,132,9,6,1,6,1,6,1,7,1,7,1,7,1,7,5,7,140,8,7,10,7,12,7,143,
  	9,7,1,7,1,7,3,7,147,8,7,1,8,1,8,1,8,1,8,3,8,153,8,8,1,8,1,8,1,8,1,9,1,
  	9,1,10,1,10,1,10,5,10,163,8,10,10,10,12,10,166,9,10,1,11,1,11,1,11,1,
  	11,3,11,172,8,11,1,11,1,11,1,11,1,11,5,11,178,8,11,10,11,12,11,181,9,
  	11,3,11,183,8,11,1,12,1,12,5,12,187,8,12,10,12,12,12,190,9,12,1,12,1,
  	12,1,13,1,13,3,13,196,8,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,
  	14,206,8,14,1,15,1,15,1,15,1,15,1,15,1,16,3,16,214,8,16,1,16,1,16,1,17,
  	1,17,3,17,220,8,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,
  	231,8,18,1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,
  	1,22,1,22,3,22,247,8,22,1,23,1,23,3,23,251,8,23,1,24,1,24,1,25,1,25,1,
  	25,1,25,1,25,5,25,260,8,25,10,25,12,25,263,9,25,1,26,1,26,1,26,1,26,1,
  	26,1,26,3,26,271,8,26,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,281,
  	8,28,1,28,3,28,284,8,28,1,29,1,29,1,29,5,29,289,8,29,10,29,12,29,292,
  	9,29,1,30,1,30,1,30,1,30,1,30,1,30,5,30,300,8,30,10,30,12,30,303,9,30,
  	1,31,1,31,1,31,1,31,1,31,1,31,5,31,311,8,31,10,31,12,31,314,9,31,1,32,
  	1,32,1,32,1,32,1,32,1,32,5,32,322,8,32,10,32,12,32,325,9,32,1,33,1,33,
  	1,33,1,33,1,33,1,33,5,33,333,8,33,10,33,12,33,336,9,33,1,34,1,34,1,34,
  	1,34,1,34,1,34,5,34,344,8,34,10,34,12,34,347,9,34,1,35,1,35,1,35,3,35,
  	352,8,35,1,35,1,35,1,35,5,35,357,8,35,10,35,12,35,360,9,35,1,35,0,6,60,
  	62,64,66,68,70,36,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,
  	38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,0,8,1,0,1,4,1,0,1,
  	5,1,0,40,42,2,0,32,33,35,35,1,0,36,38,1,0,32,33,1,0,18,21,2,0,14,14,17,
  	17,369,0,76,1,0,0,0,2,81,1,0,0,0,4,83,1,0,0,0,6,95,1,0,0,0,8,97,1,0,0,
  	0,10,122,1,0,0,0,12,124,1,0,0,0,14,135,1,0,0,0,16,148,1,0,0,0,18,157,
  	1,0,0,0,20,159,1,0,0,0,22,167,1,0,0,0,24,184,1,0,0,0,26,195,1,0,0,0,28,
  	205,1,0,0,0,30,207,1,0,0,0,32,213,1,0,0,0,34,217,1,0,0,0,36,223,1,0,0,
  	0,38,232,1,0,0,0,40,238,1,0,0,0,42,241,1,0,0,0,44,246,1,0,0,0,46,250,
  	1,0,0,0,48,252,1,0,0,0,50,254,1,0,0,0,52,270,1,0,0,0,54,272,1,0,0,0,56,
  	283,1,0,0,0,58,285,1,0,0,0,60,293,1,0,0,0,62,304,1,0,0,0,64,315,1,0,0,
  	0,66,326,1,0,0,0,68,337,1,0,0,0,70,351,1,0,0,0,72,75,3,2,1,0,73,75,3,
  	16,8,0,74,72,1,0,0,0,74,73,1,0,0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,
  	1,0,0,0,77,1,1,0,0,0,78,76,1,0,0,0,79,82,3,4,2,0,80,82,3,12,6,0,81,79,
  	1,0,0,0,81,80,1,0,0,0,82,3,1,0,0,0,83,84,5,6,0,0,84,85,3,6,3,0,85,90,
  	3,8,4,0,86,87,5,23,0,0,87,89,3,8,4,0,88,86,1,0,0,0,89,92,1,0,0,0,90,88,
  	1,0,0,0,90,91,1,0,0,0,91,93,1,0,0,0,92,90,1,0,0,0,93,94,5,24,0,0,94,5,
  	1,0,0,0,95,96,7,0,0,0,96,7,1,0,0,0,97,103,5,39,0,0,98,99,5,28,0,0,99,
  	100,5,40,0,0,100,102,5,29,0,0,101,98,1,0,0,0,102,105,1,0,0,0,103,101,
  	1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,103,1,0,0,0,106,107,5,13,
  	0,0,107,108,3,10,5,0,108,9,1,0,0,0,109,123,3,46,23,0,110,119,5,30,0,0,
  	111,116,3,10,5,0,112,113,5,23,0,0,113,115,3,10,5,0,114,112,1,0,0,0,115,
  	118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,117,120,1,0,0,0,118,116,1,
  	0,0,0,119,111,1,0,0,0,119,120,1,0,0,0,120,121,1,0,0,0,121,123,5,31,0,
  	0,122,109,1,0,0,0,122,110,1,0,0,0,123,11,1,0,0,0,124,125,3,6,3,0,125,
  	130,3,14,7,0,126,127,5,23,0,0,127,129,3,14,7,0,128,126,1,0,0,0,129,132,
  	1,0,0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,133,1,0,0,0,132,130,1,0,0,
  	0,133,134,5,24,0,0,134,13,1,0,0,0,135,141,5,39,0,0,136,137,5,28,0,0,137,
  	138,5,40,0,0,138,140,5,29,0,0,139,136,1,0,0,0,140,143,1,0,0,0,141,139,
  	1,0,0,0,141,142,1,0,0,0,142,146,1,0,0,0,143,141,1,0,0,0,144,145,5,13,
  	0,0,145,147,3,10,5,0,146,144,1,0,0,0,146,147,1,0,0,0,147,15,1,0,0,0,148,
  	149,3,18,9,0,149,150,5,39,0,0,150,152,5,26,0,0,151,153,3,20,10,0,152,
  	151,1,0,0,0,152,153,1,0,0,0,153,154,1,0,0,0,154,155,5,27,0,0,155,156,
  	3,24,12,0,156,17,1,0,0,0,157,158,7,1,0,0,158,19,1,0,0,0,159,164,3,22,
  	11,0,160,161,5,23,0,0,161,163,3,22,11,0,162,160,1,0,0,0,163,166,1,0,0,
  	0,164,162,1,0,0,0,164,165,1,0,0,0,165,21,1,0,0,0,166,164,1,0,0,0,167,
  	168,3,6,3,0,168,182,5,39,0,0,169,171,5,28,0,0,170,172,5,40,0,0,171,170,
  	1,0,0,0,171,172,1,0,0,0,172,173,1,0,0,0,173,179,5,29,0,0,174,175,5,28,
  	0,0,175,176,5,40,0,0,176,178,5,29,0,0,177,174,1,0,0,0,178,181,1,0,0,0,
  	179,177,1,0,0,0,179,180,1,0,0,0,180,183,1,0,0,0,181,179,1,0,0,0,182,169,
  	1,0,0,0,182,183,1,0,0,0,183,23,1,0,0,0,184,188,5,30,0,0,185,187,3,26,
  	13,0,186,185,1,0,0,0,187,190,1,0,0,0,188,186,1,0,0,0,188,189,1,0,0,0,
  	189,191,1,0,0,0,190,188,1,0,0,0,191,192,5,31,0,0,192,25,1,0,0,0,193,196,
  	3,2,1,0,194,196,3,28,14,0,195,193,1,0,0,0,195,194,1,0,0,0,196,27,1,0,
  	0,0,197,206,3,30,15,0,198,206,3,32,16,0,199,206,3,24,12,0,200,206,3,34,
  	17,0,201,206,3,36,18,0,202,206,3,38,19,0,203,206,3,40,20,0,204,206,3,
  	42,21,0,205,197,1,0,0,0,205,198,1,0,0,0,205,199,1,0,0,0,205,200,1,0,0,
  	0,205,201,1,0,0,0,205,202,1,0,0,0,205,203,1,0,0,0,205,204,1,0,0,0,206,
  	29,1,0,0,0,207,208,3,50,25,0,208,209,5,13,0,0,209,210,3,44,22,0,210,211,
  	5,24,0,0,211,31,1,0,0,0,212,214,3,44,22,0,213,212,1,0,0,0,213,214,1,0,
  	0,0,214,215,1,0,0,0,215,216,5,24,0,0,216,33,1,0,0,0,217,219,5,7,0,0,218,
  	220,3,44,22,0,219,218,1,0,0,0,219,220,1,0,0,0,220,221,1,0,0,0,221,222,
  	5,24,0,0,222,35,1,0,0,0,223,224,5,8,0,0,224,225,5,26,0,0,225,226,3,48,
  	24,0,226,227,5,27,0,0,227,230,3,28,14,0,228,229,5,9,0,0,229,231,3,28,
  	14,0,230,228,1,0,0,0,230,231,1,0,0,0,231,37,1,0,0,0,232,233,5,10,0,0,
  	233,234,5,26,0,0,234,235,3,48,24,0,235,236,5,27,0,0,236,237,3,28,14,0,
  	237,39,1,0,0,0,238,239,5,11,0,0,239,240,5,24,0,0,240,41,1,0,0,0,241,242,
  	5,12,0,0,242,243,5,24,0,0,243,43,1,0,0,0,244,247,3,62,31,0,245,247,5,
  	43,0,0,246,244,1,0,0,0,246,245,1,0,0,0,247,45,1,0,0,0,248,251,3,54,27,
  	0,249,251,5,43,0,0,250,248,1,0,0,0,250,249,1,0,0,0,251,47,1,0,0,0,252,
  	253,3,70,35,0,253,49,1,0,0,0,254,261,5,39,0,0,255,256,5,28,0,0,256,257,
  	3,44,22,0,257,258,5,29,0,0,258,260,1,0,0,0,259,255,1,0,0,0,260,263,1,
  	0,0,0,261,259,1,0,0,0,261,262,1,0,0,0,262,51,1,0,0,0,263,261,1,0,0,0,
  	264,265,5,26,0,0,265,266,3,44,22,0,266,267,5,27,0,0,267,271,1,0,0,0,268,
  	271,3,50,25,0,269,271,3,54,27,0,270,264,1,0,0,0,270,268,1,0,0,0,270,269,
  	1,0,0,0,271,53,1,0,0,0,272,273,7,2,0,0,273,55,1,0,0,0,274,284,3,52,26,
  	0,275,276,7,3,0,0,276,284,3,56,28,0,277,278,5,39,0,0,278,280,5,26,0,0,
  	279,281,3,58,29,0,280,279,1,0,0,0,280,281,1,0,0,0,281,282,1,0,0,0,282,
  	284,5,27,0,0,283,274,1,0,0,0,283,275,1,0,0,0,283,277,1,0,0,0,284,57,1,
  	0,0,0,285,290,3,44,22,0,286,287,5,23,0,0,287,289,3,44,22,0,288,286,1,
  	0,0,0,289,292,1,0,0,0,290,288,1,0,0,0,290,291,1,0,0,0,291,59,1,0,0,0,
  	292,290,1,0,0,0,293,294,6,30,-1,0,294,295,3,56,28,0,295,301,1,0,0,0,296,
  	297,10,1,0,0,297,298,7,4,0,0,298,300,3,56,28,0,299,296,1,0,0,0,300,303,
  	1,0,0,0,301,299,1,0,0,0,301,302,1,0,0,0,302,61,1,0,0,0,303,301,1,0,0,
  	0,304,305,6,31,-1,0,305,306,3,60,30,0,306,312,1,0,0,0,307,308,10,1,0,
  	0,308,309,7,5,0,0,309,311,3,60,30,0,310,307,1,0,0,0,311,314,1,0,0,0,312,
  	310,1,0,0,0,312,313,1,0,0,0,313,63,1,0,0,0,314,312,1,0,0,0,315,316,6,
  	32,-1,0,316,317,3,62,31,0,317,323,1,0,0,0,318,319,10,1,0,0,319,320,7,
  	6,0,0,320,322,3,62,31,0,321,318,1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,
  	0,323,324,1,0,0,0,324,65,1,0,0,0,325,323,1,0,0,0,326,327,6,33,-1,0,327,
  	328,3,64,32,0,328,334,1,0,0,0,329,330,10,1,0,0,330,331,7,7,0,0,331,333,
  	3,64,32,0,332,329,1,0,0,0,333,336,1,0,0,0,334,332,1,0,0,0,334,335,1,0,
  	0,0,335,67,1,0,0,0,336,334,1,0,0,0,337,338,6,34,-1,0,338,339,3,66,33,
  	0,339,345,1,0,0,0,340,341,10,1,0,0,341,342,5,15,0,0,342,344,3,66,33,0,
  	343,340,1,0,0,0,344,347,1,0,0,0,345,343,1,0,0,0,345,346,1,0,0,0,346,69,
  	1,0,0,0,347,345,1,0,0,0,348,349,6,35,-1,0,349,352,5,43,0,0,350,352,3,
  	68,34,0,351,348,1,0,0,0,351,350,1,0,0,0,352,358,1,0,0,0,353,354,10,1,
  	0,0,354,355,5,16,0,0,355,357,3,68,34,0,356,353,1,0,0,0,357,360,1,0,0,
  	0,358,356,1,0,0,0,358,359,1,0,0,0,359,71,1,0,0,0,360,358,1,0,0,0,36,74,
  	76,81,90,103,116,119,122,130,141,146,152,164,171,179,182,188,195,205,
  	213,219,230,246,250,261,270,280,283,290,301,312,323,334,345,351,358
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cactparserParserStaticData = staticData.release();
}

}

CactParser::CactParser(TokenStream *input) : CactParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CactParser::CactParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CactParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cactparserParserStaticData->atn, cactparserParserStaticData->decisionToDFA, cactparserParserStaticData->sharedContextCache, options);
}

CactParser::~CactParser() {
  delete _interpreter;
}

const atn::ATN& CactParser::getATN() const {
  return *cactparserParserStaticData->atn;
}

std::string CactParser::getGrammarFileName() const {
  return "CactParser.g4";
}

const std::vector<std::string>& CactParser::getRuleNames() const {
  return cactparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& CactParser::getVocabulary() const {
  return cactparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CactParser::getSerializedATN() const {
  return cactparserParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

CactParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CactParser::DeclarationContext *> CactParser::CompilationUnitContext::declaration() {
  return getRuleContexts<CactParser::DeclarationContext>();
}

CactParser::DeclarationContext* CactParser::CompilationUnitContext::declaration(size_t i) {
  return getRuleContext<CactParser::DeclarationContext>(i);
}

std::vector<CactParser::FunctionDefinitionContext *> CactParser::CompilationUnitContext::functionDefinition() {
  return getRuleContexts<CactParser::FunctionDefinitionContext>();
}

CactParser::FunctionDefinitionContext* CactParser::CompilationUnitContext::functionDefinition(size_t i) {
  return getRuleContext<CactParser::FunctionDefinitionContext>(i);
}


size_t CactParser::CompilationUnitContext::getRuleIndex() const {
  return CactParser::RuleCompilationUnit;
}


std::any CactParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

CactParser::CompilationUnitContext* CactParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, CactParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 126) != 0)) {
      setState(74);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(72);
        declaration();
        break;
      }

      case 2: {
        setState(73);
        functionDefinition();
        break;
      }

      default:
        break;
      }
      setState(78);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

CactParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::ConstantDeclarationContext* CactParser::DeclarationContext::constantDeclaration() {
  return getRuleContext<CactParser::ConstantDeclarationContext>(0);
}

CactParser::VariableDeclarationContext* CactParser::DeclarationContext::variableDeclaration() {
  return getRuleContext<CactParser::VariableDeclarationContext>(0);
}


size_t CactParser::DeclarationContext::getRuleIndex() const {
  return CactParser::RuleDeclaration;
}


std::any CactParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CactParser::DeclarationContext* CactParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, CactParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(81);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(79);
        constantDeclaration();
        break;
      }

      case CactParser::Int32:
      case CactParser::Float:
      case CactParser::Double:
      case CactParser::Bool: {
        enterOuterAlt(_localctx, 2);
        setState(80);
        variableDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDeclarationContext ------------------------------------------------------------------

CactParser::ConstantDeclarationContext::ConstantDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ConstantDeclarationContext::Const() {
  return getToken(CactParser::Const, 0);
}

CactParser::BasicTypeContext* CactParser::ConstantDeclarationContext::basicType() {
  return getRuleContext<CactParser::BasicTypeContext>(0);
}

std::vector<CactParser::ConstantDefinitionContext *> CactParser::ConstantDeclarationContext::constantDefinition() {
  return getRuleContexts<CactParser::ConstantDefinitionContext>();
}

CactParser::ConstantDefinitionContext* CactParser::ConstantDeclarationContext::constantDefinition(size_t i) {
  return getRuleContext<CactParser::ConstantDefinitionContext>(i);
}

tree::TerminalNode* CactParser::ConstantDeclarationContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDeclarationContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::ConstantDeclarationContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::ConstantDeclarationContext::getRuleIndex() const {
  return CactParser::RuleConstantDeclaration;
}


std::any CactParser::ConstantDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantDeclarationContext* CactParser::constantDeclaration() {
  ConstantDeclarationContext *_localctx = _tracker.createInstance<ConstantDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, CactParser::RuleConstantDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    match(CactParser::Const);
    setState(84);
    basicType();
    setState(85);
    constantDefinition();
    setState(90);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(86);
      match(CactParser::Comma);
      setState(87);
      constantDefinition();
      setState(92);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(93);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

CactParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::BasicTypeContext::Int32() {
  return getToken(CactParser::Int32, 0);
}

tree::TerminalNode* CactParser::BasicTypeContext::Bool() {
  return getToken(CactParser::Bool, 0);
}

tree::TerminalNode* CactParser::BasicTypeContext::Float() {
  return getToken(CactParser::Float, 0);
}

tree::TerminalNode* CactParser::BasicTypeContext::Double() {
  return getToken(CactParser::Double, 0);
}


size_t CactParser::BasicTypeContext::getRuleIndex() const {
  return CactParser::RuleBasicType;
}


std::any CactParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BasicTypeContext* CactParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, CactParser::RuleBasicType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(95);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDefinitionContext ------------------------------------------------------------------

CactParser::ConstantDefinitionContext::ConstantDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ConstantInitialValueContext* CactParser::ConstantDefinitionContext::constantInitialValue() {
  return getRuleContext<CactParser::ConstantInitialValueContext>(0);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDefinitionContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDefinitionContext::IntegerConstant() {
  return getTokens(CactParser::IntegerConstant);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::IntegerConstant(size_t i) {
  return getToken(CactParser::IntegerConstant, i);
}

std::vector<tree::TerminalNode *> CactParser::ConstantDefinitionContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}


size_t CactParser::ConstantDefinitionContext::getRuleIndex() const {
  return CactParser::RuleConstantDefinition;
}


std::any CactParser::ConstantDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantDefinition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantDefinitionContext* CactParser::constantDefinition() {
  ConstantDefinitionContext *_localctx = _tracker.createInstance<ConstantDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 8, CactParser::RuleConstantDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    match(CactParser::Identifier);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::LeftBracket) {
      setState(98);
      match(CactParser::LeftBracket);
      setState(99);
      match(CactParser::IntegerConstant);
      setState(100);
      match(CactParser::RightBracket);
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
    match(CactParser::Equal);
    setState(107);
    constantInitialValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantInitialValueContext ------------------------------------------------------------------

CactParser::ConstantInitialValueContext::ConstantInitialValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::ConstantExpressionContext* CactParser::ConstantInitialValueContext::constantExpression() {
  return getRuleContext<CactParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* CactParser::ConstantInitialValueContext::LeftBrace() {
  return getToken(CactParser::LeftBrace, 0);
}

tree::TerminalNode* CactParser::ConstantInitialValueContext::RightBrace() {
  return getToken(CactParser::RightBrace, 0);
}

std::vector<CactParser::ConstantInitialValueContext *> CactParser::ConstantInitialValueContext::constantInitialValue() {
  return getRuleContexts<CactParser::ConstantInitialValueContext>();
}

CactParser::ConstantInitialValueContext* CactParser::ConstantInitialValueContext::constantInitialValue(size_t i) {
  return getRuleContext<CactParser::ConstantInitialValueContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::ConstantInitialValueContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::ConstantInitialValueContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::ConstantInitialValueContext::getRuleIndex() const {
  return CactParser::RuleConstantInitialValue;
}


std::any CactParser::ConstantInitialValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantInitialValue(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantInitialValueContext* CactParser::constantInitialValue() {
  ConstantInitialValueContext *_localctx = _tracker.createInstance<ConstantInitialValueContext>(_ctx, getState());
  enterRule(_localctx, 10, CactParser::RuleConstantInitialValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(122);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant:
      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 1);
        setState(109);
        constantExpression();
        break;
      }

      case CactParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(110);
        match(CactParser::LeftBrace);
        setState(119);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 16493748158464) != 0)) {
          setState(111);
          constantInitialValue();
          setState(116);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CactParser::Comma) {
            setState(112);
            match(CactParser::Comma);
            setState(113);
            constantInitialValue();
            setState(118);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(121);
        match(CactParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

CactParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::BasicTypeContext* CactParser::VariableDeclarationContext::basicType() {
  return getRuleContext<CactParser::BasicTypeContext>(0);
}

std::vector<CactParser::VariableDefinitionContext *> CactParser::VariableDeclarationContext::variableDefinition() {
  return getRuleContexts<CactParser::VariableDefinitionContext>();
}

CactParser::VariableDefinitionContext* CactParser::VariableDeclarationContext::variableDefinition(size_t i) {
  return getRuleContext<CactParser::VariableDefinitionContext>(i);
}

tree::TerminalNode* CactParser::VariableDeclarationContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

std::vector<tree::TerminalNode *> CactParser::VariableDeclarationContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::VariableDeclarationContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::VariableDeclarationContext::getRuleIndex() const {
  return CactParser::RuleVariableDeclaration;
}


std::any CactParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CactParser::VariableDeclarationContext* CactParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, CactParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    basicType();
    setState(125);
    variableDefinition();
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(126);
      match(CactParser::Comma);
      setState(127);
      variableDefinition();
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(133);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDefinitionContext ------------------------------------------------------------------

CactParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::VariableDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CactParser::VariableDefinitionContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::VariableDefinitionContext::IntegerConstant() {
  return getTokens(CactParser::IntegerConstant);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::IntegerConstant(size_t i) {
  return getToken(CactParser::IntegerConstant, i);
}

std::vector<tree::TerminalNode *> CactParser::VariableDefinitionContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ConstantInitialValueContext* CactParser::VariableDefinitionContext::constantInitialValue() {
  return getRuleContext<CactParser::ConstantInitialValueContext>(0);
}


size_t CactParser::VariableDefinitionContext::getRuleIndex() const {
  return CactParser::RuleVariableDefinition;
}


std::any CactParser::VariableDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitVariableDefinition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::VariableDefinitionContext* CactParser::variableDefinition() {
  VariableDefinitionContext *_localctx = _tracker.createInstance<VariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 14, CactParser::RuleVariableDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    match(CactParser::Identifier);
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::LeftBracket) {
      setState(136);
      match(CactParser::LeftBracket);
      setState(137);
      match(CactParser::IntegerConstant);
      setState(138);
      match(CactParser::RightBracket);
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(146);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::Equal) {
      setState(144);
      match(CactParser::Equal);
      setState(145);
      constantInitialValue();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

CactParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::FunctionTypeContext* CactParser::FunctionDefinitionContext::functionType() {
  return getRuleContext<CactParser::FunctionTypeContext>(0);
}

tree::TerminalNode* CactParser::FunctionDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::FunctionDefinitionContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

tree::TerminalNode* CactParser::FunctionDefinitionContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::BlockContext* CactParser::FunctionDefinitionContext::block() {
  return getRuleContext<CactParser::BlockContext>(0);
}

CactParser::FunctionFormalParamsContext* CactParser::FunctionDefinitionContext::functionFormalParams() {
  return getRuleContext<CactParser::FunctionFormalParamsContext>(0);
}


size_t CactParser::FunctionDefinitionContext::getRuleIndex() const {
  return CactParser::RuleFunctionDefinition;
}


std::any CactParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionDefinitionContext* CactParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 16, CactParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    functionType();
    setState(149);
    match(CactParser::Identifier);
    setState(150);
    match(CactParser::LeftParenthesis);
    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30) != 0)) {
      setState(151);
      functionFormalParams();
    }
    setState(154);
    match(CactParser::RightParenthesis);
    setState(155);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

CactParser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::FunctionTypeContext::Void() {
  return getToken(CactParser::Void, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Int32() {
  return getToken(CactParser::Int32, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Float() {
  return getToken(CactParser::Float, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Double() {
  return getToken(CactParser::Double, 0);
}

tree::TerminalNode* CactParser::FunctionTypeContext::Bool() {
  return getToken(CactParser::Bool, 0);
}


size_t CactParser::FunctionTypeContext::getRuleIndex() const {
  return CactParser::RuleFunctionType;
}


std::any CactParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionTypeContext* CactParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, CactParser::RuleFunctionType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 62) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionFormalParamsContext ------------------------------------------------------------------

CactParser::FunctionFormalParamsContext::FunctionFormalParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CactParser::FunctionFormalParamContext *> CactParser::FunctionFormalParamsContext::functionFormalParam() {
  return getRuleContexts<CactParser::FunctionFormalParamContext>();
}

CactParser::FunctionFormalParamContext* CactParser::FunctionFormalParamsContext::functionFormalParam(size_t i) {
  return getRuleContext<CactParser::FunctionFormalParamContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParamsContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::FunctionFormalParamsContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::FunctionFormalParamsContext::getRuleIndex() const {
  return CactParser::RuleFunctionFormalParams;
}


std::any CactParser::FunctionFormalParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionFormalParams(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionFormalParamsContext* CactParser::functionFormalParams() {
  FunctionFormalParamsContext *_localctx = _tracker.createInstance<FunctionFormalParamsContext>(_ctx, getState());
  enterRule(_localctx, 20, CactParser::RuleFunctionFormalParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    functionFormalParam();
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(160);
      match(CactParser::Comma);
      setState(161);
      functionFormalParam();
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionFormalParamContext ------------------------------------------------------------------

CactParser::FunctionFormalParamContext::FunctionFormalParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::BasicTypeContext* CactParser::FunctionFormalParamContext::basicType() {
  return getRuleContext<CactParser::BasicTypeContext>(0);
}

tree::TerminalNode* CactParser::FunctionFormalParamContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParamContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::FunctionFormalParamContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParamContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::FunctionFormalParamContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionFormalParamContext::IntegerConstant() {
  return getTokens(CactParser::IntegerConstant);
}

tree::TerminalNode* CactParser::FunctionFormalParamContext::IntegerConstant(size_t i) {
  return getToken(CactParser::IntegerConstant, i);
}


size_t CactParser::FunctionFormalParamContext::getRuleIndex() const {
  return CactParser::RuleFunctionFormalParam;
}


std::any CactParser::FunctionFormalParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionFormalParam(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionFormalParamContext* CactParser::functionFormalParam() {
  FunctionFormalParamContext *_localctx = _tracker.createInstance<FunctionFormalParamContext>(_ctx, getState());
  enterRule(_localctx, 22, CactParser::RuleFunctionFormalParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    basicType();
    setState(168);
    match(CactParser::Identifier);
    setState(182);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::LeftBracket) {
      setState(169);
      match(CactParser::LeftBracket);
      setState(171);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CactParser::IntegerConstant) {
        setState(170);
        match(CactParser::IntegerConstant);
      }
      setState(173);
      match(CactParser::RightBracket);
      setState(179);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CactParser::LeftBracket) {
        setState(174);
        match(CactParser::LeftBracket);
        setState(175);
        match(CactParser::IntegerConstant);
        setState(176);
        match(CactParser::RightBracket);
        setState(181);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CactParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::BlockContext::LeftBrace() {
  return getToken(CactParser::LeftBrace, 0);
}

tree::TerminalNode* CactParser::BlockContext::RightBrace() {
  return getToken(CactParser::RightBrace, 0);
}

std::vector<CactParser::BlockItemContext *> CactParser::BlockContext::blockItem() {
  return getRuleContexts<CactParser::BlockItemContext>();
}

CactParser::BlockItemContext* CactParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<CactParser::BlockItemContext>(i);
}


size_t CactParser::BlockContext::getRuleIndex() const {
  return CactParser::RuleBlock;
}


std::any CactParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BlockContext* CactParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 24, CactParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(CactParser::LeftBrace);
    setState(188);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17090832506334) != 0)) {
      setState(185);
      blockItem();
      setState(190);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(191);
    match(CactParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

CactParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::DeclarationContext* CactParser::BlockItemContext::declaration() {
  return getRuleContext<CactParser::DeclarationContext>(0);
}

CactParser::StatementContext* CactParser::BlockItemContext::statement() {
  return getRuleContext<CactParser::StatementContext>(0);
}


size_t CactParser::BlockItemContext::getRuleIndex() const {
  return CactParser::RuleBlockItem;
}


std::any CactParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BlockItemContext* CactParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 26, CactParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::Int32:
      case CactParser::Float:
      case CactParser::Double:
      case CactParser::Bool:
      case CactParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(193);
        declaration();
        break;
      }

      case CactParser::Return:
      case CactParser::If:
      case CactParser::While:
      case CactParser::Break:
      case CactParser::Continue:
      case CactParser::Semicolon:
      case CactParser::LeftParenthesis:
      case CactParser::LeftBrace:
      case CactParser::Plus:
      case CactParser::Minus:
      case CactParser::ExclamationMark:
      case CactParser::Identifier:
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant:
      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(194);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CactParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::AssignStatementContext* CactParser::StatementContext::assignStatement() {
  return getRuleContext<CactParser::AssignStatementContext>(0);
}

CactParser::ExpressionStatementContext* CactParser::StatementContext::expressionStatement() {
  return getRuleContext<CactParser::ExpressionStatementContext>(0);
}

CactParser::BlockContext* CactParser::StatementContext::block() {
  return getRuleContext<CactParser::BlockContext>(0);
}

CactParser::ReturnStatementContext* CactParser::StatementContext::returnStatement() {
  return getRuleContext<CactParser::ReturnStatementContext>(0);
}

CactParser::IfStatementContext* CactParser::StatementContext::ifStatement() {
  return getRuleContext<CactParser::IfStatementContext>(0);
}

CactParser::WhileStatementContext* CactParser::StatementContext::whileStatement() {
  return getRuleContext<CactParser::WhileStatementContext>(0);
}

CactParser::BreakStatementContext* CactParser::StatementContext::breakStatement() {
  return getRuleContext<CactParser::BreakStatementContext>(0);
}

CactParser::ContinueStatementContext* CactParser::StatementContext::continueStatement() {
  return getRuleContext<CactParser::ContinueStatementContext>(0);
}


size_t CactParser::StatementContext::getRuleIndex() const {
  return CactParser::RuleStatement;
}


std::any CactParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::StatementContext* CactParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 28, CactParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(205);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(197);
      assignStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(198);
      expressionStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(199);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(200);
      returnStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(201);
      ifStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(202);
      whileStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(203);
      breakStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(204);
      continueStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignStatementContext ------------------------------------------------------------------

CactParser::AssignStatementContext::AssignStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::LeftValueContext* CactParser::AssignStatementContext::leftValue() {
  return getRuleContext<CactParser::LeftValueContext>(0);
}

tree::TerminalNode* CactParser::AssignStatementContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ExpressionContext* CactParser::AssignStatementContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}

tree::TerminalNode* CactParser::AssignStatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}


size_t CactParser::AssignStatementContext::getRuleIndex() const {
  return CactParser::RuleAssignStatement;
}


std::any CactParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::AssignStatementContext* CactParser::assignStatement() {
  AssignStatementContext *_localctx = _tracker.createInstance<AssignStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, CactParser::RuleAssignStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    leftValue();
    setState(208);
    match(CactParser::Equal);
    setState(209);
    expression();
    setState(210);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

CactParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ExpressionStatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

CactParser::ExpressionContext* CactParser::ExpressionStatementContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}


size_t CactParser::ExpressionStatementContext::getRuleIndex() const {
  return CactParser::RuleExpressionStatement;
}


std::any CactParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ExpressionStatementContext* CactParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, CactParser::RuleExpressionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17089741979648) != 0)) {
      setState(212);
      expression();
    }
    setState(215);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

CactParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ReturnStatementContext::Return() {
  return getToken(CactParser::Return, 0);
}

tree::TerminalNode* CactParser::ReturnStatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

CactParser::ExpressionContext* CactParser::ReturnStatementContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}


size_t CactParser::ReturnStatementContext::getRuleIndex() const {
  return CactParser::RuleReturnStatement;
}


std::any CactParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ReturnStatementContext* CactParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, CactParser::RuleReturnStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    match(CactParser::Return);
    setState(219);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 17089741979648) != 0)) {
      setState(218);
      expression();
    }
    setState(221);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

CactParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::IfStatementContext::If() {
  return getToken(CactParser::If, 0);
}

tree::TerminalNode* CactParser::IfStatementContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

CactParser::ConditionContext* CactParser::IfStatementContext::condition() {
  return getRuleContext<CactParser::ConditionContext>(0);
}

tree::TerminalNode* CactParser::IfStatementContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

std::vector<CactParser::StatementContext *> CactParser::IfStatementContext::statement() {
  return getRuleContexts<CactParser::StatementContext>();
}

CactParser::StatementContext* CactParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<CactParser::StatementContext>(i);
}

tree::TerminalNode* CactParser::IfStatementContext::Else() {
  return getToken(CactParser::Else, 0);
}


size_t CactParser::IfStatementContext::getRuleIndex() const {
  return CactParser::RuleIfStatement;
}


std::any CactParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::IfStatementContext* CactParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, CactParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(CactParser::If);
    setState(224);
    match(CactParser::LeftParenthesis);
    setState(225);
    condition();
    setState(226);
    match(CactParser::RightParenthesis);
    setState(227);
    statement();
    setState(230);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(228);
      match(CactParser::Else);
      setState(229);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

CactParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::WhileStatementContext::While() {
  return getToken(CactParser::While, 0);
}

tree::TerminalNode* CactParser::WhileStatementContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

CactParser::ConditionContext* CactParser::WhileStatementContext::condition() {
  return getRuleContext<CactParser::ConditionContext>(0);
}

tree::TerminalNode* CactParser::WhileStatementContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::StatementContext* CactParser::WhileStatementContext::statement() {
  return getRuleContext<CactParser::StatementContext>(0);
}


size_t CactParser::WhileStatementContext::getRuleIndex() const {
  return CactParser::RuleWhileStatement;
}


std::any CactParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::WhileStatementContext* CactParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 38, CactParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    match(CactParser::While);
    setState(233);
    match(CactParser::LeftParenthesis);
    setState(234);
    condition();
    setState(235);
    match(CactParser::RightParenthesis);
    setState(236);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

CactParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::BreakStatementContext::Break() {
  return getToken(CactParser::Break, 0);
}

tree::TerminalNode* CactParser::BreakStatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}


size_t CactParser::BreakStatementContext::getRuleIndex() const {
  return CactParser::RuleBreakStatement;
}


std::any CactParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::BreakStatementContext* CactParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 40, CactParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    match(CactParser::Break);
    setState(239);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

CactParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::ContinueStatementContext::Continue() {
  return getToken(CactParser::Continue, 0);
}

tree::TerminalNode* CactParser::ContinueStatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}


size_t CactParser::ContinueStatementContext::getRuleIndex() const {
  return CactParser::RuleContinueStatement;
}


std::any CactParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ContinueStatementContext* CactParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 42, CactParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(CactParser::Continue);
    setState(242);
    match(CactParser::Semicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CactParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::AddExpressionContext* CactParser::ExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}

tree::TerminalNode* CactParser::ExpressionContext::BooleanConstant() {
  return getToken(CactParser::BooleanConstant, 0);
}


size_t CactParser::ExpressionContext::getRuleIndex() const {
  return CactParser::RuleExpression;
}


std::any CactParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ExpressionContext* CactParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, CactParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::LeftParenthesis:
      case CactParser::Plus:
      case CactParser::Minus:
      case CactParser::ExclamationMark:
      case CactParser::Identifier:
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant: {
        enterOuterAlt(_localctx, 1);
        setState(244);
        addExpression(0);
        break;
      }

      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(245);
        match(CactParser::BooleanConstant);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

CactParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::NumberContext* CactParser::ConstantExpressionContext::number() {
  return getRuleContext<CactParser::NumberContext>(0);
}

tree::TerminalNode* CactParser::ConstantExpressionContext::BooleanConstant() {
  return getToken(CactParser::BooleanConstant, 0);
}


size_t CactParser::ConstantExpressionContext::getRuleIndex() const {
  return CactParser::RuleConstantExpression;
}


std::any CactParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConstantExpressionContext* CactParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, CactParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(250);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant: {
        enterOuterAlt(_localctx, 1);
        setState(248);
        number();
        break;
      }

      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(249);
        match(CactParser::BooleanConstant);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

CactParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::LogicalOrExpressionContext* CactParser::ConditionContext::logicalOrExpression() {
  return getRuleContext<CactParser::LogicalOrExpressionContext>(0);
}


size_t CactParser::ConditionContext::getRuleIndex() const {
  return CactParser::RuleCondition;
}


std::any CactParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

CactParser::ConditionContext* CactParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 48, CactParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    logicalOrExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LeftValueContext ------------------------------------------------------------------

CactParser::LeftValueContext::LeftValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::LeftValueContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CactParser::LeftValueContext::LeftBracket() {
  return getTokens(CactParser::LeftBracket);
}

tree::TerminalNode* CactParser::LeftValueContext::LeftBracket(size_t i) {
  return getToken(CactParser::LeftBracket, i);
}

std::vector<CactParser::ExpressionContext *> CactParser::LeftValueContext::expression() {
  return getRuleContexts<CactParser::ExpressionContext>();
}

CactParser::ExpressionContext* CactParser::LeftValueContext::expression(size_t i) {
  return getRuleContext<CactParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::LeftValueContext::RightBracket() {
  return getTokens(CactParser::RightBracket);
}

tree::TerminalNode* CactParser::LeftValueContext::RightBracket(size_t i) {
  return getToken(CactParser::RightBracket, i);
}


size_t CactParser::LeftValueContext::getRuleIndex() const {
  return CactParser::RuleLeftValue;
}


std::any CactParser::LeftValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLeftValue(this);
  else
    return visitor->visitChildren(this);
}

CactParser::LeftValueContext* CactParser::leftValue() {
  LeftValueContext *_localctx = _tracker.createInstance<LeftValueContext>(_ctx, getState());
  enterRule(_localctx, 50, CactParser::RuleLeftValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(254);
    match(CactParser::Identifier);
    setState(261);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(255);
        match(CactParser::LeftBracket);
        setState(256);
        expression();
        setState(257);
        match(CactParser::RightBracket); 
      }
      setState(263);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

CactParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::PrimaryExpressionContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

CactParser::ExpressionContext* CactParser::PrimaryExpressionContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}

tree::TerminalNode* CactParser::PrimaryExpressionContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::LeftValueContext* CactParser::PrimaryExpressionContext::leftValue() {
  return getRuleContext<CactParser::LeftValueContext>(0);
}

CactParser::NumberContext* CactParser::PrimaryExpressionContext::number() {
  return getRuleContext<CactParser::NumberContext>(0);
}


size_t CactParser::PrimaryExpressionContext::getRuleIndex() const {
  return CactParser::RulePrimaryExpression;
}


std::any CactParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::PrimaryExpressionContext* CactParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, CactParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::LeftParenthesis: {
        enterOuterAlt(_localctx, 1);
        setState(264);
        match(CactParser::LeftParenthesis);
        setState(265);
        expression();
        setState(266);
        match(CactParser::RightParenthesis);
        break;
      }

      case CactParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(268);
        leftValue();
        break;
      }

      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant: {
        enterOuterAlt(_localctx, 3);
        setState(269);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

CactParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::NumberContext::IntegerConstant() {
  return getToken(CactParser::IntegerConstant, 0);
}

tree::TerminalNode* CactParser::NumberContext::FloatConstant() {
  return getToken(CactParser::FloatConstant, 0);
}

tree::TerminalNode* CactParser::NumberContext::DoubleConstant() {
  return getToken(CactParser::DoubleConstant, 0);
}


size_t CactParser::NumberContext::getRuleIndex() const {
  return CactParser::RuleNumber;
}


std::any CactParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

CactParser::NumberContext* CactParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 54, CactParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7696581394432) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

CactParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::PrimaryExpressionContext* CactParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<CactParser::PrimaryExpressionContext>(0);
}

CactParser::UnaryExpressionContext* CactParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<CactParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::Plus() {
  return getToken(CactParser::Plus, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::Minus() {
  return getToken(CactParser::Minus, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::ExclamationMark() {
  return getToken(CactParser::ExclamationMark, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

tree::TerminalNode* CactParser::UnaryExpressionContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

CactParser::FunctionRealParamsContext* CactParser::UnaryExpressionContext::functionRealParams() {
  return getRuleContext<CactParser::FunctionRealParamsContext>(0);
}


size_t CactParser::UnaryExpressionContext::getRuleIndex() const {
  return CactParser::RuleUnaryExpression;
}


std::any CactParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CactParser::UnaryExpressionContext* CactParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 56, CactParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(283);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(274);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(275);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 47244640256) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(276);
      unaryExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(277);
      match(CactParser::Identifier);
      setState(278);
      match(CactParser::LeftParenthesis);
      setState(280);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 17089741979648) != 0)) {
        setState(279);
        functionRealParams();
      }
      setState(282);
      match(CactParser::RightParenthesis);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionRealParamsContext ------------------------------------------------------------------

CactParser::FunctionRealParamsContext::FunctionRealParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CactParser::ExpressionContext *> CactParser::FunctionRealParamsContext::expression() {
  return getRuleContexts<CactParser::ExpressionContext>();
}

CactParser::ExpressionContext* CactParser::FunctionRealParamsContext::expression(size_t i) {
  return getRuleContext<CactParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CactParser::FunctionRealParamsContext::Comma() {
  return getTokens(CactParser::Comma);
}

tree::TerminalNode* CactParser::FunctionRealParamsContext::Comma(size_t i) {
  return getToken(CactParser::Comma, i);
}


size_t CactParser::FunctionRealParamsContext::getRuleIndex() const {
  return CactParser::RuleFunctionRealParams;
}


std::any CactParser::FunctionRealParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitFunctionRealParams(this);
  else
    return visitor->visitChildren(this);
}

CactParser::FunctionRealParamsContext* CactParser::functionRealParams() {
  FunctionRealParamsContext *_localctx = _tracker.createInstance<FunctionRealParamsContext>(_ctx, getState());
  enterRule(_localctx, 58, CactParser::RuleFunctionRealParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(285);
    expression();
    setState(290);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(286);
      match(CactParser::Comma);
      setState(287);
      expression();
      setState(292);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpressionContext ------------------------------------------------------------------

CactParser::MulExpressionContext::MulExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::UnaryExpressionContext* CactParser::MulExpressionContext::unaryExpression() {
  return getRuleContext<CactParser::UnaryExpressionContext>(0);
}

CactParser::MulExpressionContext* CactParser::MulExpressionContext::mulExpression() {
  return getRuleContext<CactParser::MulExpressionContext>(0);
}

tree::TerminalNode* CactParser::MulExpressionContext::Asterisk() {
  return getToken(CactParser::Asterisk, 0);
}

tree::TerminalNode* CactParser::MulExpressionContext::Slash() {
  return getToken(CactParser::Slash, 0);
}

tree::TerminalNode* CactParser::MulExpressionContext::Percent() {
  return getToken(CactParser::Percent, 0);
}


size_t CactParser::MulExpressionContext::getRuleIndex() const {
  return CactParser::RuleMulExpression;
}


std::any CactParser::MulExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitMulExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::MulExpressionContext* CactParser::mulExpression() {
   return mulExpression(0);
}

CactParser::MulExpressionContext* CactParser::mulExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::MulExpressionContext *_localctx = _tracker.createInstance<MulExpressionContext>(_ctx, parentState);
  CactParser::MulExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, CactParser::RuleMulExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(294);
    unaryExpression();
    _ctx->stop = _input->LT(-1);
    setState(301);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulExpression);
        setState(296);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(297);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 481036337152) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(298);
        unaryExpression(); 
      }
      setState(303);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddExpressionContext ------------------------------------------------------------------

CactParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::MulExpressionContext* CactParser::AddExpressionContext::mulExpression() {
  return getRuleContext<CactParser::MulExpressionContext>(0);
}

CactParser::AddExpressionContext* CactParser::AddExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}

tree::TerminalNode* CactParser::AddExpressionContext::Plus() {
  return getToken(CactParser::Plus, 0);
}

tree::TerminalNode* CactParser::AddExpressionContext::Minus() {
  return getToken(CactParser::Minus, 0);
}


size_t CactParser::AddExpressionContext::getRuleIndex() const {
  return CactParser::RuleAddExpression;
}


std::any CactParser::AddExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitAddExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::AddExpressionContext* CactParser::addExpression() {
   return addExpression(0);
}

CactParser::AddExpressionContext* CactParser::addExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, parentState);
  CactParser::AddExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, CactParser::RuleAddExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(305);
    mulExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(312);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExpression);
        setState(307);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(308);
        _la = _input->LA(1);
        if (!(_la == CactParser::Plus

        || _la == CactParser::Minus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(309);
        mulExpression(0); 
      }
      setState(314);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

CactParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::AddExpressionContext* CactParser::RelationalExpressionContext::addExpression() {
  return getRuleContext<CactParser::AddExpressionContext>(0);
}

CactParser::RelationalExpressionContext* CactParser::RelationalExpressionContext::relationalExpression() {
  return getRuleContext<CactParser::RelationalExpressionContext>(0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::Less() {
  return getToken(CactParser::Less, 0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::LessEqual() {
  return getToken(CactParser::LessEqual, 0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::Greater() {
  return getToken(CactParser::Greater, 0);
}

tree::TerminalNode* CactParser::RelationalExpressionContext::GreaterEqual() {
  return getToken(CactParser::GreaterEqual, 0);
}


size_t CactParser::RelationalExpressionContext::getRuleIndex() const {
  return CactParser::RuleRelationalExpression;
}


std::any CactParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::RelationalExpressionContext* CactParser::relationalExpression() {
   return relationalExpression(0);
}

CactParser::RelationalExpressionContext* CactParser::relationalExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, parentState);
  CactParser::RelationalExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, CactParser::RuleRelationalExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(316);
    addExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(323);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
        setState(318);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(319);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 3932160) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(320);
        addExpression(0); 
      }
      setState(325);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalEqualExpressionContext ------------------------------------------------------------------

CactParser::LogicalEqualExpressionContext::LogicalEqualExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::RelationalExpressionContext* CactParser::LogicalEqualExpressionContext::relationalExpression() {
  return getRuleContext<CactParser::RelationalExpressionContext>(0);
}

CactParser::LogicalEqualExpressionContext* CactParser::LogicalEqualExpressionContext::logicalEqualExpression() {
  return getRuleContext<CactParser::LogicalEqualExpressionContext>(0);
}

tree::TerminalNode* CactParser::LogicalEqualExpressionContext::LogicalEqual() {
  return getToken(CactParser::LogicalEqual, 0);
}

tree::TerminalNode* CactParser::LogicalEqualExpressionContext::NotEqual() {
  return getToken(CactParser::NotEqual, 0);
}


size_t CactParser::LogicalEqualExpressionContext::getRuleIndex() const {
  return CactParser::RuleLogicalEqualExpression;
}


std::any CactParser::LogicalEqualExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLogicalEqualExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::LogicalEqualExpressionContext* CactParser::logicalEqualExpression() {
   return logicalEqualExpression(0);
}

CactParser::LogicalEqualExpressionContext* CactParser::logicalEqualExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::LogicalEqualExpressionContext *_localctx = _tracker.createInstance<LogicalEqualExpressionContext>(_ctx, parentState);
  CactParser::LogicalEqualExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 66;
  enterRecursionRule(_localctx, 66, CactParser::RuleLogicalEqualExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(327);
    relationalExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(334);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalEqualExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalEqualExpression);
        setState(329);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(330);
        _la = _input->LA(1);
        if (!(_la == CactParser::LogicalEqual

        || _la == CactParser::NotEqual)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(331);
        relationalExpression(0); 
      }
      setState(336);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

CactParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CactParser::LogicalEqualExpressionContext* CactParser::LogicalAndExpressionContext::logicalEqualExpression() {
  return getRuleContext<CactParser::LogicalEqualExpressionContext>(0);
}

CactParser::LogicalAndExpressionContext* CactParser::LogicalAndExpressionContext::logicalAndExpression() {
  return getRuleContext<CactParser::LogicalAndExpressionContext>(0);
}

tree::TerminalNode* CactParser::LogicalAndExpressionContext::LogicalAnd() {
  return getToken(CactParser::LogicalAnd, 0);
}


size_t CactParser::LogicalAndExpressionContext::getRuleIndex() const {
  return CactParser::RuleLogicalAndExpression;
}


std::any CactParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::LogicalAndExpressionContext* CactParser::logicalAndExpression() {
   return logicalAndExpression(0);
}

CactParser::LogicalAndExpressionContext* CactParser::logicalAndExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, parentState);
  CactParser::LogicalAndExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 68;
  enterRecursionRule(_localctx, 68, CactParser::RuleLogicalAndExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(338);
    logicalEqualExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(345);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalAndExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalAndExpression);
        setState(340);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(341);
        match(CactParser::LogicalAnd);
        setState(342);
        logicalEqualExpression(0); 
      }
      setState(347);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

CactParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::LogicalOrExpressionContext::BooleanConstant() {
  return getToken(CactParser::BooleanConstant, 0);
}

CactParser::LogicalAndExpressionContext* CactParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContext<CactParser::LogicalAndExpressionContext>(0);
}

CactParser::LogicalOrExpressionContext* CactParser::LogicalOrExpressionContext::logicalOrExpression() {
  return getRuleContext<CactParser::LogicalOrExpressionContext>(0);
}

tree::TerminalNode* CactParser::LogicalOrExpressionContext::LogicalOr() {
  return getToken(CactParser::LogicalOr, 0);
}


size_t CactParser::LogicalOrExpressionContext::getRuleIndex() const {
  return CactParser::RuleLogicalOrExpression;
}


std::any CactParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CactParserVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}


CactParser::LogicalOrExpressionContext* CactParser::logicalOrExpression() {
   return logicalOrExpression(0);
}

CactParser::LogicalOrExpressionContext* CactParser::logicalOrExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CactParser::LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, parentState);
  CactParser::LogicalOrExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 70;
  enterRecursionRule(_localctx, 70, CactParser::RuleLogicalOrExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(351);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::BooleanConstant: {
        setState(349);
        match(CactParser::BooleanConstant);
        break;
      }

      case CactParser::LeftParenthesis:
      case CactParser::Plus:
      case CactParser::Minus:
      case CactParser::ExclamationMark:
      case CactParser::Identifier:
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant: {
        setState(350);
        logicalAndExpression(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(358);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalOrExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalOrExpression);
        setState(353);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(354);
        match(CactParser::LogicalOr);
        setState(355);
        logicalAndExpression(0); 
      }
      setState(360);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CactParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 30: return mulExpressionSempred(antlrcpp::downCast<MulExpressionContext *>(context), predicateIndex);
    case 31: return addExpressionSempred(antlrcpp::downCast<AddExpressionContext *>(context), predicateIndex);
    case 32: return relationalExpressionSempred(antlrcpp::downCast<RelationalExpressionContext *>(context), predicateIndex);
    case 33: return logicalEqualExpressionSempred(antlrcpp::downCast<LogicalEqualExpressionContext *>(context), predicateIndex);
    case 34: return logicalAndExpressionSempred(antlrcpp::downCast<LogicalAndExpressionContext *>(context), predicateIndex);
    case 35: return logicalOrExpressionSempred(antlrcpp::downCast<LogicalOrExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CactParser::mulExpressionSempred(MulExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::addExpressionSempred(AddExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::relationalExpressionSempred(RelationalExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::logicalEqualExpressionSempred(LogicalEqualExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::logicalAndExpressionSempred(LogicalAndExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CactParser::logicalOrExpressionSempred(LogicalOrExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void CactParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cactparserParserInitialize();
#else
  ::antlr4::internal::call_once(cactparserParserOnceFlag, cactparserParserInitialize);
#endif
}
