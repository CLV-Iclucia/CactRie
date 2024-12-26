//
// Created by creeper on 12/26/24.
//

#ifndef RISCV_BACKEND_METADATA_H
#define RISCV_BACKEND_METADATA_H
#include <cstdint>
namespace llvm {

constexpr uint32_t kMaximumIntegerArgumentRegisters = 8;
constexpr uint32_t kMaximumFloatArgumentRegisters = 8;

}
#endif //RISCV_BACKEND_METADATA_H
