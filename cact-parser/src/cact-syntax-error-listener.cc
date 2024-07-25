//
// Created by creeper on 7/24/24.
//
#include <cact-parser/cact-syntax-error-listener.h>
namespace cactparser {
void CactSyntaxErrorListener::syntaxError(antlr4::Recognizer *recognizer,
                                          antlr4::Token *offendingSymbol,
                                          size_t line,
                                          size_t charPositionInLine,
                                          const std::string &msg,
                                          std::exception_ptr e) {
  std::cerr << "Syntax error at line " << line << ":" << charPositionInLine << " " << msg << std::endl;
}

}