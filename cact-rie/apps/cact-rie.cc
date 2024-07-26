#include <iostream>
#include <fstream>
#include <cact-parser/CactLexer.h>
#include <cact-parser/CactParser.h>
#include <cact-parser/cact-syntax-error-listener.h>
#include <antlr-runtime/ANTLRInputStream.h>
#include <antlr-runtime/CommonTokenStream.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
    return 1;
  }
  std::ifstream stream(argv[1]);
  if (!stream) {
    std::cerr << "Failed to open file: " << argv[1] << std::endl;
    return 1;
  }
  antlr4::ANTLRInputStream input(stream);
  cactparser::CactLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  cactparser::CactParser parser(&tokens);
  lexer.removeErrorListeners();
  parser.removeErrorListeners();
  cactparser::CactSyntaxErrorListener cact_error_listener;
  lexer.addErrorListener(&cact_error_listener);
  parser.addErrorListener(&cact_error_listener);
  try {
    antlr4::tree::ParseTree *tree = parser.compilationUnit();
    std::cout << tree->toStringTree(&parser, true) << std::endl;
  } catch (const std::exception &ex) {
    std::cerr << "Parsing failed: " << ex.what() << std::endl;
  }

  return 0;
}
