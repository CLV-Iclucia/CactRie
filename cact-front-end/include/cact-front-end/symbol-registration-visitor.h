//
// Created by creeper on 8/23/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_SYMBOL_REGISTRATION_VISITOR_H
#include <cact-front-end/CactParserBaseVisitor.h>
#include <cact-front-end/symbol-registry.h>
#include <cact-front-end/cact-parser-context.h>
#include <cact-front-end/cact-operator.h>
#include <stack>
#include <string>


namespace cactfrontend {


// A visitor to register symbols
struct SymbolRegistrationErrorCheckVisitor : public CactParserBaseVisitor {

  // declarations
  // CactBasicType getDataType(DataTypeCtx *ctx);
  // std::vector<ConstEvalResult> getConstIniVal(ConstantInitialValueCtx *ctx);
  // bool hasConstExpr(ConstantInitialValueCtx *ctx);
  // void enterScope(observer_ptr<Scope> scope);
  // void leaveScope();
  // CactBasicType getFuncType(FunctionTypeCtx *ctx);
  // FuncParameters getFuncParams(FunctionParametersCtx *ctx);
  // FuncParameter getFuncParam(FunctionParameterCtx *ctx);

  // Constructor: initialize the symbol registry
  SymbolRegistrationErrorCheckVisitor() : registry(std::make_unique<SymbolRegistry>()) {
    // register built-in functions
    // void print_int(int)
    auto printIntFunc = registry->newFunction(std::string("print_int"), CactBasicType::Void);
    printIntFunc->addParameter(FuncParameter(std::string("x"), CactBasicType::Int32));

    // void print_float(float)
    auto printFloatFunc = registry->newFunction(std::string("print_float"), CactBasicType::Void);
    printFloatFunc->addParameter(FuncParameter(std::string("x"), CactBasicType::Float));

    // void print_double(double)
    auto printDoubleFunc = registry->newFunction(std::string("print_double"), CactBasicType::Void);
    printDoubleFunc->addParameter(FuncParameter(std::string("x"), CactBasicType::Double));

    // void print_bool(bool)
    auto printBoolFunc = registry->newFunction(std::string("print_bool"), CactBasicType::Void);
    printBoolFunc->addParameter(FuncParameter(std::string("x"), CactBasicType::Bool));

    // int get_int()
    registry->newFunction(std::string("get_int"), CactBasicType::Int32);

    // float get_float()
    registry->newFunction(std::string("get_float"), CactBasicType::Float);

    // double get_double()
    registry->newFunction(std::string("get_double"), CactBasicType::Double);
  }

  // print message: start semantic check
  void startSemanticCheck(const char *functionName) {
#ifdef LOG
    std::cout << "Semantic check starts: " + std::string(functionName) + "()" << std::endl;
#endif // LOG
  }

  // print message: complete semantic check
  void completeSemanticCheck(const char *functionName) {
#ifdef LOG
    std::cout << "Semantic check completed: " + std::string(functionName) + "()" << std::endl;
#endif // LOG
  }

  // visit a compilation unit
  std::any visitCompilationUnit(CompilationUnitCtx *ctx) override {
    startSemanticCheck("CompilationUnit");
    currentScope = this->registry->createGlobalScope();
    for (auto &child : ctx->children)
      visit(child);
    completeSemanticCheck("CompilationUnit");
    return {};
  }

  std::any visitConstantDeclaration(ConstantDeclarationCtx *ctx) override {
    // record the basic type
    startSemanticCheck("ConstantDeclaration");
    auto basicType = getDataType(ctx->dataType());

    // visit all constantDefinitions
    for (auto &constDef : ctx->constantDefinition()){
      constDef->needType = basicType;
      visit(constDef);
    }
    completeSemanticCheck("ConstantDeclaration");
    return {};
  }

