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
  std::unordered_map<observer_ptr<Scope>, size_t> scopeIDMap{};
  std::string rename(std::shared_ptr<CactConstVar> var) {
    const auto& name = var->name;
    auto scope = var->scope;
    if (!scopeIDMap.contains(scope))
      scopeIDMap[scope] = scopeIDMap.size();

    size_t scopeID = scopeIDMap[scope];

    return name + ".b." + std::to_string(scopeID);
  }
  void clear() {
    scopeIDMap.clear();
  }
};

// struct to generate IR code
struct LLVMIRGenerator final : public CactBaseVisitor {
  // constructor, initialize the output stream and the name of the module
  explicit LLVMIRGenerator(std::ostream &os, const std::string &name, std::shared_ptr<SymbolRegistry> registry)
      : irCodeStream(os), moduleName(name), registry(std::move(registry)) {}

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

  std::any visitDeclaration(CactParser::DeclarationContext *ctx) override;

private:

  void allocateVariable(std::shared_ptr<CactConstVar> var, const std::string &newName);

  void allocateLocalVariables(CactParser::BlockContext *block);

  void allocateLocalVariables(CactParser::BlockContext *block, int depth);

  struct EvaluationCodegenResult {
    std::string code;
    std::string result;
  };

  enum IndexResolvingMode {
    Address,
    Value
  };

  EvaluationCodegenResult fetchAddressCodeGen(std::shared_ptr<CactExpr> expr);
  EvaluationCodegenResult evaluationCodeGen(std::shared_ptr<CactExpr> expr);
  EvaluationCodegenResult indexOpCodeGen(std::shared_ptr<CactExpr> lhs, std::shared_ptr<CactExpr> rhs, IndexResolvingMode);
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
  std::string rename(std::shared_ptr<CactConstVar> var) {
    return localIdentifierMangler.rename(var);
  }
  std::string addressOf(std::shared_ptr<CactConstVar> var) {
    return registry->isGlobal(var) ? "@" : "%" + rename(var);
  }
  std::string temporaryName(int id) {
    return std::to_string(id);
  }

  std::string assignReg() {
    return temporaryName(temporaryID++);
  }

  int temporaryID = 0;
  std::vector<int> ifID{};
  std::vector<int> whileID{};
  LocalIdentifierMangler localIdentifierMangler{};
  std::ostream &irCodeStream;
  std::string moduleName;
  std::shared_ptr<SymbolRegistry> registry{};
  std::string returnStatementIRGen(const std::string &labelPrefix, CactParser::ReturnStatementContext *ctx);
  LLVMIRGenerator::EvaluationCodegenResult variableEvaluationCodeGen(std::shared_ptr<CactConstVarArray> SharedPtr);
};

}
#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_IR_GENERATOR_H
