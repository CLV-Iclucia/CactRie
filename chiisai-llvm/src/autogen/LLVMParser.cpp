
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
      "scalarType", "basicType", "type", "pointerType", "arrayType", "globalIdentifier", 
      "localIdentifier", "unamedIdentifier", "localVariable", "variable", 
      "literal", "number", "value", "module", "initializer", "constantArray", 
      "globalDeclaration", "functionDefinition", "functionArguments", "parameterList", 
      "parameter", "basicBlock", "instruction", "returnInstruction", "branchInstruction", 
      "callInstruction", "arithmeticInstruction", "loadInstruction", "storeInstruction", 
      "phiInstruction", "phiValue", "comparisonOperation", "comparisonInstruction", 
      "allocaInstruction", "binaryOperation", "comparisonPredicate"
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
  	4,1,64,324,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,1,0,1,0,1,1,1,1,3,1,77,8,1,1,2,1,2,1,2,3,2,82,8,2,1,3,1,3,1,3,4,3,
  	87,8,3,11,3,12,3,88,1,3,1,3,4,3,93,8,3,11,3,12,3,94,3,3,97,8,3,1,3,1,
  	3,4,3,101,8,3,11,3,12,3,102,5,3,105,8,3,10,3,12,3,108,9,3,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,8,1,8,3,8,127,8,8,1,
  	9,1,9,3,9,131,8,9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,3,12,140,8,12,1,
  	13,1,13,5,13,144,8,13,10,13,12,13,147,9,13,1,14,1,14,1,14,3,14,152,8,
  	14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,5,15,161,8,15,10,15,12,15,164,9,
  	15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,3,16,174,8,16,1,17,1,17,1,
  	17,1,17,1,17,1,17,5,17,182,8,17,10,17,12,17,185,9,17,1,17,1,17,1,18,1,
  	18,3,18,191,8,18,1,18,1,18,1,19,1,19,1,19,5,19,198,8,19,10,19,12,19,201,
  	9,19,1,20,1,20,1,20,1,21,1,21,1,21,5,21,209,8,21,10,21,12,21,212,9,21,
  	1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,223,8,22,1,23,1,23,
  	1,23,3,23,228,8,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,
  	1,24,1,24,1,24,3,24,243,8,24,1,25,1,25,1,25,3,25,248,8,25,1,25,1,25,1,
  	25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,274,8,27,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,286,8,28,1,29,1,29,1,29,1,29,1,
  	29,5,29,293,8,29,10,29,12,29,296,9,29,1,30,1,30,1,30,1,30,1,30,1,30,1,
  	31,1,31,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,33,1,33,1,33,1,
  	33,1,33,1,34,1,34,1,35,1,35,1,35,0,1,6,36,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,
  	68,70,0,5,1,0,31,35,1,0,61,62,1,0,23,24,1,0,13,16,1,0,36,45,322,0,72,
  	1,0,0,0,2,76,1,0,0,0,4,81,1,0,0,0,6,96,1,0,0,0,8,109,1,0,0,0,10,115,1,
  	0,0,0,12,118,1,0,0,0,14,121,1,0,0,0,16,126,1,0,0,0,18,130,1,0,0,0,20,
  	132,1,0,0,0,22,134,1,0,0,0,24,139,1,0,0,0,26,145,1,0,0,0,28,151,1,0,0,
  	0,30,153,1,0,0,0,32,167,1,0,0,0,34,175,1,0,0,0,36,188,1,0,0,0,38,194,
  	1,0,0,0,40,202,1,0,0,0,42,205,1,0,0,0,44,222,1,0,0,0,46,224,1,0,0,0,48,
  	242,1,0,0,0,50,247,1,0,0,0,52,254,1,0,0,0,54,262,1,0,0,0,56,275,1,0,0,
  	0,58,287,1,0,0,0,60,297,1,0,0,0,62,303,1,0,0,0,64,305,1,0,0,0,66,314,
  	1,0,0,0,68,319,1,0,0,0,70,321,1,0,0,0,72,73,7,0,0,0,73,1,1,0,0,0,74,77,
  	5,29,0,0,75,77,3,0,0,0,76,74,1,0,0,0,76,75,1,0,0,0,77,3,1,0,0,0,78,82,
  	3,2,1,0,79,82,3,6,3,0,80,82,3,8,4,0,81,78,1,0,0,0,81,79,1,0,0,0,81,80,
  	1,0,0,0,82,5,1,0,0,0,83,84,6,3,-1,0,84,86,3,2,1,0,85,87,5,56,0,0,86,85,
  	1,0,0,0,87,88,1,0,0,0,88,86,1,0,0,0,88,89,1,0,0,0,89,97,1,0,0,0,90,92,
  	3,8,4,0,91,93,5,56,0,0,92,91,1,0,0,0,93,94,1,0,0,0,94,92,1,0,0,0,94,95,
  	1,0,0,0,95,97,1,0,0,0,96,83,1,0,0,0,96,90,1,0,0,0,97,106,1,0,0,0,98,100,
  	10,2,0,0,99,101,5,56,0,0,100,99,1,0,0,0,101,102,1,0,0,0,102,100,1,0,0,
  	0,102,103,1,0,0,0,103,105,1,0,0,0,104,98,1,0,0,0,105,108,1,0,0,0,106,
  	104,1,0,0,0,106,107,1,0,0,0,107,7,1,0,0,0,108,106,1,0,0,0,109,110,5,52,
  	0,0,110,111,5,61,0,0,111,112,5,58,0,0,112,113,3,4,2,0,113,114,5,53,0,
  	0,114,9,1,0,0,0,115,116,5,54,0,0,116,117,5,60,0,0,117,11,1,0,0,0,118,
  	119,5,55,0,0,119,120,5,60,0,0,120,13,1,0,0,0,121,122,5,55,0,0,122,123,
  	5,59,0,0,123,15,1,0,0,0,124,127,3,12,6,0,125,127,3,14,7,0,126,124,1,0,
  	0,0,126,125,1,0,0,0,127,17,1,0,0,0,128,131,3,10,5,0,129,131,3,16,8,0,
  	130,128,1,0,0,0,130,129,1,0,0,0,131,19,1,0,0,0,132,133,7,1,0,0,133,21,
  	1,0,0,0,134,135,3,0,0,0,135,136,3,20,10,0,136,23,1,0,0,0,137,140,3,18,
  	9,0,138,140,3,22,11,0,139,137,1,0,0,0,139,138,1,0,0,0,140,25,1,0,0,0,
  	141,144,3,32,16,0,142,144,3,34,17,0,143,141,1,0,0,0,143,142,1,0,0,0,144,
  	147,1,0,0,0,145,143,1,0,0,0,145,146,1,0,0,0,146,27,1,0,0,0,147,145,1,
  	0,0,0,148,152,5,61,0,0,149,152,5,62,0,0,150,152,3,30,15,0,151,148,1,0,
  	0,0,151,149,1,0,0,0,151,150,1,0,0,0,152,29,1,0,0,0,153,154,5,52,0,0,154,
  	155,3,4,2,0,155,156,5,61,0,0,156,157,5,58,0,0,157,162,3,24,12,0,158,159,
  	5,47,0,0,159,161,3,24,12,0,160,158,1,0,0,0,161,164,1,0,0,0,162,160,1,
  	0,0,0,162,163,1,0,0,0,163,165,1,0,0,0,164,162,1,0,0,0,165,166,5,53,0,
  	0,166,31,1,0,0,0,167,168,5,1,0,0,168,169,3,4,2,0,169,173,3,10,5,0,170,
  	171,5,47,0,0,171,172,5,4,0,0,172,174,3,28,14,0,173,170,1,0,0,0,173,174,
  	1,0,0,0,174,33,1,0,0,0,175,176,5,3,0,0,176,177,3,4,2,0,177,178,3,10,5,
  	0,178,179,3,36,18,0,179,183,5,50,0,0,180,182,3,42,21,0,181,180,1,0,0,
  	0,182,185,1,0,0,0,183,181,1,0,0,0,183,184,1,0,0,0,184,186,1,0,0,0,185,
  	183,1,0,0,0,186,187,5,51,0,0,187,35,1,0,0,0,188,190,5,48,0,0,189,191,
  	3,38,19,0,190,189,1,0,0,0,190,191,1,0,0,0,191,192,1,0,0,0,192,193,5,49,
  	0,0,193,37,1,0,0,0,194,199,3,40,20,0,195,196,5,47,0,0,196,198,3,40,20,
  	0,197,195,1,0,0,0,198,201,1,0,0,0,199,197,1,0,0,0,199,200,1,0,0,0,200,
  	39,1,0,0,0,201,199,1,0,0,0,202,203,3,4,2,0,203,204,3,12,6,0,204,41,1,
  	0,0,0,205,206,5,28,0,0,206,210,5,57,0,0,207,209,3,44,22,0,208,207,1,0,
  	0,0,209,212,1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,43,1,0,0,0,212,
  	210,1,0,0,0,213,223,3,46,23,0,214,223,3,48,24,0,215,223,3,50,25,0,216,
  	223,3,52,26,0,217,223,3,54,27,0,218,223,3,56,28,0,219,223,3,58,29,0,220,
  	223,3,64,32,0,221,223,3,66,33,0,222,213,1,0,0,0,222,214,1,0,0,0,222,215,
  	1,0,0,0,222,216,1,0,0,0,222,217,1,0,0,0,222,218,1,0,0,0,222,219,1,0,0,
  	0,222,220,1,0,0,0,222,221,1,0,0,0,223,45,1,0,0,0,224,225,5,7,0,0,225,
  	227,3,4,2,0,226,228,3,24,12,0,227,226,1,0,0,0,227,228,1,0,0,0,228,47,
  	1,0,0,0,229,230,5,6,0,0,230,231,5,31,0,0,231,232,3,24,12,0,232,233,5,
  	47,0,0,233,234,5,28,0,0,234,235,3,14,7,0,235,236,5,47,0,0,236,237,5,28,
  	0,0,237,238,3,14,7,0,238,243,1,0,0,0,239,240,5,6,0,0,240,241,5,28,0,0,
  	241,243,3,14,7,0,242,229,1,0,0,0,242,239,1,0,0,0,243,49,1,0,0,0,244,245,
  	3,14,7,0,245,246,5,46,0,0,246,248,1,0,0,0,247,244,1,0,0,0,247,248,1,0,
  	0,0,248,249,1,0,0,0,249,250,5,8,0,0,250,251,3,4,2,0,251,252,3,10,5,0,
  	252,253,3,36,18,0,253,51,1,0,0,0,254,255,3,14,7,0,255,256,5,46,0,0,256,
  	257,3,68,34,0,257,258,3,4,2,0,258,259,3,24,12,0,259,260,5,47,0,0,260,
  	261,3,24,12,0,261,53,1,0,0,0,262,263,3,14,7,0,263,264,5,46,0,0,264,265,
  	5,9,0,0,265,266,3,4,2,0,266,267,5,47,0,0,267,268,3,4,2,0,268,269,5,56,
  	0,0,269,273,3,18,9,0,270,271,5,47,0,0,271,272,5,4,0,0,272,274,5,61,0,
  	0,273,270,1,0,0,0,273,274,1,0,0,0,274,55,1,0,0,0,275,276,5,10,0,0,276,
  	277,3,4,2,0,277,278,3,24,12,0,278,279,5,47,0,0,279,280,3,4,2,0,280,281,
  	5,56,0,0,281,285,3,18,9,0,282,283,5,47,0,0,283,284,5,4,0,0,284,286,5,
  	61,0,0,285,282,1,0,0,0,285,286,1,0,0,0,286,57,1,0,0,0,287,288,5,12,0,
  	0,288,289,3,4,2,0,289,294,3,60,30,0,290,291,5,47,0,0,291,293,3,60,30,
  	0,292,290,1,0,0,0,293,296,1,0,0,0,294,292,1,0,0,0,294,295,1,0,0,0,295,
  	59,1,0,0,0,296,294,1,0,0,0,297,298,5,50,0,0,298,299,3,14,7,0,299,300,
  	5,47,0,0,300,301,3,24,12,0,301,302,5,51,0,0,302,61,1,0,0,0,303,304,7,
  	2,0,0,304,63,1,0,0,0,305,306,3,14,7,0,306,307,5,46,0,0,307,308,3,62,31,
  	0,308,309,3,70,35,0,309,310,3,4,2,0,310,311,3,24,12,0,311,312,5,47,0,
  	0,312,313,3,24,12,0,313,65,1,0,0,0,314,315,3,12,6,0,315,316,5,46,0,0,
  	316,317,5,11,0,0,317,318,3,4,2,0,318,67,1,0,0,0,319,320,7,3,0,0,320,69,
  	1,0,0,0,321,322,7,4,0,0,322,71,1,0,0,0,26,76,81,88,94,96,102,106,126,
  	130,139,143,145,151,162,173,183,190,199,210,222,227,242,247,273,285,294
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


