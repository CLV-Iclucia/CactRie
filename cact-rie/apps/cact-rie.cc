#include <iostream>
#include <fstream>
#include <cact-front-end/CactLexer.h>
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-syntax-error-listener.h>
#include <cact-front-end/symbol-registration-visitor.h>
#include <cact-front-end/const-eval-and-expression-generation.h>
#include <antlr-runtime/ANTLRInputStream.h>
#include <antlr-runtime/CommonTokenStream.h>

// declarations
// extern bool lexical_syntax_analysis(antlr4::tree::ParseTree * &tree, std::ifstream &stream, std::string source_file_name);
// extern bool semantic_analysis(antlr4::tree::ParseTree *tree);

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


  antlr4::tree::ParseTree * tree;

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
    tree = parser.compilationUnit();

    // if error
    if (cact_error_listener.hasSyntaxError()) {
      std::cerr << "Syntax error(s) found in the source file. Compilation failed." << std::endl;
      return 1;
    }
  }
  catch (const std::exception &ex) {
    std::cerr << "Parsing failed: " << ex.what() << std::endl;
    return 1;
  }

  // // print the parse tree
  // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  // call function to perform semantic analysis


  cactfrontend::SymbolRegistrationErrorCheckVisitor visitor_pass1;
  
  // check if there is any semantic error
  // try {
    visitor_pass1.visit(tree);
    std::cout << "Semantic check completed." << std::endl;
  // }
  // catch (const std::exception &ex) {
  //   std::cerr << "Semantic error(s) found in the source file. Compilation failed." << std::endl;
  //   std::cerr << ex.what() << std::endl;
  //   return 1;
  // }

  auto visitor_pass2 = cactfrontend::ConstEvalVisitor(visitor_pass1.registry);

  // evaluate constant expression and generate expression tree in the tree nodes
  // try {
    visitor_pass2.visit(tree);
    std::cout << "Expression generation completed." << std::endl;
  // }
  // catch (const std::exception &ex) {
  //   std::cerr << "Semantic error(s) found in the source file. Compilation failed." << std::endl;
  //   std::cerr << ex.what() << std::endl;
  //   return 1;
  // }


  return 0;
}
