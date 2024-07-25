
// Generated from ./grammar/CactParser.g4 by ANTLR 4.13.1


#include "CactParserVisitor.h"

#include "CactParser.h"


using namespace antlrcpp;
using namespace cactparser;

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
      "compilationUnit", "basicType", "declaration", "variableDefinition", 
      "variableDeclaration", "constantDeclaration", "constantDefinition", 
      "constantInitialValue", "functionDefinition", "functionType", "functionFormalParams", 
      "functionFormalParam", "block", "blockItem", "statement", "expression", 
      "constantExpression", "condition", "leftValue", "primaryExpression", 
      "number", "unaryExpression", "functionRealParams", "mulExpression", 
      "addExpression", "relationalExpression", "logicalEqualExpression", 
      "logicalAndExpression", "logicalOrExpression"
    },
    std::vector<std::string>{
      "", "'int'", "'float'", "'double'", "'bool'", "'void'", "'const'", 
      "'true'", "'false'", "'return'", "'if'", "'else'", "'while'", "'break'", 
      "'continue'", "'='", "'=='", "'&&'", "'||'", "'!='", "'<'", "'<='", 
      "'>'", "'>='", "'.'", "','", "';'", "':'", "'('", "')'", "'['", "']'", 
      "'{'", "'}'", "'+'", "'-'", "'|'", "'!'", "'*'", "'/'", "'%'"
    },
    std::vector<std::string>{
      "", "Int", "Float", "Double", "Bool", "Void", "Const", "True", "False", 
      "Return", "If", "Else", "While", "Break", "Continue", "Equal", "LogicalEqual", 
      "LogicalAnd", "LogicalOr", "NotEqual", "Less", "LessEqual", "Greater", 
      "GreaterEqual", "Period", "Comma", "Semicolon", "Colon", "LeftParenthesis", 
      "RightParenthesis", "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", 
      "Plus", "Minus", "Pipe", "ExclamationMark", "Asterisk", "Slash", "Percent", 
      "Identifier", "DecimalConstant", "OctalConstant", "HexadecimalConstant", 
      "IntegerConstant", "FloatConstant", "DoubleConstant", "BooleanConstant", 
      "LineComment", "BlockComment", "NewLine", "WhiteSpaces"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,52,326,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,1,0,1,0,5,0,61,8,0,10,0,12,0,64,9,0,1,1,1,1,1,2,1,2,3,2,70,8,2,1,3,
  	1,3,1,3,1,3,3,3,76,8,3,1,3,1,3,3,3,80,8,3,1,4,1,4,1,4,1,4,5,4,86,8,4,
  	10,4,12,4,89,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,98,8,5,10,5,12,5,101,
  	9,5,1,5,1,5,1,6,1,6,1,6,1,6,3,6,109,8,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,
  	7,5,7,119,8,7,10,7,12,7,122,9,7,3,7,124,8,7,1,7,3,7,127,8,7,1,8,1,8,1,
  	8,1,8,3,8,133,8,8,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,10,3,10,143,8,10,1,
  	11,1,11,1,11,1,11,3,11,149,8,11,1,11,1,11,1,11,1,11,5,11,155,8,11,10,
  	11,12,11,158,9,11,3,11,160,8,11,1,12,1,12,5,12,164,8,12,10,12,12,12,167,
  	9,12,1,12,1,12,1,13,1,13,3,13,173,8,13,1,14,1,14,1,14,1,14,1,14,1,14,
  	3,14,181,8,14,1,14,1,14,1,14,1,14,3,14,187,8,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,3,14,197,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,3,14,209,8,14,1,15,1,15,3,15,213,8,15,1,16,1,16,3,16,217,
  	8,16,1,17,1,17,1,18,1,18,1,18,1,18,1,18,5,18,226,8,18,10,18,12,18,229,
  	9,18,1,19,1,19,1,19,1,19,1,19,1,19,3,19,237,8,19,1,20,1,20,1,21,1,21,
  	1,21,1,21,1,21,1,21,3,21,247,8,21,1,21,3,21,250,8,21,1,22,1,22,1,22,5,
  	22,255,8,22,10,22,12,22,258,9,22,1,23,1,23,1,23,1,23,1,23,1,23,5,23,266,
  	8,23,10,23,12,23,269,9,23,1,24,1,24,1,24,1,24,1,24,1,24,5,24,277,8,24,
  	10,24,12,24,280,9,24,1,25,1,25,1,25,1,25,1,25,1,25,5,25,288,8,25,10,25,
  	12,25,291,9,25,1,26,1,26,1,26,1,26,1,26,1,26,5,26,299,8,26,10,26,12,26,
  	302,9,26,1,27,1,27,1,27,1,27,1,27,1,27,5,27,310,8,27,10,27,12,27,313,
  	9,27,1,28,1,28,1,28,1,28,1,28,1,28,5,28,321,8,28,10,28,12,28,324,9,28,
  	1,28,0,6,46,48,50,52,54,56,29,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,52,54,56,0,8,1,0,1,4,1,0,1,5,1,0,45,
  	47,2,0,34,35,37,37,1,0,38,40,1,0,34,35,1,0,20,23,2,0,16,16,19,19,339,
  	0,62,1,0,0,0,2,65,1,0,0,0,4,69,1,0,0,0,6,71,1,0,0,0,8,81,1,0,0,0,10,92,
  	1,0,0,0,12,104,1,0,0,0,14,126,1,0,0,0,16,128,1,0,0,0,18,137,1,0,0,0,20,
  	139,1,0,0,0,22,144,1,0,0,0,24,161,1,0,0,0,26,172,1,0,0,0,28,208,1,0,0,
  	0,30,212,1,0,0,0,32,216,1,0,0,0,34,218,1,0,0,0,36,220,1,0,0,0,38,236,
  	1,0,0,0,40,238,1,0,0,0,42,249,1,0,0,0,44,251,1,0,0,0,46,259,1,0,0,0,48,
  	270,1,0,0,0,50,281,1,0,0,0,52,292,1,0,0,0,54,303,1,0,0,0,56,314,1,0,0,
  	0,58,61,3,4,2,0,59,61,3,16,8,0,60,58,1,0,0,0,60,59,1,0,0,0,61,64,1,0,
  	0,0,62,60,1,0,0,0,62,63,1,0,0,0,63,1,1,0,0,0,64,62,1,0,0,0,65,66,7,0,
  	0,0,66,3,1,0,0,0,67,70,3,10,5,0,68,70,3,8,4,0,69,67,1,0,0,0,69,68,1,0,
  	0,0,70,5,1,0,0,0,71,75,5,41,0,0,72,73,5,30,0,0,73,74,5,45,0,0,74,76,5,
  	31,0,0,75,72,1,0,0,0,75,76,1,0,0,0,76,79,1,0,0,0,77,78,5,15,0,0,78,80,
  	3,32,16,0,79,77,1,0,0,0,79,80,1,0,0,0,80,7,1,0,0,0,81,82,3,2,1,0,82,87,
  	3,6,3,0,83,84,5,25,0,0,84,86,3,6,3,0,85,83,1,0,0,0,86,89,1,0,0,0,87,85,
  	1,0,0,0,87,88,1,0,0,0,88,90,1,0,0,0,89,87,1,0,0,0,90,91,5,26,0,0,91,9,
  	1,0,0,0,92,93,5,6,0,0,93,94,3,2,1,0,94,99,3,12,6,0,95,96,5,25,0,0,96,
  	98,3,12,6,0,97,95,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,0,99,100,1,0,0,0,
  	100,102,1,0,0,0,101,99,1,0,0,0,102,103,5,26,0,0,103,11,1,0,0,0,104,108,
  	5,41,0,0,105,106,5,30,0,0,106,107,5,45,0,0,107,109,5,31,0,0,108,105,1,
  	0,0,0,108,109,1,0,0,0,109,110,1,0,0,0,110,111,5,15,0,0,111,112,3,14,7,
  	0,112,13,1,0,0,0,113,127,3,32,16,0,114,123,5,32,0,0,115,120,3,14,7,0,
  	116,117,5,25,0,0,117,119,3,14,7,0,118,116,1,0,0,0,119,122,1,0,0,0,120,
  	118,1,0,0,0,120,121,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,123,115,1,
  	0,0,0,123,124,1,0,0,0,124,125,1,0,0,0,125,127,5,33,0,0,126,113,1,0,0,
  	0,126,114,1,0,0,0,127,15,1,0,0,0,128,129,3,18,9,0,129,130,5,41,0,0,130,
  	132,5,28,0,0,131,133,3,20,10,0,132,131,1,0,0,0,132,133,1,0,0,0,133,134,
  	1,0,0,0,134,135,5,29,0,0,135,136,3,24,12,0,136,17,1,0,0,0,137,138,7,1,
  	0,0,138,19,1,0,0,0,139,142,3,22,11,0,140,141,5,25,0,0,141,143,3,22,11,
  	0,142,140,1,0,0,0,142,143,1,0,0,0,143,21,1,0,0,0,144,145,3,2,1,0,145,
  	159,5,41,0,0,146,148,5,30,0,0,147,149,5,45,0,0,148,147,1,0,0,0,148,149,
  	1,0,0,0,149,150,1,0,0,0,150,156,5,31,0,0,151,152,5,30,0,0,152,153,5,45,
  	0,0,153,155,5,31,0,0,154,151,1,0,0,0,155,158,1,0,0,0,156,154,1,0,0,0,
  	156,157,1,0,0,0,157,160,1,0,0,0,158,156,1,0,0,0,159,146,1,0,0,0,159,160,
  	1,0,0,0,160,23,1,0,0,0,161,165,5,32,0,0,162,164,3,26,13,0,163,162,1,0,
  	0,0,164,167,1,0,0,0,165,163,1,0,0,0,165,166,1,0,0,0,166,168,1,0,0,0,167,
  	165,1,0,0,0,168,169,5,33,0,0,169,25,1,0,0,0,170,173,3,4,2,0,171,173,3,
  	28,14,0,172,170,1,0,0,0,172,171,1,0,0,0,173,27,1,0,0,0,174,175,3,36,18,
  	0,175,176,5,15,0,0,176,177,3,30,15,0,177,178,5,26,0,0,178,209,1,0,0,0,
  	179,181,3,30,15,0,180,179,1,0,0,0,180,181,1,0,0,0,181,182,1,0,0,0,182,
  	209,5,26,0,0,183,209,3,24,12,0,184,186,5,9,0,0,185,187,3,30,15,0,186,
  	185,1,0,0,0,186,187,1,0,0,0,187,188,1,0,0,0,188,209,5,26,0,0,189,190,
  	5,10,0,0,190,191,5,28,0,0,191,192,3,34,17,0,192,193,5,29,0,0,193,196,
  	3,28,14,0,194,195,5,11,0,0,195,197,3,28,14,0,196,194,1,0,0,0,196,197,
  	1,0,0,0,197,209,1,0,0,0,198,199,5,12,0,0,199,200,5,28,0,0,200,201,3,34,
  	17,0,201,202,5,29,0,0,202,203,3,28,14,0,203,209,1,0,0,0,204,205,5,13,
  	0,0,205,209,5,26,0,0,206,207,5,14,0,0,207,209,5,26,0,0,208,174,1,0,0,
  	0,208,180,1,0,0,0,208,183,1,0,0,0,208,184,1,0,0,0,208,189,1,0,0,0,208,
  	198,1,0,0,0,208,204,1,0,0,0,208,206,1,0,0,0,209,29,1,0,0,0,210,213,3,
  	48,24,0,211,213,5,48,0,0,212,210,1,0,0,0,212,211,1,0,0,0,213,31,1,0,0,
  	0,214,217,3,40,20,0,215,217,5,48,0,0,216,214,1,0,0,0,216,215,1,0,0,0,
  	217,33,1,0,0,0,218,219,3,56,28,0,219,35,1,0,0,0,220,227,5,41,0,0,221,
  	222,5,30,0,0,222,223,3,30,15,0,223,224,5,31,0,0,224,226,1,0,0,0,225,221,
  	1,0,0,0,226,229,1,0,0,0,227,225,1,0,0,0,227,228,1,0,0,0,228,37,1,0,0,
  	0,229,227,1,0,0,0,230,231,5,28,0,0,231,232,3,30,15,0,232,233,5,29,0,0,
  	233,237,1,0,0,0,234,237,3,36,18,0,235,237,3,40,20,0,236,230,1,0,0,0,236,
  	234,1,0,0,0,236,235,1,0,0,0,237,39,1,0,0,0,238,239,7,2,0,0,239,41,1,0,
  	0,0,240,250,3,38,19,0,241,242,7,3,0,0,242,250,3,42,21,0,243,244,5,41,
  	0,0,244,246,5,28,0,0,245,247,3,44,22,0,246,245,1,0,0,0,246,247,1,0,0,
  	0,247,248,1,0,0,0,248,250,5,29,0,0,249,240,1,0,0,0,249,241,1,0,0,0,249,
  	243,1,0,0,0,250,43,1,0,0,0,251,256,3,30,15,0,252,253,5,25,0,0,253,255,
  	3,30,15,0,254,252,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,256,257,1,0,
  	0,0,257,45,1,0,0,0,258,256,1,0,0,0,259,260,6,23,-1,0,260,261,3,42,21,
  	0,261,267,1,0,0,0,262,263,10,1,0,0,263,264,7,4,0,0,264,266,3,42,21,0,
  	265,262,1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,268,47,
  	1,0,0,0,269,267,1,0,0,0,270,271,6,24,-1,0,271,272,3,46,23,0,272,278,1,
  	0,0,0,273,274,10,1,0,0,274,275,7,5,0,0,275,277,3,46,23,0,276,273,1,0,
  	0,0,277,280,1,0,0,0,278,276,1,0,0,0,278,279,1,0,0,0,279,49,1,0,0,0,280,
  	278,1,0,0,0,281,282,6,25,-1,0,282,283,3,48,24,0,283,289,1,0,0,0,284,285,
  	10,1,0,0,285,286,7,6,0,0,286,288,3,48,24,0,287,284,1,0,0,0,288,291,1,
  	0,0,0,289,287,1,0,0,0,289,290,1,0,0,0,290,51,1,0,0,0,291,289,1,0,0,0,
  	292,293,6,26,-1,0,293,294,3,50,25,0,294,300,1,0,0,0,295,296,10,1,0,0,
  	296,297,7,7,0,0,297,299,3,50,25,0,298,295,1,0,0,0,299,302,1,0,0,0,300,
  	298,1,0,0,0,300,301,1,0,0,0,301,53,1,0,0,0,302,300,1,0,0,0,303,304,6,
  	27,-1,0,304,305,3,52,26,0,305,311,1,0,0,0,306,307,10,1,0,0,307,308,5,
  	17,0,0,308,310,3,52,26,0,309,306,1,0,0,0,310,313,1,0,0,0,311,309,1,0,
  	0,0,311,312,1,0,0,0,312,55,1,0,0,0,313,311,1,0,0,0,314,315,6,28,-1,0,
  	315,316,3,54,27,0,316,322,1,0,0,0,317,318,10,1,0,0,318,319,5,18,0,0,319,
  	321,3,54,27,0,320,317,1,0,0,0,321,324,1,0,0,0,322,320,1,0,0,0,322,323,
  	1,0,0,0,323,57,1,0,0,0,324,322,1,0,0,0,35,60,62,69,75,79,87,99,108,120,
  	123,126,132,142,148,156,159,165,172,180,186,196,208,212,216,227,236,246,
  	249,256,267,278,289,300,311,322
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
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 126) != 0)) {
      setState(60);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(58);
        declaration();
        break;
      }

      case 2: {
        setState(59);
        functionDefinition();
        break;
      }

      default:
        break;
      }
      setState(64);
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

