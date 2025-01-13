//
// Created by creeper on 12/26/24.
//

#ifndef RISCV_BACKEND_METADATA_H
#define RISCV_BACKEND_METADATA_H
#include <cstdint>
#include <chiisai-llvm/ref.h>
namespace llvm {

constexpr uint32_t kMaximumIntegerArgumentRegisters = 8;
constexpr uint32_t kMaximumFloatArgumentRegisters = 8;

struct Type;
uint32_t sizeOfType(CRef<Type> type);

}
#endif //RISCV_BACKEND_METADATA_H
