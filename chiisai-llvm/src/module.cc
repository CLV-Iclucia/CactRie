//
// Created by creeper on 10/4/24.
//
#include <chiisai-llvm/user.h>
#include <chiisai-llvm/value.h>
#include <chiisai-llvm/module.h>
#include <chiisai-llvm/function.h>
namespace llvm {

Module &Module::addFunction(std::unique_ptr<Function> &&function) {
  if (m_functionMap.find(function->name()) != m_functionMap.end())
    throw std::runtime_error("function already exists");
  functions.push_back(std::move(function));
  m_functionMap[functions.back()->name()] = mystl::make_observer(functions.back().get());
  return *this;
}
}