//----------------- BasicTypeContext ------------------------------------------------------------------

CactParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::BasicTypeContext::Int() {
  return getToken(CactParser::Int, 0);
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
  enterRule(_localctx, 2, CactParser::RuleBasicType);
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
    setState(65);
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
  enterRule(_localctx, 4, CactParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(69);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(67);
        constantDeclaration();
        break;
      }

      case CactParser::Int:
      case CactParser::Float:
      case CactParser::Double:
      case CactParser::Bool: {
        enterOuterAlt(_localctx, 2);
        setState(68);
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

//----------------- VariableDefinitionContext ------------------------------------------------------------------

CactParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CactParser::VariableDefinitionContext::Identifier() {
  return getToken(CactParser::Identifier, 0);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::LeftBracket() {
  return getToken(CactParser::LeftBracket, 0);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::IntegerConstant() {
  return getToken(CactParser::IntegerConstant, 0);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::RightBracket() {
  return getToken(CactParser::RightBracket, 0);
}

tree::TerminalNode* CactParser::VariableDefinitionContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ConstantExpressionContext* CactParser::VariableDefinitionContext::constantExpression() {
  return getRuleContext<CactParser::ConstantExpressionContext>(0);
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
  enterRule(_localctx, 6, CactParser::RuleVariableDefinition);
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
    setState(71);
    match(CactParser::Identifier);
    setState(75);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::LeftBracket) {
      setState(72);
      match(CactParser::LeftBracket);
      setState(73);
      match(CactParser::IntegerConstant);
      setState(74);
      match(CactParser::RightBracket);
    }
    setState(79);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::Equal) {
      setState(77);
      match(CactParser::Equal);
      setState(78);
      constantExpression();
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
  enterRule(_localctx, 8, CactParser::RuleVariableDeclaration);
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
    setState(81);
    basicType();
    setState(82);
    variableDefinition();
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(83);
      match(CactParser::Comma);
      setState(84);
      variableDefinition();
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(90);
    match(CactParser::Semicolon);
   
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
  enterRule(_localctx, 10, CactParser::RuleConstantDeclaration);
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
    setState(92);
    match(CactParser::Const);
    setState(93);
    basicType();
    setState(94);
    constantDefinition();
    setState(99);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(95);
      match(CactParser::Comma);
      setState(96);
      constantDefinition();
      setState(101);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(102);
    match(CactParser::Semicolon);
   
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

tree::TerminalNode* CactParser::ConstantDefinitionContext::LeftBracket() {
  return getToken(CactParser::LeftBracket, 0);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::IntegerConstant() {
  return getToken(CactParser::IntegerConstant, 0);
}

tree::TerminalNode* CactParser::ConstantDefinitionContext::RightBracket() {
  return getToken(CactParser::RightBracket, 0);
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
  enterRule(_localctx, 12, CactParser::RuleConstantDefinition);
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
    setState(104);
    match(CactParser::Identifier);
    setState(108);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::LeftBracket) {
      setState(105);
      match(CactParser::LeftBracket);
      setState(106);
      match(CactParser::IntegerConstant);
      setState(107);
      match(CactParser::RightBracket);
    }
    setState(110);
    match(CactParser::Equal);
    setState(111);
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
  enterRule(_localctx, 14, CactParser::RuleConstantInitialValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(126);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant:
      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 1);
        setState(113);
        constantExpression();
        break;
      }

      case CactParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(114);
        match(CactParser::LeftBrace);
        setState(123);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 527769876299776) != 0)) {
          setState(115);
          constantInitialValue();
          setState(120);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CactParser::Comma) {
            setState(116);
            match(CactParser::Comma);
            setState(117);
            constantInitialValue();
            setState(122);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(125);
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
    setState(128);
    functionType();
    setState(129);
    match(CactParser::Identifier);
    setState(130);
    match(CactParser::LeftParenthesis);
    setState(132);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30) != 0)) {
      setState(131);
      functionFormalParams();
    }
    setState(134);
    match(CactParser::RightParenthesis);
    setState(135);
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

