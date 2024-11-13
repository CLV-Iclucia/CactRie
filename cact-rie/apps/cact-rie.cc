#include <iostream>
#include <fstream>
#include <cact-front-end/CactLexer.h>
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-syntax-error-listener.h>
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
  cactfrontend::CactLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  cactfrontend::CactParser parser(&tokens);
  lexer.removeErrorListeners();
  parser.removeErrorListeners();
  cactfrontend::CactSyntaxErrorListener cact_error_listener(argv[1]);
  lexer.addErrorListener(&cact_error_listener);
  parser.addErrorListener(&cact_error_listener);
  try {
    antlr4::tree::ParseTree *tree = parser.compilationUnit();

    // print the parse tree
    std::cout << tree->toStringTree(&parser) << std::endl;

    // call function to check if there is any static syntax error
    // auto *root = ;

    
    if (cact_error_listener.hasSyntaxError()) {
      std::cerr << "Syntax error(s) found in the source file. Compilation failed." << std::endl;
      return 1;
    }
  } catch (const std::exception &ex) {
    std::cerr << "Parsing failed: " << ex.what() << std::endl;
    return 1;
  }

  return 0;
}
