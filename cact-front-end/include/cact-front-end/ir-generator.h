//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H

#include <sstream>
#include <format>
#include <cact-front-end/cact-base-visitor.h>
#include <cact-front-end/cact-operator.h>
#include <cact-front-end/const-eval-and-expression-generation.h>

namespace cactfrontend {

struct LocalIdentifierMangler {
  std::unordered_map<CactParser::BlockContext *, size_t> blockIDMap{};
  size_t nextBlockID = 0;
  std::string rename(const std::string &originalName, CactParser::BlockContext *block) {
    if (blockIDMap.find(block) == blockIDMap.end()) {
      blockIDMap[block] = nextBlockID++;
    }

    size_t blockID = blockIDMap[block];

    return originalName + ".b." + std::to_string(blockID);
  }
  void clear() {
    blockIDMap.clear();
    nextBlockID = 0;
  }
};

// struct to generate IR code
struct LLVMIRGenerator final : public CactBaseVisitor {
  // constructor, initialize the output stream and the name of the module
  explicit LLVMIRGenerator(std::ostream &os, const std::string &name) : irCodeStream(os), moduleName(name) {}

  // visit a compilation unit
  std::any visitCompilationUnit(CactParser::CompilationUnitContext *ctx) override {
    // output the module name
    irCodeStream << "; ModuleID = '"
                 << "'\nsource_filename = \""
                 << moduleName
                 << ".cact\"\n";
    for (auto &child : ctx->children)
      visit(child);
    return {};
  }

  std::string ifStatementIRGen(const std::string &labelPrefix, CactParser::IfStatementContext *ctx);

  std::string whileStatementIRGen(const std::string &labelPrefix, CactParser::WhileStatementContext *ctx);

  std::string statementIRGen(const std::string &labelPrefix, CactParser::StatementContext *ctx);

  std::any visitFunctionDefinition(CactParser::FunctionDefinitionContext *ctx) override;

private:

  void allocateLocalVariables(CactParser::BlockContext *block);

  void allocateLocalVariables(CactParser::BlockContext *block, int depth);

  struct EvaluationCodegenResult {
    std::string code;
    std::string resultName;
  };

  EvaluationCodegenResult evaluationCodeGen(std::shared_ptr<CactExpr> expr);

  static std::string basicTypeString(const CactBasicType &type) {
    static std::map<CactBasicType, std::string> typeMap = {
        {CactBasicType::Int32, "i32"},
        {CactBasicType::Float, "float"},
        {CactBasicType::Double, "double"},
        {CactBasicType::Bool, "i1"},
        {CactBasicType::Void, "void"}
    };
    return typeMap.at(type);
  }
  std::optional<CactParser::StatementContext *> reduceStatement(CactParser::StatementContext *ctx);

  // nullopt: cannot reduce
  // nullptr: reduce to empty statement, this while can be removed
  // statement: the statement to replace the while loop
  std::optional<CactParser::StatementContext *> reduceWhileLoop(CactParser::WhileStatementContext *ctx);

  // nullopt: cannot reduce
  // nullptr: reduce to empty statement, this if can be removed
  // statement: the statement to replace the if statement
  std::optional<CactParser::StatementContext *> reduceIfBranch(CactParser::IfStatementContext *ctx);
  std::string renameLocalIdentifier(const std::string &originalName, CactParser::BlockContext *block) {
    return localIdentifierMangler.rename(originalName, block);
  }
  std::string temporaryName(int id) {
    return std::to_string(id);
  }

  int temporaryID = 0;
  std::vector<int> ifID{};
  std::vector<int> whileID{};
  LocalIdentifierMangler localIdentifierMangler{};
  // and output stream to output the generated IR chars
  std::ostream &irCodeStream;
  std::string moduleName;
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
