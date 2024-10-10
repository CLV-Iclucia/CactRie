//
// Created by creeper on 9/23/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
#include <chiisai-llvm/value.h>
namespace llvm {

struct User : Value {
private:
  friend struct Module;
  mystl::poly_view_list<Value> m_usedValues{};
};

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_USER_H