  std::any visitDataType(DataTypeCtx *ctx) override {
    startSemanticCheck("DataType");
    if (ctx->Int32())       {std::cout << "Int32"  << std::endl; return CactBasicType::Int32; }
    else if (ctx->Bool())   {std::cout << "Bool"   << std::endl; return CactBasicType::Bool;  }
    else if (ctx->Float())  {std::cout << "Float"  << std::endl; return CactBasicType::Float; }
    else if (ctx->Double()) {std::cout << "Double" << std::endl; return CactBasicType::Double;}
    else
      throw std::runtime_error("IMPORTANT: unknown error in DataType");
    completeSemanticCheck("DataType");
    return {};
  }

  CactBasicType getDataType(DataTypeCtx *ctx) {
    return std::any_cast<CactBasicType>(visit(ctx));
  }

  std::any visitConstantDefinition(ConstantDefinitionCtx *ctx) override {
    startSemanticCheck("ConstantDefinition");
    // record name and type
    ctx->name = ctx->Identifier()->getText();
    ctx->constant.constInit(ctx->needType);

    for (auto &dimCtx : ctx->IntegerConstant()) {
      int dim = std::stoi(dimCtx->getText());
      if (dim <= 0) // dimension should be positive
        throw std::runtime_error("the size of an array must be greater than zero");
      ctx->constant.type.addDim((uint32_t)dim);
    }

    // set some attributes for constantInitialValue, visit it and get the result
    auto constInitVal = ctx->constantInitialValue();
    constInitVal->currentDim = 0;
    constInitVal->type = ctx->constant.type;
    visit(constInitVal);

    // register the constant
    currentScope->registerVariable(ctx->name, ctx->constant);

    completeSemanticCheck("ConstantDefinition");
    return {};
  }

  std::any visitConstantInitialValue(ConstantInitialValueCtx *ctx) override {
    startSemanticCheck("ConstantInitialValue");
    // if it is a constant expression, check the value's type
    const uint32_t currentDim = ctx->currentDim;
    const CactType &type = ctx->type;
    const uint32_t typeDim = type.dim();

    auto constExpr = ctx->constantExpression();
    if (constExpr) {
      if (currentDim != typeDim)
        throw std::runtime_error("invalid array initialization");
      visit(constExpr);
      if (type.basicType != constExpr->basicType)
        throw std::runtime_error("a value of type \"" +
                                 type2String(constExpr->basicType) +
                                 "\" cannot be used to initialize an entity of type \"" +
                                 type.toString() +
                                 "\"");
    }

    // if it is an array
    else {
      if (currentDim >= typeDim)
        throw std::runtime_error("too many initializer values");

      // count the number of child in constantInitialValue() array
      uint32_t count = ctx->constantInitialValue().size();

      // set default attributes of children -- constant initial values
      for (auto &child : ctx->constantInitialValue()) {
        child->currentDim = currentDim + 1;
        child->type = type;
      }

      // check if the initial value could be a flat array
      bool flatFlag = false;
      if (count == type.arrayDims[currentDim] && currentDim == 0) {
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
          child->currentDim = typeDim;
        }
      }
      // case (2): count result is exactly arrayDims[currentDim]
      else if (0 <= currentDim && currentDim < typeDim - 1) { // certain outer dimension
        if (count != type.arrayDims[currentDim])
          throw std::runtime_error("invalid array width of certain dimension");
      }
      // case (3): count result is exactly arrayDims[currentDim]
      else if (currentDim == typeDim - 1) { // the innermost dimension
        if (count > type.arrayDims[currentDim])
          throw std::runtime_error("invalid array width of certain dimension");
      }
      else {
        throw std::runtime_error("IMPORTANT: unknown error in constant initial value");
      }

      // visit all children
      for (auto &child : ctx->constantInitialValue()) {
        visit(child);
      }

    }
    completeSemanticCheck("ConstantInitialValue");
    return {};
  }

  bool hasConstExpr(ConstantInitialValueCtx *ctx) {
    return ctx->constantExpression() != nullptr;
  }

