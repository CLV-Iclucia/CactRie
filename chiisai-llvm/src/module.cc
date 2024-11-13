//
// Created by creeper on 10/4/24.
//
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/function.h>
#include <chiisai-llvm/executor.h>
namespace llvm {

Module &Module::addFunction(std::unique_ptr<Function> &&function) {
  if (m_functionMap.find(function->name()) != m_functionMap.end())
    throw std::runtime_error("function already exists");
  functions.push_back(std::move(function));
  m_functionMap[functions.back()->name()] = mystl::make_observer(functions.back().get());
  return *this;
}
void Module::accept(Executor &executor) {
  auto main = function("main");
  minilog::info("Executing main function of module {}", m_name);
  executor.pushFrame();
  executor.execute(main);
  executor.popFrame();
  minilog::info("Execution of main function of module {} finished", m_name);
}
}