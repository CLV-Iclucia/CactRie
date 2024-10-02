
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
      "localIdentifier", "unamedIdentifier", "variable", "number", "value", 
      "module", "initializer", "constantArray", "globalDeclaration", "functionDefinition", 
      "functionArguments", "parameterList", "parameter", "block", "basicBlock", 
      "instruction", "returnInstruction", "branchInstruction", "callInstruction", 
      "arithmeticInstruction", "memoryInstruction", "phiInstruction", "phiValue", 
      "comparisonInstruction", "binaryOperation", "comparisonPredicate"
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
  	4,1,64,278,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,1,1,1,1,1,1,3,1,68,8,1,1,2,1,2,1,2,4,2,
  	73,8,2,11,2,12,2,74,1,2,1,2,4,2,79,8,2,11,2,12,2,80,3,2,83,8,2,1,2,1,
  	2,4,2,87,8,2,11,2,12,2,88,5,2,91,8,2,10,2,12,2,94,9,2,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,3,7,114,8,7,1,
  	8,1,8,1,9,1,9,3,9,120,8,9,1,10,1,10,5,10,124,8,10,10,10,12,10,127,9,10,
  	1,11,1,11,1,11,3,11,132,8,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,
  	141,8,12,10,12,12,12,144,9,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,
  	3,13,154,8,13,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,3,15,164,8,15,1,
  	15,1,15,1,16,1,16,1,16,5,16,171,8,16,10,16,12,16,174,9,16,1,17,1,17,1,
  	17,1,18,1,18,5,18,181,8,18,10,18,12,18,184,9,18,1,18,1,18,1,19,1,19,1,
  	19,5,19,191,8,19,10,19,12,19,194,9,19,1,20,1,20,1,20,1,20,1,20,1,20,1,
  	20,3,20,203,8,20,1,21,1,21,1,21,3,21,208,8,21,1,22,1,22,1,22,1,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,223,8,22,1,23,1,23,1,23,
  	1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,25,249,8,25,1,26,1,26,1,26,1,26,
  	1,26,5,26,256,8,26,10,26,12,26,259,9,26,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,30,1,30,1,30,0,1,4,31,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,
  	50,52,54,56,58,60,0,6,2,0,29,29,31,35,1,0,61,62,1,0,9,10,1,0,23,24,1,
  	0,13,16,1,0,36,45,276,0,62,1,0,0,0,2,67,1,0,0,0,4,82,1,0,0,0,6,95,1,0,
  	0,0,8,101,1,0,0,0,10,104,1,0,0,0,12,107,1,0,0,0,14,113,1,0,0,0,16,115,
  	1,0,0,0,18,119,1,0,0,0,20,125,1,0,0,0,22,131,1,0,0,0,24,133,1,0,0,0,26,
  	147,1,0,0,0,28,155,1,0,0,0,30,161,1,0,0,0,32,167,1,0,0,0,34,175,1,0,0,
  	0,36,178,1,0,0,0,38,187,1,0,0,0,40,202,1,0,0,0,42,204,1,0,0,0,44,222,
  	1,0,0,0,46,224,1,0,0,0,48,229,1,0,0,0,50,237,1,0,0,0,52,250,1,0,0,0,54,
  	260,1,0,0,0,56,266,1,0,0,0,58,273,1,0,0,0,60,275,1,0,0,0,62,63,7,0,0,
  	0,63,1,1,0,0,0,64,68,3,0,0,0,65,68,3,4,2,0,66,68,3,6,3,0,67,64,1,0,0,
  	0,67,65,1,0,0,0,67,66,1,0,0,0,68,3,1,0,0,0,69,70,6,2,-1,0,70,72,3,0,0,
  	0,71,73,5,56,0,0,72,71,1,0,0,0,73,74,1,0,0,0,74,72,1,0,0,0,74,75,1,0,
  	0,0,75,83,1,0,0,0,76,78,3,6,3,0,77,79,5,56,0,0,78,77,1,0,0,0,79,80,1,
  	0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,83,1,0,0,0,82,69,1,0,0,0,82,76,1,
  	0,0,0,83,92,1,0,0,0,84,86,10,2,0,0,85,87,5,56,0,0,86,85,1,0,0,0,87,88,
  	1,0,0,0,88,86,1,0,0,0,88,89,1,0,0,0,89,91,1,0,0,0,90,84,1,0,0,0,91,94,
  	1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,0,93,5,1,0,0,0,94,92,1,0,0,0,95,96,
  	5,52,0,0,96,97,5,61,0,0,97,98,5,58,0,0,98,99,3,2,1,0,99,100,5,53,0,0,
  	100,7,1,0,0,0,101,102,5,54,0,0,102,103,5,60,0,0,103,9,1,0,0,0,104,105,
  	5,55,0,0,105,106,5,60,0,0,106,11,1,0,0,0,107,108,5,55,0,0,108,109,5,59,
  	0,0,109,13,1,0,0,0,110,114,3,8,4,0,111,114,3,10,5,0,112,114,3,12,6,0,
  	113,110,1,0,0,0,113,111,1,0,0,0,113,112,1,0,0,0,114,15,1,0,0,0,115,116,
  	7,1,0,0,116,17,1,0,0,0,117,120,3,14,7,0,118,120,3,16,8,0,119,117,1,0,
  	0,0,119,118,1,0,0,0,120,19,1,0,0,0,121,124,3,26,13,0,122,124,3,28,14,
  	0,123,121,1,0,0,0,123,122,1,0,0,0,124,127,1,0,0,0,125,123,1,0,0,0,125,
  	126,1,0,0,0,126,21,1,0,0,0,127,125,1,0,0,0,128,132,5,61,0,0,129,132,5,
  	62,0,0,130,132,3,24,12,0,131,128,1,0,0,0,131,129,1,0,0,0,131,130,1,0,
  	0,0,132,23,1,0,0,0,133,134,5,52,0,0,134,135,3,2,1,0,135,136,5,61,0,0,
  	136,137,5,58,0,0,137,142,3,18,9,0,138,139,5,47,0,0,139,141,3,18,9,0,140,
  	138,1,0,0,0,141,144,1,0,0,0,142,140,1,0,0,0,142,143,1,0,0,0,143,145,1,
  	0,0,0,144,142,1,0,0,0,145,146,5,53,0,0,146,25,1,0,0,0,147,148,5,1,0,0,
  	148,149,3,2,1,0,149,153,3,8,4,0,150,151,5,47,0,0,151,152,5,4,0,0,152,
  	154,3,22,11,0,153,150,1,0,0,0,153,154,1,0,0,0,154,27,1,0,0,0,155,156,
  	5,3,0,0,156,157,3,2,1,0,157,158,3,8,4,0,158,159,3,30,15,0,159,160,3,36,
  	18,0,160,29,1,0,0,0,161,163,5,48,0,0,162,164,3,32,16,0,163,162,1,0,0,
  	0,163,164,1,0,0,0,164,165,1,0,0,0,165,166,5,49,0,0,166,31,1,0,0,0,167,
  	172,3,34,17,0,168,169,5,47,0,0,169,171,3,34,17,0,170,168,1,0,0,0,171,
  	174,1,0,0,0,172,170,1,0,0,0,172,173,1,0,0,0,173,33,1,0,0,0,174,172,1,
  	0,0,0,175,176,3,2,1,0,176,177,3,10,5,0,177,35,1,0,0,0,178,182,5,50,0,
  	0,179,181,3,38,19,0,180,179,1,0,0,0,181,184,1,0,0,0,182,180,1,0,0,0,182,
  	183,1,0,0,0,183,185,1,0,0,0,184,182,1,0,0,0,185,186,5,51,0,0,186,37,1,
  	0,0,0,187,188,5,28,0,0,188,192,5,57,0,0,189,191,3,40,20,0,190,189,1,0,
  	0,0,191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,39,1,0,0,0,194,
  	192,1,0,0,0,195,203,3,42,21,0,196,203,3,44,22,0,197,203,3,46,23,0,198,
  	203,3,48,24,0,199,203,3,50,25,0,200,203,3,52,26,0,201,203,3,56,28,0,202,
  	195,1,0,0,0,202,196,1,0,0,0,202,197,1,0,0,0,202,198,1,0,0,0,202,199,1,
  	0,0,0,202,200,1,0,0,0,202,201,1,0,0,0,203,41,1,0,0,0,204,205,5,7,0,0,
  	205,207,3,2,1,0,206,208,3,18,9,0,207,206,1,0,0,0,207,208,1,0,0,0,208,
  	43,1,0,0,0,209,210,5,6,0,0,210,211,5,31,0,0,211,212,3,18,9,0,212,213,
  	5,47,0,0,213,214,5,28,0,0,214,215,3,12,6,0,215,216,5,47,0,0,216,217,5,
  	28,0,0,217,218,3,12,6,0,218,223,1,0,0,0,219,220,5,6,0,0,220,221,5,28,
  	0,0,221,223,3,12,6,0,222,209,1,0,0,0,222,219,1,0,0,0,223,45,1,0,0,0,224,
  	225,5,8,0,0,225,226,3,2,1,0,226,227,3,8,4,0,227,228,3,30,15,0,228,47,
  	1,0,0,0,229,230,3,14,7,0,230,231,5,46,0,0,231,232,3,58,29,0,232,233,3,
  	2,1,0,233,234,3,18,9,0,234,235,5,47,0,0,235,236,3,18,9,0,236,49,1,0,0,
  	0,237,238,3,14,7,0,238,239,5,46,0,0,239,240,7,2,0,0,240,241,3,2,1,0,241,
  	242,5,47,0,0,242,243,3,2,1,0,243,244,5,56,0,0,244,248,3,14,7,0,245,246,
  	5,47,0,0,246,247,5,4,0,0,247,249,5,61,0,0,248,245,1,0,0,0,248,249,1,0,
  	0,0,249,51,1,0,0,0,250,251,5,12,0,0,251,252,3,2,1,0,252,257,3,54,27,0,
  	253,254,5,47,0,0,254,256,3,54,27,0,255,253,1,0,0,0,256,259,1,0,0,0,257,
  	255,1,0,0,0,257,258,1,0,0,0,258,53,1,0,0,0,259,257,1,0,0,0,260,261,5,
  	50,0,0,261,262,3,12,6,0,262,263,5,47,0,0,263,264,3,18,9,0,264,265,5,51,
  	0,0,265,55,1,0,0,0,266,267,7,3,0,0,267,268,3,60,30,0,268,269,3,2,1,0,
  	269,270,3,18,9,0,270,271,5,47,0,0,271,272,3,18,9,0,272,57,1,0,0,0,273,
  	274,7,4,0,0,274,59,1,0,0,0,275,276,7,5,0,0,276,61,1,0,0,0,22,67,74,80,
  	82,88,92,113,119,123,125,131,142,153,163,172,182,192,202,207,222,248,
  	257
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
    setState(62);
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
    setState(67);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(64);
      basicType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(65);
      pointerType(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(66);
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
    setState(82);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::Void:
      case LLVMParser::I1:
      case LLVMParser::I32:
      case LLVMParser::I64:
      case LLVMParser::F32:
      case LLVMParser::F64: {
        setState(70);
        basicType();
        setState(72); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(71);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(74); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case LLVMParser::LeftBracket: {
        setState(76);
        arrayType();
        setState(78); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(77);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(80); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(92);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PointerTypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePointerType);
        setState(84);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(86); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(85);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(88); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER); 
      }
      setState(94);
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
    setState(95);
    match(LLVMParser::LeftBracket);
    setState(96);
    match(LLVMParser::IntegerLiteral);
    setState(97);
    match(LLVMParser::Cross);
    setState(98);
    type();
    setState(99);
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
    setState(101);
    match(LLVMParser::At);
    setState(102);
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
    setState(104);
    match(LLVMParser::Percent);
    setState(105);
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
    setState(107);
    match(LLVMParser::Percent);
    setState(108);
    match(LLVMParser::NumericIdentifier);
   
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

