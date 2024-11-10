//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
#include <cact-front-end/CactParserBaseVisitor.h>
#include <cact-front-end/symbol-registry.h>
#include <cact-front-end/cact-parser-context.h>

#include <stack>


namespace cactfrontend {


// A visitor to register symbols
struct SymbolRegistrationErrorCheckVisitor : public CactParserBaseVisitor {

  // declarations
  CactBasicType getDataType(DataTypeCtx *ctx);
  std::vector<ConstEvalResult> getConstIniVal(ConstantInitialValueCtx *ctx);
  bool hasConstExpr(ConstantInitialValueCtx *ctx);
  void enterScope(observer_ptr<Scope> scope);
  void leaveScope();
  CactBasicType getFuncType(FunctionTypeCtx *ctx);
  FuncParameters getFuncParams(FunctionFormalParamsCtx *ctx);
  FuncParameter getFuncParam(FunctionFormalParamCtx *ctx);

  // Constructor: initialize the symbol registry
  SymbolRegistrationErrorCheckVisitor() : registry(std::make_unique<SymbolRegistry>()) {}

  // visit a compilation unit
  std::any visitCompilationUnit(CompilationUnitCtx *ctx) override {
    currentScope = registry->createGlobalScope();
    for (auto &child : ctx->children)
      visit(child);
    return {};
  }

  std::any visitConstantDeclaration(ConstantDeclarationCtx *ctx) override {
    // record the basic type
    auto basicType = getDataType(ctx->dataType());

    // visit all constantDefinitions
    for (auto &constDef : ctx->constantDefinition()){
      constDef->needType = basicType;
      visit(constDef);
    }
    return {};
  }

  std::any visitDataType(DataTypeCtx *ctx) override {
    if (ctx->Int32())       return CactBasicType::Int32;
    else if (ctx->Bool())   return CactBasicType::Bool;
    else if (ctx->Float())  return CactBasicType::Float;
    else if (ctx->Double()) return CactBasicType::Double;
    else
      throw std::runtime_error("Invalid data type context");
    return {};
  }

  CactBasicType getDataType(DataTypeCtx *ctx) {
    return std::any_cast<CactBasicType>(visit(ctx));
  }

  std::any visitConstantDefinition(ConstantDefinitionCtx *ctx) override {
    // record name, basicType and arrayDims
    auto name = ctx->Identifier()->getText();
    CactType type = CactType::constType(ctx->needType);
    for (auto &dimCtx : ctx->IntegerConstant()) {
      type.arrayDims.push_back(std::stoi(dimCtx->getText())); // TODO: can it convert binary or hex?
      if (type.arrayDims.back() <= 0) // dimension should be positive
        throw std::runtime_error("Invalid width of array dimension");
    }

    // set some attributes for constantInitialValue, visit it and get the result
    auto constInitVal = ctx->constantInitialValue();
    constInitVal->currentDim = 0;
    constInitVal->basicType = type.basicType;
    constInitVal->arrayDims = type.arrayDims;
    // auto value = getConstIniVal(constInitVal);
    visit(constInitVal);

    // register the constant
    currentScope->registerVariable(name, type);
  }

  std::any visitConstantInitialValue(ConstantInitialValueCtx *ctx) override {
    // if it is a constant expression, check the value's type
    uint32_t currentDim = ctx->currentDim;
    CactBasicType basicType = ctx->basicType;
    std::vector<uint32_t> arrayDims = ctx->arrayDims;

    auto constExpr = ctx->constantExpression();
    if (constExpr) {
      if (currentDim != arrayDims.size())
        throw std::runtime_error("Invalid array dimension");
      visit(constExpr);
      if (basicType != constExpr->basicType)
        throw std::runtime_error("Invalid type of constant expression");
    }

    // if it is an array
    else {
      if (currentDim >= arrayDims.size())
        throw std::runtime_error("Invalid array dimension");

      // count the number of child in constantInitialValue() array
      uint32_t count = ctx->constantInitialValue().size();

      // set default attributes of children -- constant initial values
      for (auto &child : ctx->constantInitialValue()) {
        child->currentDim = currentDim + 1;
        child->basicType = basicType;
        child->arrayDims = arrayDims;
      }

      // check if the initial value could be a flat array
      bool flatFlag = false;
      if (count == arrayDims[currentDim] && currentDim == 0) {
        flatFlag = true;
        // check for constant expressions among all children
        for (auto &child : ctx->constantInitialValue()) {
          if (!hasConstExpr(child)) {
            flatFlag = false;
            break;
          }
        }
      }

      // case (1): if the initial value is a flat array, reset currentDim of children and visit them
      if (flatFlag) {
        for (auto &child : ctx->constantInitialValue()) {
          child->currentDim = arrayDims.size();
        }
      }
      // case (2): count result is exactly arrayDims[currentDim]
      else if (0 <= currentDim && currentDim < arrayDims.size() - 1) { // certain outer dimension
        if (count != arrayDims[currentDim])
          throw std::runtime_error("Invalid array width of certain dimension");
      }
      // case (3): count result is exactly arrayDims[currentDim]
      else if (currentDim == arrayDims.size() - 1) { // the innermost dimension
        if (count > arrayDims[currentDim])
          throw std::runtime_error("Invalid array width of certain dimension");
      }
      else {
        throw std::runtime_error("Constant value initialization: unknown error");
      }

      // visit all children
      for (auto &child : ctx->constantInitialValue()) {
        visit(child);
      }

    }
    return {};
  }

