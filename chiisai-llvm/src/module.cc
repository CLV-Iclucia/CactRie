//
// Created by creeper on 10/4/24.
//
#include <chiisai-llvm/executor.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/value.h>
namespace llvm {

Module &Module::addFunction(std::unique_ptr<Function> &&function) {
  if (m_functionMap.contains(function->name()))
    throw std::runtime_error("function already exists");
  functions.push_back(std::move(function));
  m_functionMap[functions.back()->name()] =
      mystl::make_observer(functions.back().get());
  return *this;
}
Module &Module::addGlobalVariable(std::unique_ptr<GlobalVariable> &&globalVariable) {
  if (m_globalVariableMap.contains(globalVariable->name()))
    throw std::runtime_error("global variable already exists");
  globalVariables.push_back(std::move(globalVariable));
  m_globalVariableMap[globalVariables.back()->name()] =
      mystl::make_observer(globalVariables.back().get());
  return *this;
}

void Module::accept(Executor &executor) {
  auto main = function("main");
  minilog::info("Executing main function of module {}", m_name);
  executor.pushFrame();
  executor.prvBasicBlock = {};
  executor.execute(main);
  executor.popFrame();
  minilog::info("Execution of main function of module {} finished", m_name);
}
} // namespace llvm