//----------------- ScalarTypeContext ------------------------------------------------------------------

LLVMParser::ScalarTypeContext::ScalarTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::ScalarTypeContext::I1() {
  return getToken(LLVMParser::I1, 0);
}

tree::TerminalNode* LLVMParser::ScalarTypeContext::I32() {
  return getToken(LLVMParser::I32, 0);
}

tree::TerminalNode* LLVMParser::ScalarTypeContext::I64() {
  return getToken(LLVMParser::I64, 0);
}

tree::TerminalNode* LLVMParser::ScalarTypeContext::F32() {
  return getToken(LLVMParser::F32, 0);
}

tree::TerminalNode* LLVMParser::ScalarTypeContext::F64() {
  return getToken(LLVMParser::F64, 0);
}


size_t LLVMParser::ScalarTypeContext::getRuleIndex() const {
  return LLVMParser::RuleScalarType;
}


std::any LLVMParser::ScalarTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitScalarType(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ScalarTypeContext* LLVMParser::scalarType() {
  ScalarTypeContext *_localctx = _tracker.createInstance<ScalarTypeContext>(_ctx, getState());
  enterRule(_localctx, 0, LLVMParser::RuleScalarType);
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
    setState(72);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 66571993088) != 0))) {
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

//----------------- BasicTypeContext ------------------------------------------------------------------

LLVMParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::BasicTypeContext::Void() {
  return getToken(LLVMParser::Void, 0);
}

LLVMParser::ScalarTypeContext* LLVMParser::BasicTypeContext::scalarType() {
  return getRuleContext<LLVMParser::ScalarTypeContext>(0);
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
  enterRule(_localctx, 2, LLVMParser::RuleBasicType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(74);
        match(LLVMParser::Void);
        break;
      }

      case LLVMParser::I1:
      case LLVMParser::I32:
      case LLVMParser::I64:
      case LLVMParser::F32:
      case LLVMParser::F64: {
        enterOuterAlt(_localctx, 2);
        setState(75);
        scalarType();
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
  enterRule(_localctx, 4, LLVMParser::RuleType);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(78);
      basicType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
      pointerType(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(80);
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
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, LLVMParser::RulePointerType, precedence);

    

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
    setState(96);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::Void:
      case LLVMParser::I1:
      case LLVMParser::I32:
      case LLVMParser::I64:
      case LLVMParser::F32:
      case LLVMParser::F64: {
        setState(84);
        basicType();
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
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case LLVMParser::LeftBracket: {
        setState(90);
        arrayType();
        setState(92); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(91);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(94); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(106);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<PointerTypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RulePointerType);
        setState(98);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(100); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(99);
                  match(LLVMParser::Asterisk);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(102); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER); 
      }
      setState(108);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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
  enterRule(_localctx, 8, LLVMParser::RuleArrayType);

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
    match(LLVMParser::LeftBracket);
    setState(110);
    match(LLVMParser::IntegerLiteral);
    setState(111);
    match(LLVMParser::Cross);
    setState(112);
    type();
    setState(113);
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
  enterRule(_localctx, 10, LLVMParser::RuleGlobalIdentifier);

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
    match(LLVMParser::At);
    setState(116);
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
  enterRule(_localctx, 12, LLVMParser::RuleLocalIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(LLVMParser::Percent);
    setState(119);
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
  enterRule(_localctx, 14, LLVMParser::RuleUnamedIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(LLVMParser::Percent);
    setState(122);
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
  enterRule(_localctx, 16, LLVMParser::RuleLocalVariable);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(124);
      localIdentifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(125);
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
  enterRule(_localctx, 18, LLVMParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(130);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::At: {
        enterOuterAlt(_localctx, 1);
        setState(128);
        globalIdentifier();
        break;
      }

      case LLVMParser::Percent: {
        enterOuterAlt(_localctx, 2);
        setState(129);
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

//----------------- LiteralContext ------------------------------------------------------------------

LLVMParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::LiteralContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}

tree::TerminalNode* LLVMParser::LiteralContext::FloatLiteral() {
  return getToken(LLVMParser::FloatLiteral, 0);
}


size_t LLVMParser::LiteralContext::getRuleIndex() const {
  return LLVMParser::RuleLiteral;
}


std::any LLVMParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::LiteralContext* LLVMParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 20, LLVMParser::RuleLiteral);
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
    setState(132);
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

//----------------- NumberContext ------------------------------------------------------------------

LLVMParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::ScalarTypeContext* LLVMParser::NumberContext::scalarType() {
  return getRuleContext<LLVMParser::ScalarTypeContext>(0);
}

LLVMParser::LiteralContext* LLVMParser::NumberContext::literal() {
  return getRuleContext<LLVMParser::LiteralContext>(0);
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
  enterRule(_localctx, 22, LLVMParser::RuleNumber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    scalarType();
    setState(135);
    literal();
   
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
  enterRule(_localctx, 24, LLVMParser::RuleValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(139);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::At:
      case LLVMParser::Percent: {
        enterOuterAlt(_localctx, 1);
        setState(137);
        variable();
        break;
      }

      case LLVMParser::I1:
      case LLVMParser::I32:
      case LLVMParser::I64:
      case LLVMParser::F32:
      case LLVMParser::F64: {
        enterOuterAlt(_localctx, 2);
        setState(138);
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
  enterRule(_localctx, 26, LLVMParser::RuleModule);
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
    setState(145);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Global

    || _la == LLVMParser::Define) {
      setState(143);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LLVMParser::Global: {
          setState(141);
          globalDeclaration();
          break;
        }

        case LLVMParser::Define: {
          setState(142);
          functionDefinition();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(147);
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
  enterRule(_localctx, 28, LLVMParser::RuleInitializer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LLVMParser::IntegerLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(148);
        match(LLVMParser::IntegerLiteral);
        break;
      }

      case LLVMParser::FloatLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(149);
        match(LLVMParser::FloatLiteral);
        break;
      }

      case LLVMParser::LeftBracket: {
        enterOuterAlt(_localctx, 3);
        setState(150);
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
  enterRule(_localctx, 30, LLVMParser::RuleConstantArray);
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
    setState(153);
    match(LLVMParser::LeftBracket);
    setState(154);
    type();
    setState(155);
    match(LLVMParser::IntegerLiteral);
    setState(156);
    match(LLVMParser::Cross);
    setState(157);
    value();
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(158);
      match(LLVMParser::Comma);
      setState(159);
      value();
      setState(164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(165);
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
  enterRule(_localctx, 32, LLVMParser::RuleGlobalDeclaration);
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
    match(LLVMParser::Global);
    setState(168);
    type();
    setState(169);
    globalIdentifier();
    setState(173);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(170);
      match(LLVMParser::Comma);
      setState(171);
      match(LLVMParser::Align);
      setState(172);
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

tree::TerminalNode* LLVMParser::FunctionDefinitionContext::LeftBrace() {
  return getToken(LLVMParser::LeftBrace, 0);
}

tree::TerminalNode* LLVMParser::FunctionDefinitionContext::RightBrace() {
  return getToken(LLVMParser::RightBrace, 0);
}

std::vector<LLVMParser::BasicBlockContext *> LLVMParser::FunctionDefinitionContext::basicBlock() {
  return getRuleContexts<LLVMParser::BasicBlockContext>();
}

LLVMParser::BasicBlockContext* LLVMParser::FunctionDefinitionContext::basicBlock(size_t i) {
  return getRuleContext<LLVMParser::BasicBlockContext>(i);
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
  enterRule(_localctx, 34, LLVMParser::RuleFunctionDefinition);
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
    setState(175);
    match(LLVMParser::Define);
    setState(176);
    type();
    setState(177);
    globalIdentifier();
    setState(178);
    functionArguments();
    setState(179);
    match(LLVMParser::LeftBrace);
    setState(183);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Label) {
      setState(180);
      basicBlock();
      setState(185);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(186);
    match(LLVMParser::RightBrace);
   
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
  enterRule(_localctx, 36, LLVMParser::RuleFunctionArguments);
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
    setState(188);
    match(LLVMParser::LeftParen);
    setState(190);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4503666736234496) != 0)) {
      setState(189);
      parameterList();
    }
    setState(192);
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
  enterRule(_localctx, 38, LLVMParser::RuleParameterList);
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
    setState(194);
    parameter();
    setState(199);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(195);
      match(LLVMParser::Comma);
      setState(196);
      parameter();
      setState(201);
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
  enterRule(_localctx, 40, LLVMParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    type();
    setState(203);
    localIdentifier();
   
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
  enterRule(_localctx, 42, LLVMParser::RuleBasicBlock);
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
    setState(205);
    match(LLVMParser::Label);
    setState(206);
    match(LLVMParser::Colon);
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36028797018969536) != 0)) {
      setState(207);
      instruction();
      setState(212);
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

LLVMParser::LoadInstructionContext* LLVMParser::InstructionContext::loadInstruction() {
  return getRuleContext<LLVMParser::LoadInstructionContext>(0);
}

LLVMParser::StoreInstructionContext* LLVMParser::InstructionContext::storeInstruction() {
  return getRuleContext<LLVMParser::StoreInstructionContext>(0);
}

LLVMParser::PhiInstructionContext* LLVMParser::InstructionContext::phiInstruction() {
  return getRuleContext<LLVMParser::PhiInstructionContext>(0);
}

LLVMParser::ComparisonInstructionContext* LLVMParser::InstructionContext::comparisonInstruction() {
  return getRuleContext<LLVMParser::ComparisonInstructionContext>(0);
}

LLVMParser::AllocaInstructionContext* LLVMParser::InstructionContext::allocaInstruction() {
  return getRuleContext<LLVMParser::AllocaInstructionContext>(0);
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
  enterRule(_localctx, 44, LLVMParser::RuleInstruction);

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
      setState(213);
      returnInstruction();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(214);
      branchInstruction();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(215);
      callInstruction();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(216);
      arithmeticInstruction();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(217);
      loadInstruction();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(218);
      storeInstruction();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(219);
      phiInstruction();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(220);
      comparisonInstruction();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(221);
      allocaInstruction();
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
  enterRule(_localctx, 46, LLVMParser::RuleReturnInstruction);

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
    match(LLVMParser::Ret);
    setState(225);
    type();
    setState(227);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(226);
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
  enterRule(_localctx, 48, LLVMParser::RuleBranchInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(229);
      match(LLVMParser::Br);
      setState(230);
      match(LLVMParser::I1);
      setState(231);
      value();
      setState(232);
      match(LLVMParser::Comma);
      setState(233);
      match(LLVMParser::Label);
      setState(234);
      unamedIdentifier();
      setState(235);
      match(LLVMParser::Comma);
      setState(236);
      match(LLVMParser::Label);
      setState(237);
      unamedIdentifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(239);
      match(LLVMParser::Br);
      setState(240);
      match(LLVMParser::Label);
      setState(241);
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

LLVMParser::UnamedIdentifierContext* LLVMParser::CallInstructionContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
}

tree::TerminalNode* LLVMParser::CallInstructionContext::Equals() {
  return getToken(LLVMParser::Equals, 0);
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
  enterRule(_localctx, 50, LLVMParser::RuleCallInstruction);
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
    setState(247);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Percent) {
      setState(244);
      unamedIdentifier();
      setState(245);
      match(LLVMParser::Equals);
    }
    setState(249);
    match(LLVMParser::Call);
    setState(250);
    type();
    setState(251);
    globalIdentifier();
    setState(252);
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

LLVMParser::UnamedIdentifierContext* LLVMParser::ArithmeticInstructionContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
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
  enterRule(_localctx, 52, LLVMParser::RuleArithmeticInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    unamedIdentifier();
    setState(255);
    match(LLVMParser::Equals);
    setState(256);
    binaryOperation();
    setState(257);
    type();
    setState(258);
    value();
    setState(259);
    match(LLVMParser::Comma);
    setState(260);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoadInstructionContext ------------------------------------------------------------------

LLVMParser::LoadInstructionContext::LoadInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::UnamedIdentifierContext* LLVMParser::LoadInstructionContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
}

tree::TerminalNode* LLVMParser::LoadInstructionContext::Equals() {
  return getToken(LLVMParser::Equals, 0);
}

tree::TerminalNode* LLVMParser::LoadInstructionContext::Load() {
  return getToken(LLVMParser::Load, 0);
}

std::vector<LLVMParser::TypeContext *> LLVMParser::LoadInstructionContext::type() {
  return getRuleContexts<LLVMParser::TypeContext>();
}

LLVMParser::TypeContext* LLVMParser::LoadInstructionContext::type(size_t i) {
  return getRuleContext<LLVMParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> LLVMParser::LoadInstructionContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::LoadInstructionContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}

tree::TerminalNode* LLVMParser::LoadInstructionContext::Asterisk() {
  return getToken(LLVMParser::Asterisk, 0);
}

LLVMParser::VariableContext* LLVMParser::LoadInstructionContext::variable() {
  return getRuleContext<LLVMParser::VariableContext>(0);
}

tree::TerminalNode* LLVMParser::LoadInstructionContext::Align() {
  return getToken(LLVMParser::Align, 0);
}

tree::TerminalNode* LLVMParser::LoadInstructionContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}


size_t LLVMParser::LoadInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleLoadInstruction;
}


std::any LLVMParser::LoadInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitLoadInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::LoadInstructionContext* LLVMParser::loadInstruction() {
  LoadInstructionContext *_localctx = _tracker.createInstance<LoadInstructionContext>(_ctx, getState());
  enterRule(_localctx, 54, LLVMParser::RuleLoadInstruction);
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
    setState(262);
    unamedIdentifier();
    setState(263);
    match(LLVMParser::Equals);
    setState(264);
    match(LLVMParser::Load);
    setState(265);
    type();
    setState(266);
    match(LLVMParser::Comma);
    setState(267);
    type();
    setState(268);
    match(LLVMParser::Asterisk);
    setState(269);
    variable();
    setState(273);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(270);
      match(LLVMParser::Comma);
      setState(271);
      match(LLVMParser::Align);
      setState(272);
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

//----------------- StoreInstructionContext ------------------------------------------------------------------

LLVMParser::StoreInstructionContext::StoreInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::StoreInstructionContext::Store() {
  return getToken(LLVMParser::Store, 0);
}

std::vector<LLVMParser::TypeContext *> LLVMParser::StoreInstructionContext::type() {
  return getRuleContexts<LLVMParser::TypeContext>();
}

LLVMParser::TypeContext* LLVMParser::StoreInstructionContext::type(size_t i) {
  return getRuleContext<LLVMParser::TypeContext>(i);
}

LLVMParser::ValueContext* LLVMParser::StoreInstructionContext::value() {
  return getRuleContext<LLVMParser::ValueContext>(0);
}

std::vector<tree::TerminalNode *> LLVMParser::StoreInstructionContext::Comma() {
  return getTokens(LLVMParser::Comma);
}

tree::TerminalNode* LLVMParser::StoreInstructionContext::Comma(size_t i) {
  return getToken(LLVMParser::Comma, i);
}

tree::TerminalNode* LLVMParser::StoreInstructionContext::Asterisk() {
  return getToken(LLVMParser::Asterisk, 0);
}

LLVMParser::VariableContext* LLVMParser::StoreInstructionContext::variable() {
  return getRuleContext<LLVMParser::VariableContext>(0);
}

tree::TerminalNode* LLVMParser::StoreInstructionContext::Align() {
  return getToken(LLVMParser::Align, 0);
}

tree::TerminalNode* LLVMParser::StoreInstructionContext::IntegerLiteral() {
  return getToken(LLVMParser::IntegerLiteral, 0);
}


size_t LLVMParser::StoreInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleStoreInstruction;
}


std::any LLVMParser::StoreInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitStoreInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::StoreInstructionContext* LLVMParser::storeInstruction() {
  StoreInstructionContext *_localctx = _tracker.createInstance<StoreInstructionContext>(_ctx, getState());
  enterRule(_localctx, 56, LLVMParser::RuleStoreInstruction);
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
    match(LLVMParser::Store);
    setState(276);
    type();
    setState(277);
    value();
    setState(278);
    match(LLVMParser::Comma);
    setState(279);
    type();
    setState(280);
    match(LLVMParser::Asterisk);
    setState(281);
    variable();
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LLVMParser::Comma) {
      setState(282);
      match(LLVMParser::Comma);
      setState(283);
      match(LLVMParser::Align);
      setState(284);
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
  enterRule(_localctx, 58, LLVMParser::RulePhiInstruction);
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
    setState(287);
    match(LLVMParser::Phi);
    setState(288);
    type();
    setState(289);
    phiValue();
    setState(294);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LLVMParser::Comma) {
      setState(290);
      match(LLVMParser::Comma);
      setState(291);
      phiValue();
      setState(296);
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
  enterRule(_localctx, 60, LLVMParser::RulePhiValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(LLVMParser::LeftBrace);
    setState(298);
    unamedIdentifier();
    setState(299);
    match(LLVMParser::Comma);
    setState(300);
    value();
    setState(301);
    match(LLVMParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonOperationContext ------------------------------------------------------------------

LLVMParser::ComparisonOperationContext::ComparisonOperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LLVMParser::ComparisonOperationContext::Icmp() {
  return getToken(LLVMParser::Icmp, 0);
}

tree::TerminalNode* LLVMParser::ComparisonOperationContext::Fcmp() {
  return getToken(LLVMParser::Fcmp, 0);
}


size_t LLVMParser::ComparisonOperationContext::getRuleIndex() const {
  return LLVMParser::RuleComparisonOperation;
}


std::any LLVMParser::ComparisonOperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitComparisonOperation(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::ComparisonOperationContext* LLVMParser::comparisonOperation() {
  ComparisonOperationContext *_localctx = _tracker.createInstance<ComparisonOperationContext>(_ctx, getState());
  enterRule(_localctx, 62, LLVMParser::RuleComparisonOperation);
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
    setState(303);
    _la = _input->LA(1);
    if (!(_la == LLVMParser::Icmp

    || _la == LLVMParser::Fcmp)) {
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

//----------------- ComparisonInstructionContext ------------------------------------------------------------------

LLVMParser::ComparisonInstructionContext::ComparisonInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::UnamedIdentifierContext* LLVMParser::ComparisonInstructionContext::unamedIdentifier() {
  return getRuleContext<LLVMParser::UnamedIdentifierContext>(0);
}

tree::TerminalNode* LLVMParser::ComparisonInstructionContext::Equals() {
  return getToken(LLVMParser::Equals, 0);
}

LLVMParser::ComparisonOperationContext* LLVMParser::ComparisonInstructionContext::comparisonOperation() {
  return getRuleContext<LLVMParser::ComparisonOperationContext>(0);
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
  enterRule(_localctx, 64, LLVMParser::RuleComparisonInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    unamedIdentifier();
    setState(306);
    match(LLVMParser::Equals);
    setState(307);
    comparisonOperation();
    setState(308);
    comparisonPredicate();
    setState(309);
    type();
    setState(310);
    value();
    setState(311);
    match(LLVMParser::Comma);
    setState(312);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocaInstructionContext ------------------------------------------------------------------

LLVMParser::AllocaInstructionContext::AllocaInstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LLVMParser::LocalIdentifierContext* LLVMParser::AllocaInstructionContext::localIdentifier() {
  return getRuleContext<LLVMParser::LocalIdentifierContext>(0);
}

tree::TerminalNode* LLVMParser::AllocaInstructionContext::Equals() {
  return getToken(LLVMParser::Equals, 0);
}

tree::TerminalNode* LLVMParser::AllocaInstructionContext::Alloca() {
  return getToken(LLVMParser::Alloca, 0);
}

LLVMParser::TypeContext* LLVMParser::AllocaInstructionContext::type() {
  return getRuleContext<LLVMParser::TypeContext>(0);
}


size_t LLVMParser::AllocaInstructionContext::getRuleIndex() const {
  return LLVMParser::RuleAllocaInstruction;
}


std::any LLVMParser::AllocaInstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LLVMParserVisitor*>(visitor))
    return parserVisitor->visitAllocaInstruction(this);
  else
    return visitor->visitChildren(this);
}

LLVMParser::AllocaInstructionContext* LLVMParser::allocaInstruction() {
  AllocaInstructionContext *_localctx = _tracker.createInstance<AllocaInstructionContext>(_ctx, getState());
  enterRule(_localctx, 66, LLVMParser::RuleAllocaInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    localIdentifier();
    setState(315);
    match(LLVMParser::Equals);
    setState(316);
    match(LLVMParser::Alloca);
    setState(317);
    type();
   
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
  enterRule(_localctx, 68, LLVMParser::RuleBinaryOperation);
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
    setState(319);
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
  enterRule(_localctx, 70, LLVMParser::RuleComparisonPredicate);
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
    setState(321);
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
    case 3: return pointerTypeSempred(antlrcpp::downCast<PointerTypeContext *>(context), predicateIndex);

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