  bool hasConstExpr(ConstantInitialValueCtx *ctx) {
    return ctx->constantExpression() != nullptr;
  }

  // std::vector<ConstEvalResult> getConstIniVal(ConstantInitialValueCtx *ctx) {
  //   return std::any_cast<std::vector<ConstEvalResult>>(visit(ctx));
  // }

  std::any visitVariableDeclaration(VariableDeclarationCtx *ctx) override {
    // record the basic type
    auto basicType = getDataType(ctx->dataType());

    // visit all variableDefinitions
    for (auto &varDef : ctx->variableDefinition()){
      varDef->needType = basicType;
      visit(varDef);
    }
    return {};
  }

  // visit a variable definition
  std::any visitVariableDefinition(VariableDefinitionCtx *ctx) override {
    // record name, basicType and arrayDims
    auto name = ctx->Identifier()->getText();
    CactType type = CactType::varType(ctx->needType);
    for (auto &dimCtx : ctx->IntegerConstant()) {
      type.arrayDims.push_back(std::stoi(dimCtx->getText())); // TODO: can it convert binary or hex?
      if (type.arrayDims.back() <= 0) // dimension should be positive
        throw std::runtime_error("Invalid width of array dimension");
    }

    // set some attributes for constantInitialValue, visit it and get the result
    auto constInitVal = ctx->constantInitialValue();
    if (constInitVal) {
      type.initialized = true; // set initialized flag

      constInitVal->currentDim = 0;
      constInitVal->basicType = type.basicType;
      constInitVal->arrayDims = type.arrayDims;
      // auto value = getConstIniVal(constInitVal);
      visit(constInitVal);
    }

    // register the constant
    currentScope->registerVariable(name, type);
  }

  // enter a new scope
  void enterScope(observer_ptr<Scope> scope) {
    scope = registry->newScope();
    scope.get()->setParent(currentScope);
    currentScope = scope;
  }

  // leave the current scope
  void leaveScope() {
    currentScope = currentScope.get()->getParent();
  }

  // visit a function definition
  std::any visitFunctionDefinition(FunctionDefinitionCtx *ctx) override {
    // create a new scope
    enterScope(ctx->scope);

    // record the function's return data type and name 
    CactFunction function;
    function.returnType = getFuncType(ctx->functionType());
    function.name = ctx->Identifier()->getText();

    // visit the function's formal parameters
    function.parameters = getFuncParams(ctx->functionFormalParams());

    // register all formal parameters in the scope
    for (auto &param : function.parameters) {
      CactType var = CactType::paramType(param.basicType, param.arrayDims);
      ctx->scope->registerVariable(param.name, var);
    }

    // create a new function
    registry->newFunction(function);
    currentFunction = make_observer(&function);

    // visit the block
    visit(ctx->block());

    leaveScope();
    return {};
  }

  // get the function type
  CactBasicType getFuncType(FunctionTypeCtx *ctx) {
    return std::any_cast<CactBasicType>(visit(ctx));
  }

  std::any visitFunctionType(FunctionTypeCtx *ctx) override {
    if      (ctx->Void())   return CactBasicType::Void;
    else if (ctx->Int32())  return CactBasicType::Int32;
    else if (ctx->Bool())   return CactBasicType::Bool;
    else if (ctx->Float())  return CactBasicType::Float;
    else if (ctx->Double()) return CactBasicType::Double;
    else
      throw std::runtime_error("Invalid function type context");
    return {};
  }

  FuncParameters getFuncParams(FunctionFormalParamsCtx *ctx) {
    if (ctx == nullptr)
      return FuncParameters();
    return std::any_cast<FuncParameters>(visit(ctx));
  }

  std::any visitFunctionFormalParams(FunctionFormalParamsCtx *ctx) override {
    FuncParameters params;
    for (auto &param : ctx->functionFormalParam()) {
      params.push_back(std::any_cast<FuncParameter>(visit(param)));
    }
    return params;
  }

  FuncParameter getFuncParam(FunctionFormalParamCtx *ctx) {
    if (ctx == nullptr)
      return FuncParameter();
    return std::any_cast<FuncParameter>(visit(ctx));
  }

