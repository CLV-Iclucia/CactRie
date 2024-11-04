//
// Created by creeper on 11/3/24.
//

#ifndef CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_LAMBDA_H
#define CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_LAMBDA_H
namespace llvm::mystl {
namespace details {
template <int I>
struct lambda_arg {

};
}
template <int I>
details::lambda_arg<I> arg() {return {};}

}
#endif //CACTRIE_CHIISAI_LLVM_INCLUDE_CHIISAI_LLVM_MYSTL_LAMBDA_H
