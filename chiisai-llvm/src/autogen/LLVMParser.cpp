
    #include <optional>
    #include <memory>
    #include <variant>
    #include <chiisai-llvm/ref.h>
    #include <chiisai-llvm/type.h>
    #include <chiisai-llvm/basic-block.h>


// Generated from ./grammar/LLVMParser.g4 by ANTLR 4.13.1


#include "LLVMParserVisitor.h"

#include "LLVMParser.h"


using namespace antlrcpp;
using namespace llvm;

using namespace antlr4;

namespace {

struct LLVMParserStaticData final {
  LLVMParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LLVMParserStaticData(const LLVMParserStaticData&) = delete;
  LLVMParserStaticData(LLVMParserStaticData&&) = delete;
  LLVMParserStaticData& operator=(const LLVMParserStaticData&) = delete;
  LLVMParserStaticData& operator=(LLVMParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag llvmparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
LLVMParserStaticData *llvmparserParserStaticData = nullptr;

void llvmparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (llvmparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(llvmparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LLVMParserStaticData>(
    std::vector<std::string>{
      "basicType", "type", "pointerType", "arrayType", "globalIdentifier", 
      "localIdentifier", "unamedIdentifier", "localVariable", "variable", 
      "number", "value", "module", "initializer", "constantArray", "globalDeclaration", 
      "functionDefinition", "functionArguments", "parameterList", "parameter", 
      "block", "basicBlock", "instruction", "returnInstruction", "branchInstruction", 
      "callInstruction", "arithmeticInstruction", "memoryInstruction", "phiInstruction", 
      "phiValue", "comparisonInstruction", "binaryOperation", "comparisonPredicate"
    },
    std::vector<std::string>{
      "", "'global'", "'external'", "'define'", "'align'", "'unreachable'", 
      "'br'", "'ret'", "'call'", "'load'", "'store'", "'alloca'", "'phi'", 
      "'add'", "'sub'", "'mul'", "'div'", "'and'", "'or'", "'xor'", "'shl'", 
      "'lshr'", "'ashr'", "'icmp'", "'fcmp'", "'sext'", "'zext'", "'trunc'", 
      "'label'", "'void'", "'ptr'", "'i1'", "'i32'", "'i64'", "'f32'", "'f64'", 
      "'eq'", "'ne'", "'ugt'", "'uge'", "'ult'", "'ule'", "'sgt'", "'sge'", 
      "'slt'", "'sle'", "'='", "','", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "'@'", "'%'", "'*'", "':'", "'x'"
    },
    std::vector<std::string>{
      "", "Global", "External", "Define", "Align", "Unreachable", "Br", 
      "Ret", "Call", "Load", "Store", "Alloca", "Phi", "Add", "Sub", "Mul", 
      "Div", "And", "Or", "Xor", "Shl", "Lshr", "Ashr", "Icmp", "Fcmp", 
      "Sext", "Zext", "Trunc", "Label", "Void", "Ptr", "I1", "I32", "I64", 
      "F32", "F64", "Eq", "Ne", "Ugt", "Uge", "Ult", "Ule", "Sgt", "Sge", 
      "Slt", "Sle", "Equals", "Comma", "LeftParen", "RightParen", "LeftBrace", 
      "RightBrace", "LeftBracket", "RightBracket", "At", "Percent", "Asterisk", 
      "Colon", "Cross", "NumericIdentifier", "NamedIdentifier", "IntegerLiteral", 
      "FloatLiteral", "Whitespace", "Comment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,64,283,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,1,0,1,1,1,1,1,1,3,1,70,8,1,1,2,1,
  	2,1,2,4,2,75,8,2,11,2,12,2,76,1,2,1,2,4,2,81,8,2,11,2,12,2,82,3,2,85,
  	8,2,1,2,1,2,4,2,89,8,2,11,2,12,2,90,5,2,93,8,2,10,2,12,2,96,9,2,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,3,7,115,
  	8,7,1,8,1,8,3,8,119,8,8,1,9,1,9,1,10,1,10,3,10,125,8,10,1,11,1,11,5,11,
  	129,8,11,10,11,12,11,132,9,11,1,12,1,12,1,12,3,12,137,8,12,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,5,13,146,8,13,10,13,12,13,149,9,13,1,13,1,13,
  	1,14,1,14,1,14,1,14,1,14,1,14,3,14,159,8,14,1,15,1,15,1,15,1,15,1,15,
  	1,15,1,16,1,16,3,16,169,8,16,1,16,1,16,1,17,1,17,1,17,5,17,176,8,17,10,
  	17,12,17,179,9,17,1,18,1,18,1,18,1,19,1,19,5,19,186,8,19,10,19,12,19,
  	189,9,19,1,19,1,19,1,20,1,20,1,20,5,20,196,8,20,10,20,12,20,199,9,20,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,208,8,21,1,22,1,22,1,22,3,22,
  	213,8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,23,3,23,228,8,23,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,
  	1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,
  	3,26,254,8,26,1,27,1,27,1,27,1,27,1,27,5,27,261,8,27,10,27,12,27,264,
  	9,27,1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,30,1,30,1,31,1,31,1,31,0,1,4,32,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,0,6,2,0,29,29,31,
  	35,1,0,61,62,1,0,9,10,1,0,23,24,1,0,13,16,1,0,36,45,280,0,64,1,0,0,0,
  	2,69,1,0,0,0,4,84,1,0,0,0,6,97,1,0,0,0,8,103,1,0,0,0,10,106,1,0,0,0,12,
  	109,1,0,0,0,14,114,1,0,0,0,16,118,1,0,0,0,18,120,1,0,0,0,20,124,1,0,0,
  	0,22,130,1,0,0,0,24,136,1,0,0,0,26,138,1,0,0,0,28,152,1,0,0,0,30,160,
  	1,0,0,0,32,166,1,0,0,0,34,172,1,0,0,0,36,180,1,0,0,0,38,183,1,0,0,0,40,
  	192,1,0,0,0,42,207,1,0,0,0,44,209,1,0,0,0,46,227,1,0,0,0,48,229,1,0,0,
  	0,50,234,1,0,0,0,52,242,1,0,0,0,54,255,1,0,0,0,56,265,1,0,0,0,58,271,
  	1,0,0,0,60,278,1,0,0,0,62,280,1,0,0,0,64,65,7,0,0,0,65,1,1,0,0,0,66,70,
  	3,0,0,0,67,70,3,4,2,0,68,70,3,6,3,0,69,66,1,0,0,0,69,67,1,0,0,0,69,68,
  	1,0,0,0,70,3,1,0,0,0,71,72,6,2,-1,0,72,74,3,0,0,0,73,75,5,56,0,0,74,73,
  	1,0,0,0,75,76,1,0,0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,85,1,0,0,0,78,80,
  	3,6,3,0,79,81,5,56,0,0,80,79,1,0,0,0,81,82,1,0,0,0,82,80,1,0,0,0,82,83,
  	1,0,0,0,83,85,1,0,0,0,84,71,1,0,0,0,84,78,1,0,0,0,85,94,1,0,0,0,86,88,
  	10,2,0,0,87,89,5,56,0,0,88,87,1,0,0,0,89,90,1,0,0,0,90,88,1,0,0,0,90,
  	91,1,0,0,0,91,93,1,0,0,0,92,86,1,0,0,0,93,96,1,0,0,0,94,92,1,0,0,0,94,
  	95,1,0,0,0,95,5,1,0,0,0,96,94,1,0,0,0,97,98,5,52,0,0,98,99,5,61,0,0,99,
  	100,5,58,0,0,100,101,3,2,1,0,101,102,5,53,0,0,102,7,1,0,0,0,103,104,5,
  	54,0,0,104,105,5,60,0,0,105,9,1,0,0,0,106,107,5,55,0,0,107,108,5,60,0,
  	0,108,11,1,0,0,0,109,110,5,55,0,0,110,111,5,59,0,0,111,13,1,0,0,0,112,
  	115,3,10,5,0,113,115,3,12,6,0,114,112,1,0,0,0,114,113,1,0,0,0,115,15,
  	1,0,0,0,116,119,3,8,4,0,117,119,3,14,7,0,118,116,1,0,0,0,118,117,1,0,
  	0,0,119,17,1,0,0,0,120,121,7,1,0,0,121,19,1,0,0,0,122,125,3,16,8,0,123,
  	125,3,18,9,0,124,122,1,0,0,0,124,123,1,0,0,0,125,21,1,0,0,0,126,129,3,
  	28,14,0,127,129,3,30,15,0,128,126,1,0,0,0,128,127,1,0,0,0,129,132,1,0,
  	0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,23,1,0,0,0,132,130,1,0,0,0,133,
  	137,5,61,0,0,134,137,5,62,0,0,135,137,3,26,13,0,136,133,1,0,0,0,136,134,
  	1,0,0,0,136,135,1,0,0,0,137,25,1,0,0,0,138,139,5,52,0,0,139,140,3,2,1,
  	0,140,141,5,61,0,0,141,142,5,58,0,0,142,147,3,20,10,0,143,144,5,47,0,
  	0,144,146,3,20,10,0,145,143,1,0,0,0,146,149,1,0,0,0,147,145,1,0,0,0,147,
  	148,1,0,0,0,148,150,1,0,0,0,149,147,1,0,0,0,150,151,5,53,0,0,151,27,1,
  	0,0,0,152,153,5,1,0,0,153,154,3,2,1,0,154,158,3,8,4,0,155,156,5,47,0,
  	0,156,157,5,4,0,0,157,159,3,24,12,0,158,155,1,0,0,0,158,159,1,0,0,0,159,
  	29,1,0,0,0,160,161,5,3,0,0,161,162,3,2,1,0,162,163,3,8,4,0,163,164,3,
  	32,16,0,164,165,3,38,19,0,165,31,1,0,0,0,166,168,5,48,0,0,167,169,3,34,
  	17,0,168,167,1,0,0,0,168,169,1,0,0,0,169,170,1,0,0,0,170,171,5,49,0,0,
  	171,33,1,0,0,0,172,177,3,36,18,0,173,174,5,47,0,0,174,176,3,36,18,0,175,
  	173,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,35,1,
  	0,0,0,179,177,1,0,0,0,180,181,3,2,1,0,181,182,3,10,5,0,182,37,1,0,0,0,
  	183,187,5,50,0,0,184,186,3,40,20,0,185,184,1,0,0,0,186,189,1,0,0,0,187,
  	185,1,0,0,0,187,188,1,0,0,0,188,190,1,0,0,0,189,187,1,0,0,0,190,191,5,
  	51,0,0,191,39,1,0,0,0,192,193,5,28,0,0,193,197,5,57,0,0,194,196,3,42,
  	21,0,195,194,1,0,0,0,196,199,1,0,0,0,197,195,1,0,0,0,197,198,1,0,0,0,
  	198,41,1,0,0,0,199,197,1,0,0,0,200,208,3,44,22,0,201,208,3,46,23,0,202,
  	208,3,48,24,0,203,208,3,50,25,0,204,208,3,52,26,0,205,208,3,54,27,0,206,
  	208,3,58,29,0,207,200,1,0,0,0,207,201,1,0,0,0,207,202,1,0,0,0,207,203,
  	1,0,0,0,207,204,1,0,0,0,207,205,1,0,0,0,207,206,1,0,0,0,208,43,1,0,0,
  	0,209,210,5,7,0,0,210,212,3,2,1,0,211,213,3,20,10,0,212,211,1,0,0,0,212,
  	213,1,0,0,0,213,45,1,0,0,0,214,215,5,6,0,0,215,216,5,31,0,0,216,217,3,
  	20,10,0,217,218,5,47,0,0,218,219,5,28,0,0,219,220,3,12,6,0,220,221,5,
  	47,0,0,221,222,5,28,0,0,222,223,3,12,6,0,223,228,1,0,0,0,224,225,5,6,
  	0,0,225,226,5,28,0,0,226,228,3,12,6,0,227,214,1,0,0,0,227,224,1,0,0,0,
  	228,47,1,0,0,0,229,230,5,8,0,0,230,231,3,2,1,0,231,232,3,8,4,0,232,233,
  	3,32,16,0,233,49,1,0,0,0,234,235,3,14,7,0,235,236,5,46,0,0,236,237,3,
  	60,30,0,237,238,3,2,1,0,238,239,3,20,10,0,239,240,5,47,0,0,240,241,3,
  	20,10,0,241,51,1,0,0,0,242,243,3,14,7,0,243,244,5,46,0,0,244,245,7,2,
  	0,0,245,246,3,2,1,0,246,247,5,47,0,0,247,248,3,2,1,0,248,249,5,56,0,0,
  	249,253,3,16,8,0,250,251,5,47,0,0,251,252,5,4,0,0,252,254,5,61,0,0,253,
  	250,1,0,0,0,253,254,1,0,0,0,254,53,1,0,0,0,255,256,5,12,0,0,256,257,3,
  	2,1,0,257,262,3,56,28,0,258,259,5,47,0,0,259,261,3,56,28,0,260,258,1,
  	0,0,0,261,264,1,0,0,0,262,260,1,0,0,0,262,263,1,0,0,0,263,55,1,0,0,0,
  	264,262,1,0,0,0,265,266,5,50,0,0,266,267,3,12,6,0,267,268,5,47,0,0,268,
  	269,3,20,10,0,269,270,5,51,0,0,270,57,1,0,0,0,271,272,7,3,0,0,272,273,
  	3,62,31,0,273,274,3,2,1,0,274,275,3,20,10,0,275,276,5,47,0,0,276,277,
  	3,20,10,0,277,59,1,0,0,0,278,279,7,4,0,0,279,61,1,0,0,0,280,281,7,5,0,
  	0,281,63,1,0,0,0,23,69,76,82,84,90,94,114,118,124,128,130,136,147,158,
  	168,177,187,197,207,212,227,253,262
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  llvmparserParserStaticData = staticData.release();
}

}

LLVMParser::LLVMParser(TokenStream *input) : LLVMParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LLVMParser::LLVMParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LLVMParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *llvmparserParserStaticData->atn, llvmparserParserStaticData->decisionToDFA, llvmparserParserStaticData->sharedContextCache, options);
}

LLVMParser::~LLVMParser() {
  delete _interpreter;
}

const atn::ATN& LLVMParser::getATN() const {
  return *llvmparserParserStaticData->atn;
}

std::string LLVMParser::getGrammarFileName() const {
  return "LLVMParser.g4";
}

const std::vector<std::string>& LLVMParser::getRuleNames() const {
  return llvmparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& LLVMParser::getVocabulary() const {
  return llvmparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LLVMParser::getSerializedATN() const {
  return llvmparserParserStaticData->serializedATN;
}


//----------------- BasicTypeContext ------------------------------------------------------------------

LLVMParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::BasicTypeContext::Void() {
  return getToken(LLVMParser::Void, 0);
}

tree::TerminalNode* LLVMParser::BasicTypeContext::I1() {
  return getToken(LLVMParser::I1, 0);
}

tree::TerminalNode* LLVMParser::BasicTypeContext::I32() {
  return getToken(LLVMParser::I32, 0);
}

tree::TerminalNode* LLVMParser::BasicTypeContext::I64() {
  return getToken(LLVMParser::I64, 0);
}

tree::TerminalNode* LLVMParser::BasicTypeContext::F32() {
  return getToken(LLVMParser::F32, 0);
}

tree::TerminalNode* LLVMParser::BasicTypeContext::F64() {
  return getToken(LLVMParser::F64, 0);
}


size_t LLVMParser::BasicTypeContext::getRuleIndex() const {
  return LLVMParser::RuleBasicType;
}


std::any LLVMParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::BasicTypeContext* LLVMParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 0, LLVMParser::RuleBasicType);
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
    setState(64);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67108864000) != 0))) {
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

//----------------- TypeContext ------------------------------------------------------------------

LLVMParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::BasicTypeContext* LLVMParser::TypeContext::basicType() {
  return getRuleContext<LLVMParser::BasicTypeContext>(0);
}

LLVMParser::PointerTypeContext* LLVMParser::TypeContext::pointerType() {
  return getRuleContext<LLVMParser::PointerTypeContext>(0);
}

LLVMParser::ArrayTypeContext* LLVMParser::TypeContext::arrayType() {
  return getRuleContext<LLVMParser::ArrayTypeContext>(0);
}


size_t LLVMParser::TypeContext::getRuleIndex() const {
  return LLVMParser::RuleType;
}


std::any LLVMParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::TypeContext* LLVMParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 2, LLVMParser::RuleType);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(66);
      basicType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(67);
      pointerType(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(68);
      arrayType();
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

//----------------- PointerTypeContext ------------------------------------------------------------------

LLVMParser::PointerTypeContext::PointerTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::BasicTypeContext* LLVMParser::PointerTypeContext::basicType() {
  return getRuleContext<LLVMParser::BasicTypeContext>(0);
}

std::vector<tree::TerminalNode *> LLVMParser::PointerTypeContext::Asterisk() {
  return getTokens(LLVMParser::Asterisk);
}

tree::TerminalNode* LLVMParser::PointerTypeContext::Asterisk(size_t i) {
  return getToken(LLVMParser::Asterisk, i);
}

LLVMParser::ArrayTypeContext* LLVMParser::PointerTypeContext::arrayType() {
  return getRuleContext<LLVMParser::ArrayTypeContext>(0);
}

LLVMParser::PointerTypeContext* LLVMParser::PointerTypeContext::pointerType() {
  return getRuleContext<LLVMParser::PointerTypeContext>(0);
}


size_t LLVMParser::PointerTypeContext::getRuleIndex() const {
  return LLVMParser::RulePointerType;
}


std::any LLVMParser::PointerTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitPointerType(this);
  else
    return visitor->visitChildren(this);
}


