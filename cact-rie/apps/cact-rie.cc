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
  antlr4::ANTLRInputStream input(stream);
  cactparser::CactLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  cactparser::CactParser parser(&tokens);

  return 0;
}
