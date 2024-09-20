//
// Created by creeper on 7/24/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_SYNTAX_ERROR_LISTENER_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_SYNTAX_ERROR_LISTENER_H_

#include <antlr-runtime/BaseErrorListener.h>
#include <filesystem>

namespace cactfrontend {
struct CactSyntaxErrorListener : public antlr4::BaseErrorListener {
  explicit CactSyntaxErrorListener(std::filesystem::path compiled_file_path) : compiled_file_path(std::move(
      compiled_file_path)) {}

  void syntaxError(antlr4::Recognizer *recognizer,
                   antlr4::Token *offendingSymbol,
                   size_t line,
                   size_t charPositionInLine,
                   const std::string &msg,
                   std::exception_ptr e) override;

  [[nodiscard]] bool hasSyntaxError() const { return has_syntax_error; }

 private:
  bool has_syntax_error{};
  std::filesystem::path compiled_file_path;
};
}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_SYNTAX_ERROR_LISTENER_H_
