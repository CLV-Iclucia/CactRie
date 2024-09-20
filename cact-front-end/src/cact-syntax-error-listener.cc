//
// Created by creeper on 7/24/24.
//
#include <cact-front-end/cact-syntax-error-listener.h>
#include <format>

namespace cactfrontend {
void CactSyntaxErrorListener::syntaxError(antlr4::Recognizer *recognizer,
                                          antlr4::Token *offendingSymbol,
                                          size_t line,
                                          size_t charPositionInLine,
                                          const std::string &msg,
                                          std::exception_ptr e) {
  has_syntax_error = true;
  std::cerr << std::format("うるさい！ファイル{}の第{}行の{}文字目に文法エラーが発見された: {}",
                           compiled_file_path.string(),
                           line,
                           charPositionInLine,
                           msg) << std::endl;
//  std::cerr << std::format("Как же раздражает! Ошибка синтаксиса найдена на {}-й строке, в {}-м символе: {}", line, charPositionInLine, msg) << std::endl;
}

}