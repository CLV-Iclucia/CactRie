//
// Created by creeper on 8/16/24.
//

#ifndef CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
#define CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
#include <cact-front-end/mystl/observer_ptr.h>
#include <cact-front-end/cact-expr.h>
#include <string>
#include <memory>

namespace cactfrontend {

// a constant or variable in the Cact language

struct CactConstVar {
  std::string name;
  CactType type;
  std::vector<ConstEvalResult> init_values; // the initial values

  // basic constructor
  explicit CactConstVar() = default;
  explicit CactConstVar(const std::string &_name, const CactBasicType _basic_type, bool _is_param, bool _is_const) :
    name(_name), type(_basic_type, _is_param), is_const(_is_const), initialized(_is_const) {}

  // check if this type is a modifiable left value
  [[nodiscard]]
  bool isModifiableLValue() const {
    return this->type.validOperandType() && !this->is_const;
  };

  // convert the variable to a string
  [[nodiscard]]
  std::string toString() const {
    return (this->is_const ? "const " : "") + this->type.toString() + " " + this->name;
  }

  // check if the variable is initialized
  [[nodiscard]]
  bool isInitialized() const {
    return this->initialized;
  }

protected:
  bool is_const{}; // if is const type
  bool initialized{}; // initialized or not, defaultly false for variable
};

struct CactConstant : CactConstVar {
  // constructor
  explicit CactConstant() = default;
  explicit CactConstant(const std::string &const_name, const CactBasicType basic_type) :
    CactConstVar(const_name, basic_type, false, true) {}
};

struct CactVariable : CactConstVar {
  // constructor
  explicit CactVariable() = default;
  explicit CactVariable(const std::string &var_name, const CactBasicType basic_type) :
    CactConstVar(var_name, basic_type, false, false) {}

  // set the initialized flag for the variable
  void setInitialized() {
    this->initialized = true;
  }
};


struct CactConstVarArray {
  observer_ptr<CactConstVar> symbol;
  observer_ptr<CactExpr> offset;
  uint32_t indexing_times; // 0 means not indexed, 1 means indexed once, etc.

  // constructor
  explicit CactConstVarArray() = default;
  explicit CactConstVarArray(observer_ptr<CactConstVar> symbol)
    : symbol(symbol), offset(nullptr), indexing_times(0) {}

  // add an index
  void addIndex(CactExpr index) {
    this->indices.emplace_back(index);
    this->indexing_times++;
  }

  // get the index
  [[nodiscard]]
  CactExpr getIndex(uint32_t index) const {
    return this->indices[index];
  }

  // create an expression to calculate the offset
  void setOffsetByIndices() {
    assert(this->indexing_times == this->symbol->type.dim());

    // calculate constant offset
    int32_t const_offset = 0;
    for (int i = 0; i < this->indexing_times; i++) {
      // indexing times might be less than the dimension of the array
      if (this->indexing_times <= i) {
        break;
      }

      if (indices[i].isConst()) {
        const_offset += std::get<int32_t>(indices[i].getConstValue()) * this->symbol->type.size(i);
      }
    }

    offset = getObserverPtrExpr(CactExpr(const_offset));

    // calculate non-constant offset
    observer_ptr<CactExpr> expr_tmp_ptr;

    for (int i = 0; i < this->indexing_times; i++) {
      // indexing times might be less than the dimension of the array
      if (this->indexing_times <= i) {
        break;
      }

      if (!indices[i].isConst()) {
        expr_tmp_ptr = getObserverPtrExpr(CactExpr((int32_t)(this->symbol->type.size(i))));
        expr_tmp_ptr = getObserverPtrBiExpr(
          CactBinaryExpr(
            make_observer<BinaryOperator>(new MulOperator),
            make_observer<CactExpr>(&indices[i]),
            expr_tmp_ptr));
        offset = getObserverPtrBiExpr(
          CactBinaryExpr(
            make_observer<BinaryOperator>(new AddOperator),
            offset,
            expr_tmp_ptr));
      }
    }
  }

private:
  std::vector<CactExpr> indices;

  [[nodiscard]]
  static observer_ptr<CactExpr> getObserverPtrExpr(CactExpr expr) {
    return make_observer<CactExpr>(std::make_unique<CactExpr>(expr).get());
  };

  [[nodiscard]]
  static observer_ptr<CactExpr> getObserverPtrBiExpr(CactBinaryExpr expr) {
    return make_observer<CactExpr>((CactExpr *)(std::make_unique<CactBinaryExpr>(expr).get()));
  };
};


}

#endif //CACTRIE_CACT_PARSER_INCLUDE_CACT_PARSER_CACT_CONSTANT_VARIABLE_H_