  // std::vector<ConstEvalResult> getConstIniVal(ConstantInitialValueCtx *ctx) {
  //   return std::any_cast<std::vector<ConstEvalResult>>(visit(ctx));
  // }

  std::any visitVariableDeclaration(VariableDeclarationCtx *ctx) override {
    startSemanticCheck("VariableDeclaration");
    // record the basic type
    auto basicType = getDataType(ctx->dataType());

    // visit all variableDefinitions
    for (auto &varDef : ctx->variableDefinition()){
      varDef->needType = basicType;
      visit(varDef);
    }
    completeSemanticCheck("VariableDeclaration");
    return {};
  }

  // visit a variable definition
  std::any visitVariableDefinition(VariableDefinitionCtx *ctx) override {
    startSemanticCheck("VariableDefinition");
    // record name and type
    ctx->name = ctx->Identifier()->getText();
    ctx->variable.varInit(ctx->needType);

    for (auto &dimCtx : ctx->IntegerConstant()) {
      int dim = std::stoi(dimCtx->getText());
      if (dim <= 0) // dimension should be positive
        throw std::runtime_error("the size of an array must be greater than zero");
      ctx->variable.type.addDim((uint32_t)dim);
    }

    // set some attributes for constantInitialValue, visit it and get the result
    auto constInitVal = ctx->constantInitialValue();
    if (constInitVal) {
      ctx->variable.initialized = true; // set initialized flag

      constInitVal->currentDim = 0;
      constInitVal->type = ctx->variable.type;
      // auto value = getConstIniVal(constInitVal);
      visit(constInitVal);
    }

    // register the constant
    currentScope->registerVariable(ctx->name, ctx->variable);

    completeSemanticCheck("VariableDefinition");
    return {};
  }

  // enter a new scope
  void enterScope(observer_ptr<Scope> *scope) {
    *scope = this->registry->newScope();
    scope->get()->setParent(currentScope);
    currentScope = *scope;
  }

  // leave the current scope
  void leaveScope() {
    currentScope = currentScope->getParent();
  }

  // visit a function definition
  std::any visitFunctionDefinition(FunctionDefinitionCtx *ctx) override {
    startSemanticCheck("FunctionDefinition");
    // create a new scope
    enterScope(&ctx->scope);

    // record the function's return data type and name 
    auto returnType = getFuncType(ctx->functionType());
    auto name = ctx->Identifier()->getText();
    currentFunction = ctx->function = this->registry->newFunction(name, returnType);

    // visit the function's parameters
    auto paramsCtx = ctx->functionParameters();
    if (paramsCtx) {
      paramsCtx->function = ctx->function;
      visit(paramsCtx);
    }

    // visit the block
    ctx->block()->functionBlock = true;
    visit(ctx->block());

    leaveScope();
    completeSemanticCheck("FunctionDefinition");
    return {};
  }

  // get the function type
  CactBasicType getFuncType(FunctionTypeCtx *ctx) {
    return std::any_cast<CactBasicType>(visitFunctionType(ctx));
  }

  std::any visitFunctionType(FunctionTypeCtx *ctx) override {
    startSemanticCheck("FunctionType");
    if      (ctx->Void())   return CactBasicType::Void;
    else if (ctx->Int32())  return CactBasicType::Int32;
    else if (ctx->Bool())   return CactBasicType::Bool;
    else if (ctx->Float())  return CactBasicType::Float;
    else if (ctx->Double()) return CactBasicType::Double;
    else
      throw std::runtime_error("invalid function type context");
    completeSemanticCheck("FunctionType");
    return {};
  }

  // FuncParameters getFuncParams(FunctionParametersCtx *ctx) {
  //   if (ctx == nullptr)
  //     return FuncParameters();
  //   return std::any_cast<FuncParameters>(visit(ctx));
  // }

