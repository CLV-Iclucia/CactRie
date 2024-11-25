//
// Created by creeper on 11/13/24.
//
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/module-builder.h>
#include <chiisai-llvm/autogen/LLVMLexer.h>
#include <chiisai-llvm/autogen/LLVMParser.h>
#include <cxxopts.hpp>

auto parseArgs(int argc, char **argv) {
  // use cxxopts to parse command line arguments
  // the usage of chs-lli is similar to lli
  cxxopts::Options options("chs-lli", "Chiisai LLVM Interpreter");
  options.add_options()
      ("h,help", "Print help")
      ("f,file", "Input file", cxxopts::value<std::string>());
  auto result = options.parse(argc, argv);
  return result;
}

int main(int argc, char **argv) {
  auto parseResult = parseArgs(argc, argv);
  if (parseResult.count("help")) {
    std::cout << parseResult.help() << std::endl;
    return 0;
  }
  if (!parseResult.count("file")) {
    std::cerr << "No input file specified" << std::endl;
    return 1;
  }
  auto file = parseResult["file"].as<std::filesystem::path>();
  std::ifstream ifs(file);
  if (!ifs.is_open()) {
    std::cerr << "Cannot open file " << file << std::endl;
    return 1;
  }
  antlr4::ANTLRInputStream input(ifs);
  llvm::LLVMLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  llvm::LLVMParser parser(&tokens);
  auto tree = parser.module();
  llvm::ModuleBuilder builder;
  std::unique_ptr<llvm::Module> module{};
  std::unique_ptr<llvm::LLVMContext> llvmContext{};
  try {
    builder.visitModule(tree);
    std::tie(module, llvmContext) = builder.build();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  llvm::Executor executor(*module, *llvmContext);
  executor.execute(module);
}