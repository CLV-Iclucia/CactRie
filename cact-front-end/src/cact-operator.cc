//
// Created by creeper on 8/15/24.
//
#include <cact-front-end/CactParser.h>
#include <cact-front-end/cact-operator.h>
#include <memory>
namespace cactfrontend {

const OperandTypeChecker operand_checker_all = OperandTypeChecker(
  "expression must have integral, float-point, or boolean type",
  {CactBasicType::Int32,
   CactBasicType::Float,
   CactBasicType::Double,
   CactBasicType::Bool});

const OperandTypeChecker operand_checker_int_float = OperandTypeChecker(
  "expression must have integral or float-point type",
  {CactBasicType::Int32,
   CactBasicType::Float,
   CactBasicType::Double});

const OperandTypeChecker operand_checker_int = OperandTypeChecker(
  "expression must have integral type",
  {CactBasicType::Int32});

const OperandTypeChecker operand_checker_bool = OperandTypeChecker(
  "expression must have boolean type",
  {CactBasicType::Bool});

}