  std::any visitFunctionParameters(FunctionParametersCtx *ctx) override {
    startSemanticCheck("FunctionParameters");
    auto func = ctx->function;
    for (auto &param : ctx->functionParameter()) {
      param->function = func;
      visit(param);
    }
    completeSemanticCheck("FunctionParameters");
    return {};
  }

  // FuncParameter getFuncParam(FunctionParameterCtx *ctx) {
  //   if (ctx == nullptr)
  //     return FuncParameter();
  //   return std::any_cast<FuncParameter>(visit(ctx));
  // }

  std::any visitFunctionParameter(FunctionParameterCtx *ctx) override {
    startSemanticCheck("FunctionParameter");
    // record basic type and name
    FuncParameter param;
    auto basicType = getDataType(ctx->dataType());
    auto name = ctx->Identifier()->getText();
    param.init(name, basicType);

    // if the first pair of brackets is empty, push 0 to the arrayDims
    if (ctx->IntegerConstant().size() < ctx->LeftBracket().size())
      param.paramVar.type.addDim(0);

    // record the array dimensions
    for (auto &dimCtx : ctx->IntegerConstant()) {
      int dim = std::stoi(dimCtx->getText());
      if (dim <= 0) // dimension should be positive
        throw std::runtime_error("the size of an array must be greater than zero");
      param.paramVar.type.addDim((uint32_t)dim);
    }

    // add the parameter to the function
    ctx->function->addParameter(param);

    // register the parameter
    currentScope->registerVariable(param.name, param.paramVar);

    completeSemanticCheck("FunctionParameter");
    return {};
  }

  // visit a block
  std::any visitBlock(BlockCtx *ctx) override {
    startSemanticCheck("Block");
    // create a new scope if it is not a function block
    if (!ctx->functionBlock)
      enterScope(&ctx->scope);

    ctx->hasReturn = false;
    // visit all block items
    for (auto &item : ctx->blockItem()) {
      visit(item);
      if (item->hasReturn)
        ctx->hasReturn = true;
    }

    if (!ctx->functionBlock)
      leaveScope();
    completeSemanticCheck("Block");
    return {};
  }

  // visit a blockItem
  std::any visitBlockItem(BlockItemCtx *ctx) override {
    startSemanticCheck("BlockItem");

    // visit the declaration
    if (ctx->declaration()) {
      visit(ctx->declaration());
      ctx->hasReturn = false;
    }
    // visit the statement
    else {
      visit(ctx->statement());
      ctx->hasReturn = ctx->statement()->hasReturn;
    }

    completeSemanticCheck("BlockItem");
    return {};
  }

  // visitting a statement
  std::any visitStatement(StatementCtx *ctx) override {
    startSemanticCheck("Statement");

    // if it has a block as a child, set its functionBlock to false
    if (ctx->block())
      ctx->block()->functionBlock = false;

    // visit children[0] since statement has only one child
    visit(ctx->children[0]);

    // check return status
    if (ctx->block())
      ctx->hasReturn = ctx->block()->hasReturn;
    else if (ctx->ifStatement())
      ctx->hasReturn = ctx->ifStatement()->hasReturn;
    else if (ctx->returnStatement())
      ctx->hasReturn = true;
    else // others
      ctx->hasReturn = false;

    completeSemanticCheck("Statement");
    return {};
  }

  // visit a assign statement
  std::any visitAssignStatement(AssignStatementCtx *ctx) override {
    startSemanticCheck("AssignStatement");
    LeftValueCtx *leftValue = ctx->leftValue();
    ExpressionCtx *expression = ctx->expression();

    // an array cannot become a valid left-hand-side value
    visit(leftValue);
    if (!leftValue->validLeftValue)
      throw std::runtime_error("expression must be a modifiable lvalue");

    // Check type compatibility
    visit(expression);
    if (leftValue->type != expression->type)
      throw std::runtime_error("a value of type \"" +
                               expression->type.toString() +
                               "cannot be assigned to an entity of type \"" +
                               leftValue->type.toString() +
                               "\"");

    completeSemanticCheck("AssignStatement");
    return {};
  }