LLVMParser::LocalIdentifierContext* LLVMParser::VariableContext::localIdentifier() {
  return getRuleContext<LLVMParser::LocalIdentifierContext>(0);
}

LLVMParser::UnamedIdentifierContext* LLVMParser::VariableContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
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
  enterRule(_localctx, 14, LLVMParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(113);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(110);
      globalIdentifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(111);
      localIdentifier();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(112);
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
  enterRule(_localctx, 16, LLVMParser::RuleNumber);
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
    setState(115);
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
  enterRule(_localctx, 18, LLVMParser::RuleValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(119);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::At:
      case LLVMParser::Percent: {
        enterOuterAlt(_localctx, 1);
        setState(117);
        variable();
        break;
      }

      case LLVMParser::IntegerLiteral:
      case LLVMParser::FloatLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(118);
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
  enterRule(_localctx, 20, LLVMParser::RuleModule);
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
    setState(125);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Global

    || _la == LLVMParser::Define) {
      setState(123);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LLVMParser::Global: {
          setState(121);
          globalDeclaration();
          break;
        }

        case LLVMParser::Define: {
          setState(122);
          functionDefinition();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(127);
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
  enterRule(_localctx, 22, LLVMParser::RuleInitializer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(131);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::IntegerLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(128);
        match(LLVMParser::IntegerLiteral);
        break;
      }

      case LLVMParser::FloatLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(129);
        match(LLVMParser::FloatLiteral);
        break;
      }

      case LLVMParser::LeftBracket: {
        enterOuterAlt(_localctx, 3);
        setState(130);
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
  enterRule(_localctx, 24, LLVMParser::RuleConstantArray);
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
    setState(133);
    match(LLVMParser::LeftBracket);
    setState(134);
    type();
    setState(135);
    match(LLVMParser::IntegerLiteral);
    setState(136);
    match(LLVMParser::Cross);
    setState(137);
    value();
    setState(142);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(138);
      match(LLVMParser::Comma);
      setState(139);
      value();
      setState(144);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(145);
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
  enterRule(_localctx, 26, LLVMParser::RuleGlobalDeclaration);
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
    setState(147);
    match(LLVMParser::Global);
    setState(148);
    type();
    setState(149);
    globalIdentifier();
    setState(153);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(150);
      match(LLVMParser::Comma);
      setState(151);
      match(LLVMParser::Align);
      setState(152);
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
  enterRule(_localctx, 28, LLVMParser::RuleFunctionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    match(LLVMParser::Define);
    setState(156);
    type();
    setState(157);
    globalIdentifier();
    setState(158);
    functionArguments();
    setState(159);
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
  enterRule(_localctx, 30, LLVMParser::RuleFunctionArguments);
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
    match(LLVMParser::LeftParen);
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503666736234496) != 0)) {
      setState(162);
      parameterList();
    }
    setState(165);
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
  enterRule(_localctx, 32, LLVMParser::RuleParameterList);
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
    parameter();
    setState(172);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(168);
      match(LLVMParser::Comma);
      setState(169);
      parameter();
      setState(174);
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
  enterRule(_localctx, 34, LLVMParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    type();
    setState(176);
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
  enterRule(_localctx, 36, LLVMParser::RuleBlock);
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
    setState(178);
    match(LLVMParser::LeftBrace);
    setState(182);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Label) {
      setState(179);
      basicBlock();
      setState(184);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(185);
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
  enterRule(_localctx, 38, LLVMParser::RuleBasicBlock);
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
    setState(187);
    match(LLVMParser::Label);
    setState(188);
    match(LLVMParser::Colon);
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 54043195553616320) != 0)) {
      setState(189);
      instruction();
      setState(194);
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
  enterRule(_localctx, 40, LLVMParser::RuleInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(195);
      returnInstruction();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(196);
      branchInstruction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(197);
      callInstruction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(198);
      arithmeticInstruction();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(199);
      memoryInstruction();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(200);
      phiInstruction();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(201);
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
  enterRule(_localctx, 42, LLVMParser::RuleReturnInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(LLVMParser::Ret);
    setState(205);
    type();
    setState(207);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(206);
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
  enterRule(_localctx, 44, LLVMParser::RuleBranchInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(222);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(209);
      match(LLVMParser::Br);
      setState(210);
      match(LLVMParser::I1);
      setState(211);
      value();
      setState(212);
      match(LLVMParser::Comma);
      setState(213);
      match(LLVMParser::Label);
      setState(214);
      unamedIdentifier();
      setState(215);
      match(LLVMParser::Comma);
      setState(216);
      match(LLVMParser::Label);
      setState(217);
      unamedIdentifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(219);
      match(LLVMParser::Br);
      setState(220);
      match(LLVMParser::Label);
      setState(221);
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
  enterRule(_localctx, 46, LLVMParser::RuleCallInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(224);
    match(LLVMParser::Call);
    setState(225);
    type();
    setState(226);
    globalIdentifier();
    setState(227);
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

LLVMParser::VariableContext* LLVMParser::ArithmeticInstructionContext::variable() {
  return getRuleContext<LLVMParser::VariableContext>(0);
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
  enterRule(_localctx, 48, LLVMParser::RuleArithmeticInstruction);

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
    variable();
    setState(230);
    match(LLVMParser::Equals);
    setState(231);
    binaryOperation();
    setState(232);
    type();
    setState(233);
    value();
    setState(234);
    match(LLVMParser::Comma);
    setState(235);
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

std::vector<LLVMParser::VariableContext *> LLVMParser::MemoryInstructionContext::variable() {
  return getRuleContexts<LLVMParser::VariableContext>();
}

LLVMParser::VariableContext* LLVMParser::MemoryInstructionContext::variable(size_t i) {
  return getRuleContext<LLVMParser::VariableContext>(i);
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
  enterRule(_localctx, 50, LLVMParser::RuleMemoryInstruction);
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
    setState(237);
    variable();
    setState(238);
    match(LLVMParser::Equals);
    setState(239);
    _la = _input->LA(1);
    if (!(_la == LLVMParser::Load

    || _la == LLVMParser::Store)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(240);
    type();
    setState(241);
    match(LLVMParser::Comma);
    setState(242);
    type();
    setState(243);
    match(LLVMParser::Asterisk);
    setState(244);
    variable();
    setState(248);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(245);
      match(LLVMParser::Comma);
      setState(246);
      match(LLVMParser::Align);
      setState(247);
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
  enterRule(_localctx, 52, LLVMParser::RulePhiInstruction);
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
    setState(250);
    match(LLVMParser::Phi);
    setState(251);
    type();
    setState(252);
    phiValue();
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(253);
      match(LLVMParser::Comma);
      setState(254);
      phiValue();
      setState(259);
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
  enterRule(_localctx, 54, LLVMParser::RulePhiValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    match(LLVMParser::LeftBrace);
    setState(261);
    unamedIdentifier();
    setState(262);
    match(LLVMParser::Comma);
    setState(263);
    value();
    setState(264);
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
  enterRule(_localctx, 56, LLVMParser::RuleComparisonInstruction);
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
    setState(266);
    _la = _input->LA(1);
    if (!(_la == LLVMParser::Icmp

    || _la == LLVMParser::Fcmp)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(267);
    comparisonPredicate();
    setState(268);
    type();
    setState(269);
    value();
    setState(270);
    match(LLVMParser::Comma);
    setState(271);
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
  enterRule(_localctx, 58, LLVMParser::RuleBinaryOperation);
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
    setState(273);
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
  enterRule(_localctx, 60, LLVMParser::RuleComparisonPredicate);
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
    setState(275);
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