tree::TerminalNode* CactParser::FunctionTypeContext::Int() {
  return getToken(CactParser::Int, 0);
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
    setState(137);
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

tree::TerminalNode* CactParser::FunctionFormalParamsContext::Comma() {
  return getToken(CactParser::Comma, 0);
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
    setState(139);
    functionFormalParam();
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::Comma) {
      setState(140);
      match(CactParser::Comma);
      setState(141);
      functionFormalParam();
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
    setState(144);
    basicType();
    setState(145);
    match(CactParser::Identifier);
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CactParser::LeftBracket) {
      setState(146);
      match(CactParser::LeftBracket);
      setState(148);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CactParser::IntegerConstant) {
        setState(147);
        match(CactParser::IntegerConstant);
      }
      setState(150);
      match(CactParser::RightBracket);
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CactParser::LeftBracket) {
        setState(151);
        match(CactParser::LeftBracket);
        setState(152);
        match(CactParser::IntegerConstant);
        setState(153);
        match(CactParser::RightBracket);
        setState(158);
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
    setState(161);
    match(CactParser::LeftBrace);
    setState(165);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 530158213690974) != 0)) {
      setState(162);
      blockItem();
      setState(167);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(168);
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
    setState(172);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::Int:
      case CactParser::Float:
      case CactParser::Double:
      case CactParser::Bool:
      case CactParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(170);
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
        setState(171);
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

CactParser::LeftValueContext* CactParser::StatementContext::leftValue() {
  return getRuleContext<CactParser::LeftValueContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::Equal() {
  return getToken(CactParser::Equal, 0);
}

CactParser::ExpressionContext* CactParser::StatementContext::expression() {
  return getRuleContext<CactParser::ExpressionContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::Semicolon() {
  return getToken(CactParser::Semicolon, 0);
}

CactParser::BlockContext* CactParser::StatementContext::block() {
  return getRuleContext<CactParser::BlockContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::Return() {
  return getToken(CactParser::Return, 0);
}

tree::TerminalNode* CactParser::StatementContext::If() {
  return getToken(CactParser::If, 0);
}

tree::TerminalNode* CactParser::StatementContext::LeftParenthesis() {
  return getToken(CactParser::LeftParenthesis, 0);
}

CactParser::ConditionContext* CactParser::StatementContext::condition() {
  return getRuleContext<CactParser::ConditionContext>(0);
}

tree::TerminalNode* CactParser::StatementContext::RightParenthesis() {
  return getToken(CactParser::RightParenthesis, 0);
}

std::vector<CactParser::StatementContext *> CactParser::StatementContext::statement() {
  return getRuleContexts<CactParser::StatementContext>();
}

CactParser::StatementContext* CactParser::StatementContext::statement(size_t i) {
  return getRuleContext<CactParser::StatementContext>(i);
}

tree::TerminalNode* CactParser::StatementContext::Else() {
  return getToken(CactParser::Else, 0);
}

tree::TerminalNode* CactParser::StatementContext::While() {
  return getToken(CactParser::While, 0);
}

tree::TerminalNode* CactParser::StatementContext::Break() {
  return getToken(CactParser::Break, 0);
}

tree::TerminalNode* CactParser::StatementContext::Continue() {
  return getToken(CactParser::Continue, 0);
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
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(208);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(174);
      leftValue();
      setState(175);
      match(CactParser::Equal);
      setState(176);
      expression();
      setState(177);
      match(CactParser::Semicolon);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(180);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 530153851584512) != 0)) {
        setState(179);
        expression();
      }
      setState(182);
      match(CactParser::Semicolon);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(183);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(184);
      match(CactParser::Return);
      setState(186);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 530153851584512) != 0)) {
        setState(185);
        expression();
      }
      setState(188);
      match(CactParser::Semicolon);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(189);
      match(CactParser::If);
      setState(190);
      match(CactParser::LeftParenthesis);
      setState(191);
      condition();
      setState(192);
      match(CactParser::RightParenthesis);
      setState(193);
      statement();
      setState(196);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(194);
        match(CactParser::Else);
        setState(195);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(198);
      match(CactParser::While);
      setState(199);
      match(CactParser::LeftParenthesis);
      setState(200);
      condition();
      setState(201);
      match(CactParser::RightParenthesis);
      setState(202);
      statement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(204);
      match(CactParser::Break);
      setState(205);
      match(CactParser::Semicolon);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(206);
      match(CactParser::Continue);
      setState(207);
      match(CactParser::Semicolon);
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
  enterRule(_localctx, 30, CactParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(212);
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
        setState(210);
        addExpression(0);
        break;
      }

      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(211);
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
  enterRule(_localctx, 32, CactParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(216);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant: {
        enterOuterAlt(_localctx, 1);
        setState(214);
        number();
        break;
      }

      case CactParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(215);
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
  enterRule(_localctx, 34, CactParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
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
  enterRule(_localctx, 36, CactParser::RuleLeftValue);

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
    setState(220);
    match(CactParser::Identifier);
    setState(227);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(221);
        match(CactParser::LeftBracket);
        setState(222);
        expression();
        setState(223);
        match(CactParser::RightBracket); 
      }
      setState(229);
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
  enterRule(_localctx, 38, CactParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(236);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CactParser::LeftParenthesis: {
        enterOuterAlt(_localctx, 1);
        setState(230);
        match(CactParser::LeftParenthesis);
        setState(231);
        expression();
        setState(232);
        match(CactParser::RightParenthesis);
        break;
      }

      case CactParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(234);
        leftValue();
        break;
      }

      case CactParser::IntegerConstant:
      case CactParser::FloatConstant:
      case CactParser::DoubleConstant: {
        enterOuterAlt(_localctx, 3);
        setState(235);
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
  enterRule(_localctx, 40, CactParser::RuleNumber);
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
    setState(238);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 246290604621824) != 0))) {
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
  enterRule(_localctx, 42, CactParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(249);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(240);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(241);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 188978561024) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(242);
      unaryExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(243);
      match(CactParser::Identifier);
      setState(244);
      match(CactParser::LeftParenthesis);
      setState(246);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 530153851584512) != 0)) {
        setState(245);
        functionRealParams();
      }
      setState(248);
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
  enterRule(_localctx, 44, CactParser::RuleFunctionRealParams);
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
    setState(251);
    expression();
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CactParser::Comma) {
      setState(252);
      match(CactParser::Comma);
      setState(253);
      expression();
      setState(258);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CactParser::RuleMulExpression, precedence);

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
    setState(260);
    unaryExpression();
    _ctx->stop = _input->LT(-1);
    setState(267);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulExpression);
        setState(262);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(263);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 1924145348608) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(264);
        unaryExpression(); 
      }
      setState(269);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CactParser::RuleAddExpression, precedence);

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
    setState(271);
    mulExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(278);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExpression);
        setState(273);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(274);
        _la = _input->LA(1);
        if (!(_la == CactParser::Plus

        || _la == CactParser::Minus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(275);
        mulExpression(0); 
      }
      setState(280);
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
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CactParser::RuleRelationalExpression, precedence);

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
    setState(282);
    addExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(289);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelationalExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelationalExpression);
        setState(284);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(285);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 15728640) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(286);
        addExpression(0); 
      }
      setState(291);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CactParser::RuleLogicalEqualExpression, precedence);

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
    setState(293);
    relationalExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(300);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalEqualExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalEqualExpression);
        setState(295);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(296);
        _la = _input->LA(1);
        if (!(_la == CactParser::LogicalEqual

        || _la == CactParser::NotEqual)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(297);
        relationalExpression(0); 
      }
      setState(302);
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
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CactParser::RuleLogicalAndExpression, precedence);

    

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
    setState(304);
    logicalEqualExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(311);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalAndExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalAndExpression);
        setState(306);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(307);
        match(CactParser::LogicalAnd);
        setState(308);
        logicalEqualExpression(0); 
      }
      setState(313);
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
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CactParser::RuleLogicalOrExpression, precedence);

    

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
    setState(315);
    logicalAndExpression(0);
    _ctx->stop = _input->LT(-1);
    setState(322);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LogicalOrExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLogicalOrExpression);
        setState(317);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(318);
        match(CactParser::LogicalOr);
        setState(319);
        logicalAndExpression(0); 
      }
      setState(324);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
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
    case 23: return mulExpressionSempred(antlrcpp::downCast<MulExpressionContext *>(context), predicateIndex);
    case 24: return addExpressionSempred(antlrcpp::downCast<AddExpressionContext *>(context), predicateIndex);
    case 25: return relationalExpressionSempred(antlrcpp::downCast<RelationalExpressionContext *>(context), predicateIndex);
    case 26: return logicalEqualExpressionSempred(antlrcpp::downCast<LogicalEqualExpressionContext *>(context), predicateIndex);
    case 27: return logicalAndExpressionSempred(antlrcpp::downCast<LogicalAndExpressionContext *>(context), predicateIndex);
    case 28: return logicalOrExpressionSempred(antlrcpp::downCast<LogicalOrExpressionContext *>(context), predicateIndex);

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
