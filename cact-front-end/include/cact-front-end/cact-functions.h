//
// Created by creeper on 8/15/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
#include <cact-front-end/cact-type.h>
// #include <functional>
#include <string>

namespace cactfrontend {

// a parameter in the function definition
struct FuncParameter {
  CactConstVar paramVar; // parameter variable
  std::string name; // parameter name

  // constructor
  explicit FuncParameter() = default;
  explicit FuncParameter(std::string name, CactBasicType basicType) {
    this->init(std::move(name), basicType);
  }

  // set up the parameter
  void init(const std::string name, CactBasicType basicType) {
    this->paramVar.paramInit(basicType);
    this->name = std::move(name);
  }

  // // check if the parameter type is valid
  // [[nodiscard]] bool valid() const {
  //   // dummy, need to be implemented
  //   return basicType != CactBasicType::Unknown && basicType != CactBasicType::Void;
  // }
};

// a list of function parameters
typedef std::vector<FuncParameter> FuncParameters;

// a function in the Cact language
struct CactFunction {
  CactBasicType returnType; // return type
  std::string name; // function name
  FuncParameters parameters; // parameters

  // set up name and return type
  void init(const std::string &name, CactBasicType retType) {
    this->name = std::move(name);
    this->returnType = retType;
  }

  // add a new parameter
  void addParameter(FuncParameter param) {
    // check if parameter name is used
    for (auto &p : this->parameters)
      if (p.name == param.name)
        throw std::runtime_error("Duplicate parameter name: " + param.name);

    this->parameters.push_back(param);
  }
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_FUNCTIONS_H_