LLVMParser::PointerTypeContext* LLVMParser::pointerType() {
   return pointerType(0);
}

LLVMParser::PointerTypeContext* LLVMParser::pointerType(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LLVMParser::PointerTypeContext *_localctx = _tracker.createInstance<PointerTypeContext>(_ctx, parentState);
  LLVMParser::PointerTypeContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, LLVMParser::RulePointerType, precedence);

    

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
    setState(84);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::Void:
      case LLVMParser::I1:
      case LLVMParser::I32:
      case LLVMParser::I64:
      case LLVMParser::F32:
      case LLVMParser::F64: {
        setState(72);
        basicType();
        setState(74); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(73);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(76); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case LLVMParser::LeftBracket: {
        setState(78);
        arrayType();
        setState(80); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(79);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(82); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(94);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PointerTypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePointerType);
        setState(86);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(88); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(87);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(90); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER); 
      }
      setState(96);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

LLVMParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::ArrayTypeContext::LeftBracket() {
  return getToken(LLVMParser::LeftBracket, 0);
}

tree::TerminalNode* LLVMParser::ArrayTypeContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}

tree::TerminalNode* LLVMParser::ArrayTypeContext::Cross() {
  return getToken(LLVMParser::Cross, 0);
}

LLVMParser::TypeContext* LLVMParser::ArrayTypeContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

