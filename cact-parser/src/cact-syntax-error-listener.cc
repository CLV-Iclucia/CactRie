//
// Created by creeper on 7/24/24.
//
#include <cact-parser/cact-syntax-error-listener.h>
#include <format>
namespace cactparser {
void CactSyntaxErrorListener::syntaxError(antlr4::Recognizer *recognizer,
                                          antlr4::Token *offendingSymbol,
                                          size_t line,
                                          size_t charPositionInLine,
                                          const std::string &msg,
                                          std::exception_ptr e) {
  std::cerr << std::format("うるさい！第{}行の{}文字目に文法エラーが発見された: {}", line, charPositionInLine, msg) << std::endl;
}

}