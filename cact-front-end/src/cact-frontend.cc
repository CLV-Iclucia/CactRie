//
// Created by creeper on 8/15/24.
//

#include <cact-front-end/symbol-registration-visitor.h>
#include <cact-front-end/cact-syntax-error-listener.h>

bool lexical_syntax_analysis(antlr4::tree::ParseTree * &tree, cactfrontend::CactParser parser,
                             cactfrontend::CactSyntaxErrorListener cact_error_listener) {
  try {
    tree = parser.compilationUnit();

    // if error
    if (cact_error_listener.hasSyntaxError()) {
      std::cerr << "Syntax error(s) found in the source file. Compilation failed." << std::endl;
      return 1;
    }
    return 0;
  } catch (const std::exception &ex) {
    std::cerr << "Parsing failed: " << ex.what() << std::endl;
    return 1;
  }
}

// a function to check if the type of the expression is valid
bool semantic_analysis(antlr4::tree::ParseTree *tree) {

  cactfrontend::SymbolRegistrationErrorCheckVisitor visitor;
  
  // check if there is any syntax error
    try {
      visitor.visit(tree);
      std::cout << "Syntax check completed." << std::endl;
      return 0;
    } catch (const std::exception &ex) {
      std::cerr << "Syntax error(s) found in the source file. Compilation failed." << std::endl;
      std::cerr << ex.what() << std::endl;
      return 1;
    }
}
