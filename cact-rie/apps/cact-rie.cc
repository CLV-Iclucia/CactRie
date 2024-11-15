#include <iostream>
#include <fstream>
#include <cact-front-end/CactLexer.h>
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-syntax-error-listener.h>
// #include <cact-front-end/cact-symbol-registration-visitor.h>
#include <antlr-runtime/ANTLRInputStream.h>
#include <antlr-runtime/CommonTokenStream.h>

// declarations
extern bool lexical_syntax_analysis(antlr4::tree::ParseTree * &tree, cactfrontend::CactParser parser,
                                    cactfrontend::CactSyntaxErrorListener cact_error_listener);
extern bool semantic_analysis(antlr4::tree::ParseTree *tree);

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

  // print the source file's content
  std::ifstream streamCopy(argv[1]);
  std::cout << "Source file content:" << std::endl;
  std::cout << streamCopy.rdbuf() << std::endl;

  antlr4::ANTLRInputStream input(stream);
  cactfrontend::CactLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  cactfrontend::CactParser parser(&tokens);
  lexer.removeErrorListeners();
  parser.removeErrorListeners();

  cactfrontend::CactSyntaxErrorListener cact_error_listener(argv[1]);
  lexer.addErrorListener(&cact_error_listener);
  parser.addErrorListener(&cact_error_listener);

  antlr4::tree::ParseTree * tree;
  if (lexical_syntax_analysis(tree, parser, cact_error_listener))
    return 1;

  // // print the parse tree
  // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  // call function to perform semantic analysis
  semantic_analysis(tree);


  return 0;
}