tree::TerminalNode* LLVMParser::ArrayTypeContext::RightBracket() {
  return getToken(LLVMParser::RightBracket, 0);
}


size_t LLVMParser::ArrayTypeContext::getRuleIndex() const {
  return LLVMParser::RuleArrayType;
}


std::any LLVMParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ArrayTypeContext* LLVMParser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, LLVMParser::RuleArrayType);

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
    match(LLVMParser::LeftBracket);
    setState(98);
    match(LLVMParser::IntegerLiteral);
    setState(99);
    match(LLVMParser::Cross);
    setState(100);
    type();
    setState(101);
    match(LLVMParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalIdentifierContext ------------------------------------------------------------------

LLVMParser::GlobalIdentifierContext::GlobalIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::GlobalIdentifierContext::At() {
  return getToken(LLVMParser::At, 0);
}

tree::TerminalNode* LLVMParser::GlobalIdentifierContext::NamedIdentifier() {
  return getToken(LLVMParser::NamedIdentifier, 0);
}


size_t LLVMParser::GlobalIdentifierContext::getRuleIndex() const {
  return LLVMParser::RuleGlobalIdentifier;
}


std::any LLVMParser::GlobalIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitGlobalIdentifier(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::GlobalIdentifierContext* LLVMParser::globalIdentifier() {
  GlobalIdentifierContext *_localctx = _tracker.createInstance<GlobalIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 8, LLVMParser::RuleGlobalIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    match(LLVMParser::At);
    setState(104);
    match(LLVMParser::NamedIdentifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalIdentifierContext ------------------------------------------------------------------

LLVMParser::LocalIdentifierContext::LocalIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::LocalIdentifierContext::Percent() {
  return getToken(LLVMParser::Percent, 0);
}

tree::TerminalNode* LLVMParser::LocalIdentifierContext::NamedIdentifier() {
  return getToken(LLVMParser::NamedIdentifier, 0);
}


size_t LLVMParser::LocalIdentifierContext::getRuleIndex() const {
  return LLVMParser::RuleLocalIdentifier;
}


std::any LLVMParser::LocalIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitLocalIdentifier(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::LocalIdentifierContext* LLVMParser::localIdentifier() {
  LocalIdentifierContext *_localctx = _tracker.createInstance<LocalIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 10, LLVMParser::RuleLocalIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    match(LLVMParser::Percent);
    setState(107);
    match(LLVMParser::NamedIdentifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnamedIdentifierContext ------------------------------------------------------------------

LLVMParser::UnamedIdentifierContext::UnamedIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::UnamedIdentifierContext::Percent() {
  return getToken(LLVMParser::Percent, 0);
}

tree::TerminalNode* LLVMParser::UnamedIdentifierContext::NumericIdentifier() {
  return getToken(LLVMParser::NumericIdentifier, 0);
}


size_t LLVMParser::UnamedIdentifierContext::getRuleIndex() const {
  return LLVMParser::RuleUnamedIdentifier;
}


std::any LLVMParser::UnamedIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitUnamedIdentifier(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::UnamedIdentifierContext* LLVMParser::unamedIdentifier() {
  UnamedIdentifierContext *_localctx = _tracker.createInstance<UnamedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 12, LLVMParser::RuleUnamedIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(LLVMParser::Percent);
    setState(110);
    match(LLVMParser::NumericIdentifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalVariableContext ------------------------------------------------------------------

LLVMParser::LocalVariableContext::LocalVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::LocalIdentifierContext* LLVMParser::LocalVariableContext::localIdentifier() {
  return getRuleContext<LLVMParser::LocalIdentifierContext>(0);
}

LLVMParser::UnamedIdentifierContext* LLVMParser::LocalVariableContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
}


size_t LLVMParser::LocalVariableContext::getRuleIndex() const {
  return LLVMParser::RuleLocalVariable;
}


std::any LLVMParser::LocalVariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitLocalVariable(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::LocalVariableContext* LLVMParser::localVariable() {
  LocalVariableContext *_localctx = _tracker.createInstance<LocalVariableContext>(_ctx, getState());
  enterRule(_localctx, 14, LLVMParser::RuleLocalVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(114);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(112);
      localIdentifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(113);
      unamedIdentifier();
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

//----------------- VariableContext ------------------------------------------------------------------

LLVMParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::GlobalIdentifierContext* LLVMParser::VariableContext::globalIdentifier() {
  return getRuleContext<LLVMParser::GlobalIdentifierContext>(0);
}

LLVMParser::LocalVariableContext* LLVMParser::VariableContext::localVariable() {
  return getRuleContext<LLVMParser::LocalVariableContext>(0);
}


size_t LLVMParser::VariableContext::getRuleIndex() const {
  return LLVMParser::RuleVariable;
}


std::any LLVMParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::VariableContext* LLVMParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 16, LLVMParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::At: {
        enterOuterAlt(_localctx, 1);
        setState(116);
        globalIdentifier();
        break;
      }

      case LLVMParser::Percent: {
        enterOuterAlt(_localctx, 2);
        setState(117);
        localVariable();
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

LLVMParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::NumberContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}

tree::TerminalNode* LLVMParser::NumberContext::FloatLiteral() {
  return getToken(LLVMParser::FloatLiteral, 0);
}


size_t LLVMParser::NumberContext::getRuleIndex() const {
  return LLVMParser::RuleNumber;
}


std::any LLVMParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::NumberContext* LLVMParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 18, LLVMParser::RuleNumber);
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
    setState(120);
    _la = _input->LA(1);
    if (!(_la == LLVMParser::IntegerLiteral

    || _la == LLVMParser::FloatLiteral)) {
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

//----------------- ValueContext ------------------------------------------------------------------

LLVMParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::VariableContext* LLVMParser::ValueContext::variable() {
  return getRuleContext<LLVMParser::VariableContext>(0);
}

LLVMParser::NumberContext* LLVMParser::ValueContext::number() {
  return getRuleContext<LLVMParser::NumberContext>(0);
}


size_t LLVMParser::ValueContext::getRuleIndex() const {
  return LLVMParser::RuleValue;
}


std::any LLVMParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ValueContext* LLVMParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 20, LLVMParser::RuleValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(124);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::At:
      case LLVMParser::Percent: {
        enterOuterAlt(_localctx, 1);
        setState(122);
        variable();
        break;
      }

      case LLVMParser::IntegerLiteral:
      case LLVMParser::FloatLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(123);
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

//----------------- ModuleContext ------------------------------------------------------------------

LLVMParser::ModuleContext::ModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LLVMParser::GlobalDeclarationContext *> LLVMParser::ModuleContext::globalDeclaration() {
  return getRuleContexts<LLVMParser::GlobalDeclarationContext>();
}

LLVMParser::GlobalDeclarationContext* LLVMParser::ModuleContext::globalDeclaration(size_t i) {
  return getRuleContext<LLVMParser::GlobalDeclarationContext>(i);
}

std::vector<LLVMParser::FunctionDefinitionContext *> LLVMParser::ModuleContext::functionDefinition() {
  return getRuleContexts<LLVMParser::FunctionDefinitionContext>();
}

LLVMParser::FunctionDefinitionContext* LLVMParser::ModuleContext::functionDefinition(size_t i) {
  return getRuleContext<LLVMParser::FunctionDefinitionContext>(i);
}


size_t LLVMParser::ModuleContext::getRuleIndex() const {
  return LLVMParser::RuleModule;
}


std::any LLVMParser::ModuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitModule(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ModuleContext* LLVMParser::module() {
  ModuleContext *_localctx = _tracker.createInstance<ModuleContext>(_ctx, getState());
  enterRule(_localctx, 22, LLVMParser::RuleModule);
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
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Global

    || _la == LLVMParser::Define) {
      setState(128);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LLVMParser::Global: {
          setState(126);
          globalDeclaration();
          break;
        }

        case LLVMParser::Define: {
          setState(127);
          functionDefinition();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(132);
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

//----------------- InitializerContext ------------------------------------------------------------------

LLVMParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::InitializerContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}

tree::TerminalNode* LLVMParser::InitializerContext::FloatLiteral() {
  return getToken(LLVMParser::FloatLiteral, 0);
}

LLVMParser::ConstantArrayContext* LLVMParser::InitializerContext::constantArray() {
  return getRuleContext<LLVMParser::ConstantArrayContext>(0);
}


size_t LLVMParser::InitializerContext::getRuleIndex() const {
  return LLVMParser::RuleInitializer;
}


std::any LLVMParser::InitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitInitializer(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::InitializerContext* LLVMParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 24, LLVMParser::RuleInitializer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::IntegerLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(133);
        match(LLVMParser::IntegerLiteral);
        break;
      }

      case LLVMParser::FloatLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(134);
        match(LLVMParser::FloatLiteral);
        break;
      }

      case LLVMParser::LeftBracket: {
        enterOuterAlt(_localctx, 3);
        setState(135);
        constantArray();
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

//----------------- ConstantArrayContext ------------------------------------------------------------------

LLVMParser::ConstantArrayContext::ConstantArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::ConstantArrayContext::LeftBracket() {
  return getToken(LLVMParser::LeftBracket, 0);
}

LLVMParser::TypeContext* LLVMParser::ConstantArrayContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

tree::TerminalNode* LLVMParser::ConstantArrayContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}

tree::TerminalNode* LLVMParser::ConstantArrayContext::Cross() {
  return getToken(LLVMParser::Cross, 0);
}

std::vector<LLVMParser::ValueContext *> LLVMParser::ConstantArrayContext::value() {
  return getRuleContexts<LLVMParser::ValueContext>();
}

LLVMParser::ValueContext* LLVMParser::ConstantArrayContext::value(size_t i) {
  return getRuleContext<LLVMParser::ValueContext>(i);
}

tree::TerminalNode* LLVMParser::ConstantArrayContext::RightBracket() {
  return getToken(LLVMParser::RightBracket, 0);
}

std::vector<tree::TerminalNode *> LLVMParser::ConstantArrayContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::ConstantArrayContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}


size_t LLVMParser::ConstantArrayContext::getRuleIndex() const {
  return LLVMParser::RuleConstantArray;
}


std::any LLVMParser::ConstantArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitConstantArray(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ConstantArrayContext* LLVMParser::constantArray() {
  ConstantArrayContext *_localctx = _tracker.createInstance<ConstantArrayContext>(_ctx, getState());
  enterRule(_localctx, 26, LLVMParser::RuleConstantArray);
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
    setState(138);
    match(LLVMParser::LeftBracket);
    setState(139);
    type();
    setState(140);
    match(LLVMParser::IntegerLiteral);
    setState(141);
    match(LLVMParser::Cross);
    setState(142);
    value();
    setState(147);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(143);
      match(LLVMParser::Comma);
      setState(144);
      value();
      setState(149);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(150);
    match(LLVMParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalDeclarationContext ------------------------------------------------------------------

LLVMParser::GlobalDeclarationContext::GlobalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::GlobalDeclarationContext::Global() {
  return getToken(LLVMParser::Global, 0);
}

LLVMParser::TypeContext* LLVMParser::GlobalDeclarationContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

LLVMParser::GlobalIdentifierContext* LLVMParser::GlobalDeclarationContext::globalIdentifier() {
  return getRuleContext<LLVMParser::GlobalIdentifierContext>(0);
}

tree::TerminalNode* LLVMParser::GlobalDeclarationContext::Comma() {
  return getToken(LLVMParser::Comma, 0);
}

tree::TerminalNode* LLVMParser::GlobalDeclarationContext::Align() {
  return getToken(LLVMParser::Align, 0);
}

LLVMParser::InitializerContext* LLVMParser::GlobalDeclarationContext::initializer() {
  return getRuleContext<LLVMParser::InitializerContext>(0);
}


size_t LLVMParser::GlobalDeclarationContext::getRuleIndex() const {
  return LLVMParser::RuleGlobalDeclaration;
}


std::any LLVMParser::GlobalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitGlobalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::GlobalDeclarationContext* LLVMParser::globalDeclaration() {
  GlobalDeclarationContext *_localctx = _tracker.createInstance<GlobalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 28, LLVMParser::RuleGlobalDeclaration);
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
    setState(152);
    match(LLVMParser::Global);
    setState(153);
    type();
    setState(154);
    globalIdentifier();
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(155);
      match(LLVMParser::Comma);
      setState(156);
      match(LLVMParser::Align);
      setState(157);
      initializer();
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

LLVMParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::FunctionDefinitionContext::Define() {
  return getToken(LLVMParser::Define, 0);
}

LLVMParser::TypeContext* LLVMParser::FunctionDefinitionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

LLVMParser::GlobalIdentifierContext* LLVMParser::FunctionDefinitionContext::globalIdentifier() {
  return getRuleContext<LLVMParser::GlobalIdentifierContext>(0);
}

LLVMParser::FunctionArgumentsContext* LLVMParser::FunctionDefinitionContext::functionArguments() {
  return getRuleContext<LLVMParser::FunctionArgumentsContext>(0);
}

LLVMParser::BlockContext* LLVMParser::FunctionDefinitionContext::block() {
  return getRuleContext<LLVMParser::BlockContext>(0);
}


size_t LLVMParser::FunctionDefinitionContext::getRuleIndex() const {
  return LLVMParser::RuleFunctionDefinition;
}


std::any LLVMParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::FunctionDefinitionContext* LLVMParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 30, LLVMParser::RuleFunctionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(LLVMParser::Define);
    setState(161);
    type();
    setState(162);
    globalIdentifier();
    setState(163);
    functionArguments();
    setState(164);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgumentsContext ------------------------------------------------------------------

LLVMParser::FunctionArgumentsContext::FunctionArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::FunctionArgumentsContext::LeftParen() {
  return getToken(LLVMParser::LeftParen, 0);
}

tree::TerminalNode* LLVMParser::FunctionArgumentsContext::RightParen() {
  return getToken(LLVMParser::RightParen, 0);
}

LLVMParser::ParameterListContext* LLVMParser::FunctionArgumentsContext::parameterList() {
  return getRuleContext<LLVMParser::ParameterListContext>(0);
}


size_t LLVMParser::FunctionArgumentsContext::getRuleIndex() const {
  return LLVMParser::RuleFunctionArguments;
}


std::any LLVMParser::FunctionArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitFunctionArguments(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::FunctionArgumentsContext* LLVMParser::functionArguments() {
  FunctionArgumentsContext *_localctx = _tracker.createInstance<FunctionArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 32, LLVMParser::RuleFunctionArguments);
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
    setState(166);
    match(LLVMParser::LeftParen);
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503666736234496) != 0)) {
      setState(167);
      parameterList();
    }
    setState(170);
    match(LLVMParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

LLVMParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LLVMParser::ParameterContext *> LLVMParser::ParameterListContext::parameter() {
  return getRuleContexts<LLVMParser::ParameterContext>();
}

LLVMParser::ParameterContext* LLVMParser::ParameterListContext::parameter(size_t i) {
  return getRuleContext<LLVMParser::ParameterContext>(i);
}

std::vector<tree::TerminalNode *> LLVMParser::ParameterListContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::ParameterListContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}


size_t LLVMParser::ParameterListContext::getRuleIndex() const {
  return LLVMParser::RuleParameterList;
}


std::any LLVMParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ParameterListContext* LLVMParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 34, LLVMParser::RuleParameterList);
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
    setState(172);
    parameter();
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(173);
      match(LLVMParser::Comma);
      setState(174);
      parameter();
      setState(179);
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

//----------------- ParameterContext ------------------------------------------------------------------

LLVMParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::TypeContext* LLVMParser::ParameterContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

LLVMParser::LocalIdentifierContext* LLVMParser::ParameterContext::localIdentifier() {
  return getRuleContext<LLVMParser::LocalIdentifierContext>(0);
}


size_t LLVMParser::ParameterContext::getRuleIndex() const {
  return LLVMParser::RuleParameter;
}


std::any LLVMParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ParameterContext* LLVMParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 36, LLVMParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    type();
    setState(181);
    localIdentifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

LLVMParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::BlockContext::LeftBrace() {
  return getToken(LLVMParser::LeftBrace, 0);
}

tree::TerminalNode* LLVMParser::BlockContext::RightBrace() {
  return getToken(LLVMParser::RightBrace, 0);
}

std::vector<LLVMParser::BasicBlockContext *> LLVMParser::BlockContext::basicBlock() {
  return getRuleContexts<LLVMParser::BasicBlockContext>();
}

LLVMParser::BasicBlockContext* LLVMParser::BlockContext::basicBlock(size_t i) {
  return getRuleContext<LLVMParser::BasicBlockContext>(i);
}


size_t LLVMParser::BlockContext::getRuleIndex() const {
  return LLVMParser::RuleBlock;
}


std::any LLVMParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::BlockContext* LLVMParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 38, LLVMParser::RuleBlock);
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
    setState(183);
    match(LLVMParser::LeftBrace);
    setState(187);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Label) {
      setState(184);
      basicBlock();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(190);
    match(LLVMParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicBlockContext ------------------------------------------------------------------

LLVMParser::BasicBlockContext::BasicBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::BasicBlockContext::Label() {
  return getToken(LLVMParser::Label, 0);
}

tree::TerminalNode* LLVMParser::BasicBlockContext::Colon() {
  return getToken(LLVMParser::Colon, 0);
}

std::vector<LLVMParser::InstructionContext *> LLVMParser::BasicBlockContext::instruction() {
  return getRuleContexts<LLVMParser::InstructionContext>();
}

LLVMParser::InstructionContext* LLVMParser::BasicBlockContext::instruction(size_t i) {
  return getRuleContext<LLVMParser::InstructionContext>(i);
}


size_t LLVMParser::BasicBlockContext::getRuleIndex() const {
  return LLVMParser::RuleBasicBlock;
}


std::any LLVMParser::BasicBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitBasicBlock(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::BasicBlockContext* LLVMParser::basicBlock() {
  BasicBlockContext *_localctx = _tracker.createInstance<BasicBlockContext>(_ctx, getState());
  enterRule(_localctx, 40, LLVMParser::RuleBasicBlock);
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
    setState(192);
    match(LLVMParser::Label);
    setState(193);
    match(LLVMParser::Colon);
    setState(197);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36028797044134336) != 0)) {
      setState(194);
      instruction();
      setState(199);
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

//----------------- InstructionContext ------------------------------------------------------------------

LLVMParser::InstructionContext::InstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::ReturnInstructionContext* LLVMParser::InstructionContext::returnInstruction() {
  return getRuleContext<LLVMParser::ReturnInstructionContext>(0);
}

LLVMParser::BranchInstructionContext* LLVMParser::InstructionContext::branchInstruction() {
  return getRuleContext<LLVMParser::BranchInstructionContext>(0);
}

LLVMParser::CallInstructionContext* LLVMParser::InstructionContext::callInstruction() {
  return getRuleContext<LLVMParser::CallInstructionContext>(0);
}

LLVMParser::ArithmeticInstructionContext* LLVMParser::InstructionContext::arithmeticInstruction() {
  return getRuleContext<LLVMParser::ArithmeticInstructionContext>(0);
}

LLVMParser::MemoryInstructionContext* LLVMParser::InstructionContext::memoryInstruction() {
  return getRuleContext<LLVMParser::MemoryInstructionContext>(0);
}

LLVMParser::PhiInstructionContext* LLVMParser::InstructionContext::phiInstruction() {
  return getRuleContext<LLVMParser::PhiInstructionContext>(0);
}

LLVMParser::ComparisonInstructionContext* LLVMParser::InstructionContext::comparisonInstruction() {
  return getRuleContext<LLVMParser::ComparisonInstructionContext>(0);
}


size_t LLVMParser::InstructionContext::getRuleIndex() const {
  return LLVMParser::RuleInstruction;
}


std::any LLVMParser::InstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::InstructionContext* LLVMParser::instruction() {
  InstructionContext *_localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
  enterRule(_localctx, 42, LLVMParser::RuleInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(207);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(200);
      returnInstruction();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(201);
      branchInstruction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(202);
      callInstruction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(203);
      arithmeticInstruction();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(204);
      memoryInstruction();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(205);
      phiInstruction();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(206);
      comparisonInstruction();
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

//----------------- ReturnInstructionContext ------------------------------------------------------------------

LLVMParser::ReturnInstructionContext::ReturnInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::ReturnInstructionContext::Ret() {
  return getToken(LLVMParser::Ret, 0);
}

LLVMParser::TypeContext* LLVMParser::ReturnInstructionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

LLVMParser::ValueContext* LLVMParser::ReturnInstructionContext::value() {
  return getRuleContext<LLVMParser::ValueContext>(0);
}


size_t LLVMParser::ReturnInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleReturnInstruction;
}


std::any LLVMParser::ReturnInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitReturnInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ReturnInstructionContext* LLVMParser::returnInstruction() {
  ReturnInstructionContext *_localctx = _tracker.createInstance<ReturnInstructionContext>(_ctx, getState());
  enterRule(_localctx, 44, LLVMParser::RuleReturnInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    match(LLVMParser::Ret);
    setState(210);
    type();
    setState(212);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(211);
      value();
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

//----------------- BranchInstructionContext ------------------------------------------------------------------

LLVMParser::BranchInstructionContext::BranchInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::BranchInstructionContext::Br() {
  return getToken(LLVMParser::Br, 0);
}

tree::TerminalNode* LLVMParser::BranchInstructionContext::I1() {
  return getToken(LLVMParser::I1, 0);
}

LLVMParser::ValueContext* LLVMParser::BranchInstructionContext::value() {
  return getRuleContext<LLVMParser::ValueContext>(0);
}

std::vector<tree::TerminalNode *> LLVMParser::BranchInstructionContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::BranchInstructionContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}

std::vector<tree::TerminalNode *> LLVMParser::BranchInstructionContext::Label() {
  return getTokens(LLVMParser::Label);
}

tree::TerminalNode* LLVMParser::BranchInstructionContext::Label(size_t i) {
  return getToken(LLVMParser::Label, i);
}

std::vector<LLVMParser::UnamedIdentifierContext *> LLVMParser::BranchInstructionContext::unamedIdentifier() {
  return getRuleContexts<LLVMParser::UnamedIdentifierContext>();
}

LLVMParser::UnamedIdentifierContext* LLVMParser::BranchInstructionContext::unamedIdentifier(size_t i) {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(i);
}


size_t LLVMParser::BranchInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleBranchInstruction;
}


std::any LLVMParser::BranchInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitBranchInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::BranchInstructionContext* LLVMParser::branchInstruction() {
  BranchInstructionContext *_localctx = _tracker.createInstance<BranchInstructionContext>(_ctx, getState());
  enterRule(_localctx, 46, LLVMParser::RuleBranchInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(227);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(214);
      match(LLVMParser::Br);
      setState(215);
      match(LLVMParser::I1);
      setState(216);
      value();
      setState(217);
      match(LLVMParser::Comma);
      setState(218);
      match(LLVMParser::Label);
      setState(219);
      unamedIdentifier();
      setState(220);
      match(LLVMParser::Comma);
      setState(221);
      match(LLVMParser::Label);
      setState(222);
      unamedIdentifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(224);
      match(LLVMParser::Br);
      setState(225);
      match(LLVMParser::Label);
      setState(226);
      unamedIdentifier();
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

//----------------- CallInstructionContext ------------------------------------------------------------------

LLVMParser::CallInstructionContext::CallInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::CallInstructionContext::Call() {
  return getToken(LLVMParser::Call, 0);
}

LLVMParser::TypeContext* LLVMParser::CallInstructionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

LLVMParser::GlobalIdentifierContext* LLVMParser::CallInstructionContext::globalIdentifier() {
  return getRuleContext<LLVMParser::GlobalIdentifierContext>(0);
}

LLVMParser::FunctionArgumentsContext* LLVMParser::CallInstructionContext::functionArguments() {
  return getRuleContext<LLVMParser::FunctionArgumentsContext>(0);
}


size_t LLVMParser::CallInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleCallInstruction;
}


std::any LLVMParser::CallInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitCallInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::CallInstructionContext* LLVMParser::callInstruction() {
  CallInstructionContext *_localctx = _tracker.createInstance<CallInstructionContext>(_ctx, getState());
  enterRule(_localctx, 48, LLVMParser::RuleCallInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    match(LLVMParser::Call);
    setState(230);
    type();
    setState(231);
    globalIdentifier();
    setState(232);
    functionArguments();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArithmeticInstructionContext ------------------------------------------------------------------

LLVMParser::ArithmeticInstructionContext::ArithmeticInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::LocalVariableContext* LLVMParser::ArithmeticInstructionContext::localVariable() {
  return getRuleContext<LLVMParser::LocalVariableContext>(0);
}

tree::TerminalNode* LLVMParser::ArithmeticInstructionContext::Equals() {
  return getToken(LLVMParser::Equals, 0);
}

LLVMParser::BinaryOperationContext* LLVMParser::ArithmeticInstructionContext::binaryOperation() {
  return getRuleContext<LLVMParser::BinaryOperationContext>(0);
}

LLVMParser::TypeContext* LLVMParser::ArithmeticInstructionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

std::vector<LLVMParser::ValueContext *> LLVMParser::ArithmeticInstructionContext::value() {
  return getRuleContexts<LLVMParser::ValueContext>();
}

LLVMParser::ValueContext* LLVMParser::ArithmeticInstructionContext::value(size_t i) {
  return getRuleContext<LLVMParser::ValueContext>(i);
}

tree::TerminalNode* LLVMParser::ArithmeticInstructionContext::Comma() {
  return getToken(LLVMParser::Comma, 0);
}


size_t LLVMParser::ArithmeticInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleArithmeticInstruction;
}


std::any LLVMParser::ArithmeticInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitArithmeticInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ArithmeticInstructionContext* LLVMParser::arithmeticInstruction() {
  ArithmeticInstructionContext *_localctx = _tracker.createInstance<ArithmeticInstructionContext>(_ctx, getState());
  enterRule(_localctx, 50, LLVMParser::RuleArithmeticInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    localVariable();
    setState(235);
    match(LLVMParser::Equals);
    setState(236);
    binaryOperation();
    setState(237);
    type();
    setState(238);
    value();
    setState(239);
    match(LLVMParser::Comma);
    setState(240);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemoryInstructionContext ------------------------------------------------------------------

LLVMParser::MemoryInstructionContext::MemoryInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::LocalVariableContext* LLVMParser::MemoryInstructionContext::localVariable() {
  return getRuleContext<LLVMParser::LocalVariableContext>(0);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::Equals() {
  return getToken(LLVMParser::Equals, 0);
}

std::vector<LLVMParser::TypeContext *> LLVMParser::MemoryInstructionContext::type() {
  return getRuleContexts<LLVMParser::TypeContext>();
}

LLVMParser::TypeContext* LLVMParser::MemoryInstructionContext::type(size_t i) {
  return getRuleContext<LLVMParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> LLVMParser::MemoryInstructionContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::Asterisk() {
  return getToken(LLVMParser::Asterisk, 0);
}

LLVMParser::VariableContext* LLVMParser::MemoryInstructionContext::variable() {
  return getRuleContext<LLVMParser::VariableContext>(0);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::Load() {
  return getToken(LLVMParser::Load, 0);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::Store() {
  return getToken(LLVMParser::Store, 0);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::Align() {
  return getToken(LLVMParser::Align, 0);
}

tree::TerminalNode* LLVMParser::MemoryInstructionContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}


size_t LLVMParser::MemoryInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleMemoryInstruction;
}


std::any LLVMParser::MemoryInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitMemoryInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::MemoryInstructionContext* LLVMParser::memoryInstruction() {
  MemoryInstructionContext *_localctx = _tracker.createInstance<MemoryInstructionContext>(_ctx, getState());
  enterRule(_localctx, 52, LLVMParser::RuleMemoryInstruction);
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
    setState(242);
    localVariable();
    setState(243);
    match(LLVMParser::Equals);
    setState(244);
    _la = _input->LA(1);
    if (!(_la == LLVMParser::Load

    || _la == LLVMParser::Store)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(245);
    type();
    setState(246);
    match(LLVMParser::Comma);
    setState(247);
    type();
    setState(248);
    match(LLVMParser::Asterisk);
    setState(249);
    variable();
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(250);
      match(LLVMParser::Comma);
      setState(251);
      match(LLVMParser::Align);
      setState(252);
      match(LLVMParser::IntegerLiteral);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PhiInstructionContext ------------------------------------------------------------------

LLVMParser::PhiInstructionContext::PhiInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::PhiInstructionContext::Phi() {
  return getToken(LLVMParser::Phi, 0);
}

LLVMParser::TypeContext* LLVMParser::PhiInstructionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

std::vector<LLVMParser::PhiValueContext *> LLVMParser::PhiInstructionContext::phiValue() {
  return getRuleContexts<LLVMParser::PhiValueContext>();
}

LLVMParser::PhiValueContext* LLVMParser::PhiInstructionContext::phiValue(size_t i) {
  return getRuleContext<LLVMParser::PhiValueContext>(i);
}

std::vector<tree::TerminalNode *> LLVMParser::PhiInstructionContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::PhiInstructionContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}


size_t LLVMParser::PhiInstructionContext::getRuleIndex() const {
  return LLVMParser::RulePhiInstruction;
}


std::any LLVMParser::PhiInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitPhiInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::PhiInstructionContext* LLVMParser::phiInstruction() {
  PhiInstructionContext *_localctx = _tracker.createInstance<PhiInstructionContext>(_ctx, getState());
  enterRule(_localctx, 54, LLVMParser::RulePhiInstruction);
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
    setState(255);
    match(LLVMParser::Phi);
    setState(256);
    type();
    setState(257);
    phiValue();
    setState(262);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(258);
      match(LLVMParser::Comma);
      setState(259);
      phiValue();
      setState(264);
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

//----------------- PhiValueContext ------------------------------------------------------------------

LLVMParser::PhiValueContext::PhiValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::PhiValueContext::LeftBrace() {
  return getToken(LLVMParser::LeftBrace, 0);
}

LLVMParser::UnamedIdentifierContext* LLVMParser::PhiValueContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
}

tree::TerminalNode* LLVMParser::PhiValueContext::Comma() {
  return getToken(LLVMParser::Comma, 0);
}

LLVMParser::ValueContext* LLVMParser::PhiValueContext::value() {
  return getRuleContext<LLVMParser::ValueContext>(0);
}

tree::TerminalNode* LLVMParser::PhiValueContext::RightBrace() {
  return getToken(LLVMParser::RightBrace, 0);
}


size_t LLVMParser::PhiValueContext::getRuleIndex() const {
  return LLVMParser::RulePhiValue;
}


std::any LLVMParser::PhiValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitPhiValue(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::PhiValueContext* LLVMParser::phiValue() {
  PhiValueContext *_localctx = _tracker.createInstance<PhiValueContext>(_ctx, getState());
  enterRule(_localctx, 56, LLVMParser::RulePhiValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(265);
    match(LLVMParser::LeftBrace);
    setState(266);
    unamedIdentifier();
    setState(267);
    match(LLVMParser::Comma);
    setState(268);
    value();
    setState(269);
    match(LLVMParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonInstructionContext ------------------------------------------------------------------

LLVMParser::ComparisonInstructionContext::ComparisonInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::ComparisonPredicateContext* LLVMParser::ComparisonInstructionContext::comparisonPredicate() {
  return getRuleContext<LLVMParser::ComparisonPredicateContext>(0);
}

LLVMParser::TypeContext* LLVMParser::ComparisonInstructionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}

std::vector<LLVMParser::ValueContext *> LLVMParser::ComparisonInstructionContext::value() {
  return getRuleContexts<LLVMParser::ValueContext>();
}

LLVMParser::ValueContext* LLVMParser::ComparisonInstructionContext::value(size_t i) {
  return getRuleContext<LLVMParser::ValueContext>(i);
}

tree::TerminalNode* LLVMParser::ComparisonInstructionContext::Comma() {
  return getToken(LLVMParser::Comma, 0);
}

tree::TerminalNode* LLVMParser::ComparisonInstructionContext::Icmp() {
  return getToken(LLVMParser::Icmp, 0);
}

tree::TerminalNode* LLVMParser::ComparisonInstructionContext::Fcmp() {
  return getToken(LLVMParser::Fcmp, 0);
}


size_t LLVMParser::ComparisonInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleComparisonInstruction;
}


std::any LLVMParser::ComparisonInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitComparisonInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ComparisonInstructionContext* LLVMParser::comparisonInstruction() {
  ComparisonInstructionContext *_localctx = _tracker.createInstance<ComparisonInstructionContext>(_ctx, getState());
  enterRule(_localctx, 58, LLVMParser::RuleComparisonInstruction);
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
    setState(271);
    _la = _input->LA(1);
    if (!(_la == LLVMParser::Icmp

    || _la == LLVMParser::Fcmp)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(272);
    comparisonPredicate();
    setState(273);
    type();
    setState(274);
    value();
    setState(275);
    match(LLVMParser::Comma);
    setState(276);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BinaryOperationContext ------------------------------------------------------------------

LLVMParser::BinaryOperationContext::BinaryOperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::BinaryOperationContext::Add() {
  return getToken(LLVMParser::Add, 0);
}

tree::TerminalNode* LLVMParser::BinaryOperationContext::Sub() {
  return getToken(LLVMParser::Sub, 0);
}

tree::TerminalNode* LLVMParser::BinaryOperationContext::Mul() {
  return getToken(LLVMParser::Mul, 0);
}

tree::TerminalNode* LLVMParser::BinaryOperationContext::Div() {
  return getToken(LLVMParser::Div, 0);
}


size_t LLVMParser::BinaryOperationContext::getRuleIndex() const {
  return LLVMParser::RuleBinaryOperation;
}


std::any LLVMParser::BinaryOperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitBinaryOperation(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::BinaryOperationContext* LLVMParser::binaryOperation() {
  BinaryOperationContext *_localctx = _tracker.createInstance<BinaryOperationContext>(_ctx, getState());
  enterRule(_localctx, 60, LLVMParser::RuleBinaryOperation);
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
    setState(278);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 122880) != 0))) {
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

//----------------- ComparisonPredicateContext ------------------------------------------------------------------

LLVMParser::ComparisonPredicateContext::ComparisonPredicateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Eq() {
  return getToken(LLVMParser::Eq, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Ne() {
  return getToken(LLVMParser::Ne, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Ugt() {
  return getToken(LLVMParser::Ugt, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Uge() {
  return getToken(LLVMParser::Uge, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Ult() {
  return getToken(LLVMParser::Ult, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Ule() {
  return getToken(LLVMParser::Ule, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Sgt() {
  return getToken(LLVMParser::Sgt, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Sge() {
  return getToken(LLVMParser::Sge, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Slt() {
  return getToken(LLVMParser::Slt, 0);
}

tree::TerminalNode* LLVMParser::ComparisonPredicateContext::Sle() {
  return getToken(LLVMParser::Sle, 0);
}


size_t LLVMParser::ComparisonPredicateContext::getRuleIndex() const {
  return LLVMParser::RuleComparisonPredicate;
}


std::any LLVMParser::ComparisonPredicateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitComparisonPredicate(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ComparisonPredicateContext* LLVMParser::comparisonPredicate() {
  ComparisonPredicateContext *_localctx = _tracker.createInstance<ComparisonPredicateContext>(_ctx, getState());
  enterRule(_localctx, 62, LLVMParser::RuleComparisonPredicate);
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
    setState(280);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 70300024700928) != 0))) {
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

bool LLVMParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return pointerTypeSempred(antlrcpp::downCast<PointerTypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LLVMParser::pointerTypeSempred(PointerTypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void LLVMParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  llvmparserParserInitialize();
#else
  ::antlr4::internal::call_once(llvmparserParserOnceFlag, llvmparserParserInitialize);
#endif
}
