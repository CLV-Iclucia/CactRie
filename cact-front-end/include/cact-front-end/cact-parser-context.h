//
// Created by creeper on 7/29/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_PARSER_CONTEXT_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_PARSER_CONTEXT_H_
#include <cact-front-end/CactParser.h>

namespace cactfrontend {

using CompilationUnitCtx        = CactParser::CompilationUnitContext;
using DeclarationCtx            = CactParser::DeclarationContext;
using ConstantDeclarationCtx    = CactParser::ConstantDeclarationContext;
using DataTypeCtx               = CactParser::DataTypeContext;
using ConstantDefinitionCtx     = CactParser::ConstantDefinitionContext;
using ConstantInitialValueCtx   = CactParser::ConstantInitialValueContext;
using VariableDeclarationCtx    = CactParser::VariableDeclarationContext;
using VariableDefinitionCtx     = CactParser::VariableDefinitionContext;
using FunctionDefinitionCtx     = CactParser::FunctionDefinitionContext;
using FunctionTypeCtx           = CactParser::FunctionTypeContext;
using FunctionFormalParamsCtx   = CactParser::FunctionFormalParamsContext;
using FunctionFormalParamCtx    = CactParser::FunctionFormalParamContext;
using BlockCtx                  = CactParser::BlockContext;
using BlockItemCtx              = CactParser::BlockItemContext;
using StatementCtx              = CactParser::StatementContext;
using AssignStatementCtx        = CactParser::AssignStatementContext;
using ExpressionStatementCtx    = CactParser::ExpressionStatementContext;
using ReturnStatementCtx        = CactParser::ReturnStatementContext;
using IfStatementCtx            = CactParser::IfStatementContext;
using WhileStatementCtx         = CactParser::WhileStatementContext;
using BreakStatementCtx         = CactParser::BreakStatementContext;
using ContinueStatementCtx      = CactParser::ContinueStatementContext;
using ExpressionCtx             = CactParser::ExpressionContext;
using ConstantExpressionCtx     = CactParser::ConstantExpressionContext;
using ConditionCtx              = CactParser::ConditionContext;
using LeftValueCtx              = CactParser::LeftValueContext;
using PrimaryExpressionCtx      = CactParser::PrimaryExpressionContext;
using NumberCtx                 = CactParser::NumberContext;
using UnaryExpressionCtx        = CactParser::UnaryExpressionContext;
using FunctionRealParamsCtx     = CactParser::FunctionRealParamsContext;
using MulExpressionCtx          = CactParser::MulExpressionContext;
using AddExpressionCtx          = CactParser::AddExpressionContext;
using RelationalExpressionCtx   = CactParser::RelationalExpressionContext;
using LogicalEqualExpressionCtx = CactParser::LogicalEqualExpressionContext;
using LogicalAndExpressionCtx   = CactParser::LogicalAndExpressionContext;
using LogicalOrExpressionCtx    = CactParser::LogicalOrExpressionContext; 

}

#endif // CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_PARSER_CONTEXT_H_