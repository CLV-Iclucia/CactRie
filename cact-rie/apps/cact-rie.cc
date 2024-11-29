#include <iostream>
#include <fstream>
#include <cact-front-end/CactLexer.h>
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-syntax-error-listener.h>
#include <cact-front-end/symbol-registration-visitor.h>
#include <cact-front-end/const-eval-and-expression-generation.h>
#include <antlr-runtime/ANTLRInputStream.h>
#include <antlr-runtime/CommonTokenStream.h>
#include <cxxopts.hpp>
#include <cact-front-end/ir-generator.h>
// declarations
// extern bool lexical_syntax_analysis(antlr4::tree::ParseTree * &tree, std::ifstream &stream, std::string source_file_name);
// extern bool semantic_analysis(antlr4::tree::ParseTree *tree);

auto configOptions(char *argv[]) {
  cxxopts::Options options(argv[0], "Cact compiler, your best tsundere girlfriend!");
  options.add_options()
      ("emit-llvm", "Emit LLVM IR", cxxopts::value<bool>()->default_value("true"))
      ("h,help", "Print help");
  options.allow_unrecognised_options();
  return options;
}

int compileToLLVM(const std::filesystem::path& file) {
  std::ifstream stream(file);
  if (!stream) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return 1;
  }

  // print the source file's content
  std::ifstream streamCopy(file);
  std::cout << "Source file content:" << std::endl;
  std::cout << streamCopy.rdbuf() << std::endl;

  antlr4::tree::ParseTree *tree;

  antlr4::ANTLRInputStream input(stream);
  cactfrontend::CactLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  cactfrontend::CactParser parser(&tokens);
  lexer.removeErrorListeners();
  parser.removeErrorListeners();

  cactfrontend::CactSyntaxErrorListener cact_error_listener(file);
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

  // check if there is any syntax error
  cactfrontend::SymbolRegistrationErrorCheckVisitor symbolRegistrationVisitor;

  // check if there is any semantic error
  try {
    symbolRegistrationVisitor.visit(tree);
    std::cout << "Semantic check completed." << std::endl;
  }
  catch (const std::exception &ex) {
    std::cerr << "Semantic error(s) found in the source file. Compilation failed." << std::endl;
    std::cerr << ex.what() << std::endl;
    return 1;
  }

  auto constEvalVisitor = cactfrontend::ConstEvalVisitor(symbolRegistrationVisitor.registry);

  // evaluate constant expression and generate expression tree in the tree nodes
  try {
    constEvalVisitor.visit(tree);
    std::cout << "Expression generation completed." << std::endl;
  }
  catch (const std::exception &ex) {
    std::cerr << "Semantic error(s) found in the source file. Compilation failed." << std::endl;
    std::cerr << ex.what() << std::endl;
    return 1;
  }

  auto srcFileName = file.stem().string();
  auto irCodeStream = std::ofstream(srcFileName + ".ll");
  auto llvmIRGenerator = cactfrontend::LLVMIRGenerator(irCodeStream, srcFileName, symbolRegistrationVisitor.registry);
  try {
    llvmIRGenerator.visit(tree);
    irCodeStream.close();
    std::cout << "IR generation completed." << std::endl;
  }
  catch (const std::exception &ex) {
    std::cerr << "IR generation failed." << std::endl;
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {

  auto options = configOptions(argv);
  auto args = options.parse(argc, argv);
  if (args.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }
  const auto& unmatched = args.unmatched();

  if (unmatched.empty()) {
    std::cerr << "Please provide a source file." << std::endl;
    return 1;
  }

  if (unmatched.size() > 1) {
    std::cerr << "Please provide only one source file." << std::endl;
    return 1;
  }

  if (!args["emit-llvm"].as<bool>())
    return 0;

  std::cout << "Compiling " << unmatched[0] << std::endl;
  std::filesystem::path sourceFilePath(unmatched[0]);
  if (!std::filesystem::exists(sourceFilePath)) {
    std::cerr << "Source file does not exist." << std::endl;
    return 1;
  }
  return compileToLLVM(sourceFilePath);
}