  std::any visitFunctionFormalParam(FunctionFormalParamCtx *ctx) override {
    // record basic type and name
    FuncParameter param;
    param.basicType = getDataType(ctx->dataType());
    param.name = ctx->Identifier()->getText();

    // if the first pair of brackets is empty, push 0 to the arrayDims
    if (ctx->IntegerConstant().size() < ctx->LeftBracket().size())
      param.arrayDims.push_back(0);

    // record the array dimensions
    for (auto &dimCtx : ctx->IntegerConstant()) {
      param.arrayDims.push_back(std::stoi(dimCtx->getText())); // TODO: can it convert binary or hex?
      if (param.arrayDims.back() <= 0) // dimension should be positive
        throw std::runtime_error("Invalid width of array dimension");
    }

    return param;
  }

  // visit a block
  std::any visitBlock(BlockCtx *ctx) override {
    // create a new scope
    enterScope(ctx->scope);

    ctx->hasReturn = false;
    // visit all block items
    for (auto &item : ctx->blockItem()) {
      visit(item);
      if (item->hasReturn)
        ctx->hasReturn = true;
    }

    leaveScope();
    return {};
  }

  // visit a blockItem
  std::any visitBlockItem(BlockItemCtx *ctx) override {
    ctx->hasReturn = false;

    // visit the declaration
    if (ctx->declaration()) {
      visit(ctx->declaration());
    }
    // visit the statement
    else {
      visit(ctx->statement());
      ctx->hasReturn = ctx->statement()->hasReturn;
    }

    return {};
  }

  // visitting a statement
  std::any visitStatement(StatementCtx *ctx) override {
    // visit children[0] since statement has only one child
    visit(ctx->children[0]);

    // check return status
    if (ctx->block())
      ctx->hasReturn = ctx->block()->hasReturn;
    else if (ctx->ifStatement())
      ctx->hasReturn = ctx->ifStatement()->hasReturn;
    else if (ctx->returnStatement())
      ctx->hasReturn = true;
    else
      ctx->hasReturn = false;
    return {};
  }

  // visit a assign statement
  std::any visitAssignStatement(AssignStatementCtx *ctx) override {
    LeftValueCtx *leftValue = ctx->leftValue();
    ExpressionCtx *expression = ctx->expression();

    // visit nodes
    visit(leftValue);
    visit(expression);

    // check type compatibility
    if (leftValue->basicType != expression->basicType)
      throw std::runtime_error("Type mismatch in assignment");

    return {};
  }

  // visitting a expressionStatement does not need to be overrided

  // visit a return statement
  std::any visitReturnStatement(ReturnStatementCtx *ctx) override {
    // visit the expression
    visit(ctx->expression());

    // check return type
    if (ctx->expression() == nullptr) {
      if (currentFunction->returnType != CactBasicType::Void)
        throw std::runtime_error("Return type mismatch");
    }
    else {
      if (ctx->expression()->basicType != currentFunction->returnType)
        throw std::runtime_error("Return type mismatch");
    }

    // record function for return statement
    ctx->retFunction = currentFunction;

    return {};
  }

  // visit a if statement
  std::any visitIfStatement(IfStatementCtx *ctx) override {
    // visit the condition
    visit(ctx->condition());

    // visit the statement
    visit(ctx->statement(0));
    ctx->hasReturn = ctx->statement(0)->hasReturn;

    // visit the else statement
    if (ctx->Else()) {
      // visit the statement
      visit(ctx->statement(1));
      ctx->hasReturn = ctx->hasReturn && ctx->statement(1)->hasReturn;
    }

    return {};
  }

  // visit while statement
  std::any visitWhileStatement(WhileStatementCtx *ctx) override {
    // visit the condition
    visit(ctx->condition());

    // visit the statement
    whileLoopStack.push(make_observer(ctx));
    visit(ctx->statement());
    whileLoopStack.pop();

    return {};
  }

  // visit break statement
  std::any visitBreakStatement(BreakStatementCtx *ctx) override {
    // check if the break statement is in a loop
    if (whileLoopStack.empty())
      throw std::runtime_error("Break statement not in a loop");

    // record the loop to break
    ctx->loopToBreak = whileLoopStack.top();

    return {};
  }

  // visit continue statement
  std::any visitContinueStatement(ContinueStatementCtx *ctx) override {
    // check if the continue statement is in a loop
    if (whileLoopStack.empty())
      throw std::runtime_error("Continue statement not in a loop");

    // record the loop to continue
    ctx->loopToBreak = whileLoopStack.top();

    return {};
  }


private:
  std::unique_ptr<SymbolRegistry> registry;
  observer_ptr<Scope> currentScope;
  std::stack<observer_ptr<WhileStatementCtx>> whileLoopStack;
  observer_ptr<CactFunction> currentFunction;
};

}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
