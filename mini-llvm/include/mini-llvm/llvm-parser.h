//
// Created by creeper on 8/24/24.
//

#ifndef CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_MINI_LLVM_LLVM_PARSER_H
#define CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_MINI_LLVM_LLVM_PARSER_H
#include "llvm-ir.h"
namespace llvm {
struct LLVMParser {
  explicit LLVMParser(const std::string &source) : source(source) {}
  std::unique_ptr<Module> parse();
private:
  std::unique_ptr<Module> module{};
  const std::string& source;
};
}
#endif //CACTRIE_CACT_RIE_INCLUDE_CACT_RIE_MINI_LLVM_LLVM_PARSER_H