  // visitting a expressionStatement does not need to be overrided

  // visit a return statement
  std::any visitReturnStatement(ReturnStatementCtx *ctx) override {
    startSemanticCheck("ReturnStatement");
    // visit the expression
    auto expr = ctx->expression();
    visit(expr);

    // check return type
    if (expr == nullptr) {
      if (currentFunction->returnType != CactBasicType::Void)
        throw std::runtime_error("return value type does not match the function type");
    }
    else {
      if (expr->type.isArray() || expr->type.basicType != currentFunction->returnType)
        throw std::runtime_error("return value type does not match the function type");
    }

    // record function for return statement
    ctx->retFunction = currentFunction;

    completeSemanticCheck("ReturnStatement");
    return {};
  }

  // visit a if statement
  std::any visitIfStatement(IfStatementCtx *ctx) override {
    startSemanticCheck("IfStatement");
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

    completeSemanticCheck("IfStatement");
    return {};
  }

  // visit while statement
  std::any visitWhileStatement(WhileStatementCtx *ctx) override {
    startSemanticCheck("WhileStatement");
    // visit the condition
    visit(ctx->condition());

    // visit the statement
    whileLoopStack.push(make_observer(ctx));
    visit(ctx->statement());
    whileLoopStack.pop();

    completeSemanticCheck("WhileStatement");
    return {};
  }

  // visit break statement
  std::any visitBreakStatement(BreakStatementCtx *ctx) override {
    startSemanticCheck("BreakStatement");
    // check if the break statement is in a loop
    if (whileLoopStack.empty())
      throw std::runtime_error("a break statement may only be used within a loop");

    // record the loop to break
    ctx->loopToBreak = whileLoopStack.top();

    completeSemanticCheck("BreakStatement");
    return {};
  }

  // visit continue statement
  std::any visitContinueStatement(ContinueStatementCtx *ctx) override {
    startSemanticCheck("ContinueStatement");
    // check if the continue statement is in a loop
    if (whileLoopStack.empty())
      throw std::runtime_error("a continue statement may only be used within a loop");

    // record the loop to continue
    ctx->loopToContinue = whileLoopStack.top();

    completeSemanticCheck("ContinueStatement");
    return {};
  }

  // visit an expression
  std::any visitExpression(ExpressionCtx *ctx) override {
    startSemanticCheck("Expression");
    // visit the expression
    if (ctx->addExpression()) {
      visit(ctx->addExpression());
      ctx->type = ctx->addExpression()->type;
    }
    // visit the logicalOrExpression
    else if (ctx->BooleanConstant()) {
      visit(ctx->BooleanConstant());
      ctx->type.basicType = CactBasicType::Bool;
      ctx->type.arrayDims = {};
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in expression");
    }

    completeSemanticCheck("Expression");
    return {};
  }

  // visit a constant expression
  std::any visitConstantExpression(ConstantExpressionCtx *ctx) override {
    startSemanticCheck("ConstantExpression");
    // visit the expression
    if (ctx->number()) {
      visit(ctx->number());
      ctx->basicType = ctx->number()->basicType;
    }
    // visit the logicalOrExpression
    else if (ctx->BooleanConstant()) {
      visit(ctx->BooleanConstant());
      ctx->basicType = CactBasicType::Bool;
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in expression");
    }

    completeSemanticCheck("ConstantExpression");
    return {};
  }

  // visitting a condition does not need to be overrided

  // visit a left value
  std::any visitLeftValue(LeftValueCtx *ctx) override {
    startSemanticCheck("LeftValue");
    // record the name of lvalue, and find corresponding variable
    auto name = ctx->Identifier()->getText();
    auto var = currentScope->variable(name); // if not declared, throw an error in variable()
    ctx->type = var.type;

    // visit children and check dimensions
    int count = 0;
    for (auto &expr : ctx->expression()) {
      visit(expr);
      if (!expr->type.validArrayIndex())
        throw std::runtime_error("expression must have integral type");
      count++; // count for dimensions
      if (count > var.type.dim())
        throw std::runtime_error("expression must have pointer-to-object type but it has type \"" +
                                 type2String(var.type.basicType) + "\"");
    }

    // update the type of left value by indexing times, erasing the first count dimensions
    ctx->type.arrayDims.erase(ctx->type.arrayDims.begin(), ctx->type.arrayDims.begin() + count);
    ctx->validLeftValue = var.isValidLValue();

    completeSemanticCheck("LeftValue");
    return {};
  }

  // visit primary expression
  std::any visitPrimaryExpression(PrimaryExpressionCtx *ctx) override {
    startSemanticCheck("PrimaryExpression");
    // visit the expression
    if (ctx->expression()) {
      visit(ctx->expression());
      ctx->type = ctx->expression()->type;
    }
    // visit the left value
    else if (ctx->leftValue()) {
      visit(ctx->leftValue());
      ctx->type = ctx->leftValue()->type;
    }
    // visit the number
    else if (ctx->number()) {
      visit(ctx->number());
      ctx->type.init(ctx->number()->basicType, false);
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in primary expression");
    }

    completeSemanticCheck("PrimaryExpression");
    return {};
  }

  // visit a number
  std::any visitNumber(NumberCtx *ctx) override {
    startSemanticCheck("Number");
    // record the number
    auto text = ctx->getText();
    if (ctx->IntegerConstant()) {
      ctx->basicType = CactBasicType::Int32;
    }
    else if (ctx->FloatConstant()) {
      ctx->basicType = CactBasicType::Float;
    }
    else if (ctx->DoubleConstant()) {
      ctx->basicType = CactBasicType::Double;
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in number");
    }

    completeSemanticCheck("Number");
    return {};
  }

  // visit a unary expression
  std::any visitUnaryExpression(UnaryExpressionCtx *ctx) override {
    startSemanticCheck("UnaryExpression");
    auto primary = ctx->primaryExpression();
    auto unary = ctx->unaryExpression();

    // -> primary
    if (primary) {
      visit(primary);
      ctx->type = primary->type;
      ctx->unaryOperator = make_observer<UnaryOperator>(new UnaryNopOperator);
    }
    // -> unaryOp unaryExpression
    else if (unary) {
      visit(unary);

      // check the type of unary expression
      if (!unary->type.validOperandType())
        throw std::runtime_error("expression must have arithmetic type");

      if (ctx->Plus())
        ctx->unaryOperator = make_observer<UnaryOperator>(new PlusOperator);
      else if (ctx->Minus())
        ctx->unaryOperator = make_observer<UnaryOperator>(new NegOperator);
      else if (ctx->ExclamationMark())
        ctx->unaryOperator = make_observer<UnaryOperator>(new LogicalNotOperator);
      else
        throw std::runtime_error("IMPROTANT: unknown error in unary expression");

      ctx->unaryOperator->validOperandTypeCheck(unary->type);
      ctx->type = unary->type;
    }
    // -> function call
    else if (ctx->Identifier()) {
      // find the function
      auto name = ctx->Identifier()->getText();
      auto func = this->registry->getFunction(name);
      if (!func)
        throw std::runtime_error("identifier \"" + name + "\" is undefined");

      // check parameters inside functionArguments
      if (!ctx->functionArguments()) { // no arguments
        if (func->parameters.size() != 0)
          throw std::runtime_error("too few arguments in function call");
      }
      else {
        if (func->parameters.size() != 0)
          ctx->functionArguments()->needParams = std::move(func->parameters);
        else
          ctx->functionArguments()->needParams = {};
        visit(ctx->functionArguments());
      }

      ctx->type.init(func->returnType, false);
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in unary expression");
    }

    completeSemanticCheck("UnaryExpression");
    return {};
  }

  // visit a "function arguments"
  std::any visitFunctionArguments(FunctionArgumentsCtx *ctx) override {
    startSemanticCheck("FunctionArguments");
    std::size_t numExpr = ctx->expression().size();
    std::size_t numParams = ctx->needParams.size();

    // too many arguments
    if (numExpr > numParams)
      throw std::runtime_error("too many arguments in function call");

    if (numExpr < numParams)
      throw std::runtime_error("too few arguments in function call");

    // visit all functionArguments
    for (int idx = 0; idx < numExpr; idx++) {
      visit(ctx->expression()[idx]);

      // check if the argument is compatible with parameter[count]
      if (ctx->expression()[idx]->type != ctx->needParams[idx].paramVar.type)
        throw std::runtime_error("argument of type \"" +
                                  ctx->expression()[idx]->type.toStringFull() +
                                 "\" is incompatible with parameter of type \"" +
                                  ctx->needParams[idx].paramVar.type.toStringFull() +
                                 "\"");
    }

    completeSemanticCheck("FunctionArguments");
    return {};
  }

  // visit a multiplicative expression
  std::any visitMulExpression(MulExpressionCtx *ctx) override {
    startSemanticCheck("MulExpression");
    auto unary = ctx->unaryExpression();
    auto mul = ctx->mulExpression();

    // -> unaryExpression
    if (unary && !mul) {
      visit(unary);
      ctx->binaryOperator = make_observer<BinaryOperator>(new BinaryNopOperator);
      ctx->type = unary->type;
    }
    // -> mulExpression binary-OP unaryExpression
    else if (unary && mul) {
      visit(mul);
      visit(unary);

      if (ctx->Asterisk())
        ctx->binaryOperator = make_observer<BinaryOperator>(new MulOperator);
      else if (ctx->Slash())
        ctx->binaryOperator = make_observer<BinaryOperator>(new DivOperator);
      else if (ctx->Percent())
        ctx->binaryOperator = make_observer<BinaryOperator>(new ModOperator);
      else
        throw std::runtime_error("IMPROTANT: unknown error in multiplicative expression");

      ctx->binaryOperator->binaryOperandCheck(mul->type, unary->type);
      ctx->type = mul->type;
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in multiplicative expression");
    }

    completeSemanticCheck("MulExpression");
    return {};
  }

  // visit an additive expression
  std::any visitAddExpression(AddExpressionCtx *ctx) override {
    startSemanticCheck("AddExpression");
    auto add = ctx->addExpression();
    auto mul = ctx->mulExpression();

    // -> mulExpression
    if (mul && !add) {
      visit(mul);
      ctx->binaryOperator = make_observer<BinaryOperator>(new BinaryNopOperator);
      ctx->type = mul->type;
    }
    // -> addExpression binary-OP mulExpression
    else if (mul && add) {
      visit(add);
      visit(mul);

      if (ctx->Plus())
        ctx->binaryOperator = make_observer<BinaryOperator>(new AddOperator);
      else if (ctx->Minus())
        ctx->binaryOperator = make_observer<BinaryOperator>(new SubOperator);
      else
        throw std::runtime_error("IMPROTANT: unknown error in additive expression");

      ctx->binaryOperator->binaryOperandCheck(add->type, mul->type);
      ctx->type = add->type;
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in additive expression");
    }

    completeSemanticCheck("AddExpression");
    return {};
  }

  // visit a relational expression
  std::any visitRelationalExpression(RelationalExpressionCtx *ctx) override {
    startSemanticCheck("RelationalExpression");
    auto add = ctx->addExpression();

    // -> addExpression
    if (add.size() == 1) {
      visit(add[0]);
      ctx->binaryOperator = make_observer<BinaryOperator>(new BinaryNopOperator);
      ctx->basicType = add[0]->type.basicType;
    }
    // -> addExpression binary-OP addExpression
    else if (add.size() == 2) {
      visit(add[0]);
      visit(add[1]);

      if (ctx->Less())
        ctx->binaryOperator = make_observer<BinaryOperator>(new LessOperator);
      else if (ctx->LessEqual())
        ctx->binaryOperator = make_observer<BinaryOperator>(new LessEqualOperator);
      else if (ctx->Greater())
        ctx->binaryOperator = make_observer<BinaryOperator>(new GreaterOperator);
      else if (ctx->GreaterEqual())
        ctx->binaryOperator = make_observer<BinaryOperator>(new GreaterEqualOperator);
      else
        throw std::runtime_error("IMPROTANT: unknown error in relational expression");

      ctx->binaryOperator->binaryOperandCheck(add[0]->type, add[1]->type);
      ctx->basicType = CactBasicType::Bool;
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in relational expression");
    }

    completeSemanticCheck("RelationalExpression");
    return {};
  }

  // visit a logical equal expression
  std::any visitLogicalEqualExpression(LogicalEqualExpressionCtx *ctx) override {
    startSemanticCheck("LogicalEqualExpression");
    auto relational = ctx->relationalExpression();

    // -> relationalExpression
    if (relational.size() == 1) {
      visit(relational[0]);
      ctx->binaryOperator = make_observer<BinaryOperator>(new BinaryNopOperator);
      if (relational[0]->basicType != CactBasicType::Bool)
        throw std::runtime_error("expression must have boolean type");
    }
    // -> relationalExpression binary-OP relationalExpression
    else if (relational.size() == 2) {
      visit(relational[0]);
      visit(relational[1]);

      if (ctx->LogicalEqual())
        ctx->binaryOperator = make_observer<BinaryOperator>(new EqualOperator);
      else if (ctx->NotEqual())
        ctx->binaryOperator = make_observer<BinaryOperator>(new NotEqualOperator);
      else
        throw std::runtime_error("IMPROTANT: unknown error in logical equal expression");

      ctx->binaryOperator->binaryOperandCheck(CactType(relational[0]->basicType, false),
                                                    CactType(relational[1]->basicType, false));
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in logical equal expression");
    }

    completeSemanticCheck("LogicalEqualExpression");
    return {};
  }

  // visit a logical and expression
  std::any visitLogicalAndExpression(LogicalAndExpressionCtx *ctx) override {
    startSemanticCheck("LogicalAndExpression");
    auto logicalEqual = ctx->logicalEqualExpression();
    auto logicalAnd = ctx->logicalAndExpression();

    // -> logicalEqualExpression
    if (logicalEqual && !logicalAnd) {
      visit(logicalEqual);
      ctx->binaryOperator = make_observer<BinaryOperator>(new BinaryNopOperator);
    }
    // -> logicalAndExpression && logicalEqualExpression
    else if (logicalEqual && logicalAnd) {
      visit(logicalAnd);
      visit(logicalEqual);

      ctx->binaryOperator = make_observer<BinaryOperator>(new LogicalAndOperator);
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in logical and expression");
    }

    completeSemanticCheck("LogicalAndExpression");
    return {};
  }

  // visit a logical or expression
  std::any visitLogicalOrExpression(LogicalOrExpressionCtx *ctx) override {
    startSemanticCheck("LogicalOrExpression");
    auto logicalAnd = ctx->logicalAndExpression();
    auto logicalOr = ctx->logicalOrExpression();

    // -> logicalAndExpression
    if (logicalAnd && !logicalOr) {
      visit(logicalAnd);
      ctx->binaryOperator = make_observer<BinaryOperator>(new BinaryNopOperator);
    }
    // -> logicalOrExpression || logicalAndExpression
    else if (logicalAnd && logicalOr) {
      visit(logicalOr);
      visit(logicalAnd);

      ctx->binaryOperator = make_observer<BinaryOperator>(new LogicalOrOperator);
    }
    else {
      throw std::runtime_error("IMPROTANT: unknown error in logical or expression");
    }

    completeSemanticCheck("LogicalOrExpression");
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
