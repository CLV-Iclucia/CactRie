//
// Created by creeper on 1/11/25.
//
#include "chiisai-llvm/backend/riscv/riscv-backend-metadata.h"

#include <chiisai-llvm/backend/riscv/riscv-reg-alloc.h>
#include <queue>
#include <string_view>
namespace llvm {

struct PhysRegUseInfo {
  std::pair<uint32_t, uint32_t> range{};
  std::string vReg{};
  auto operator<=>(const PhysRegUseInfo &) const = default;
};

static bool tryInsert(std::set<PhysRegUseInfo> &regSet,
                      const PhysRegUseInfo &info) {
  auto [start, end] = info.range;
  auto it = regSet.lower_bound(info);
  if (it != regSet.end() && it->range.first < end)
    return false;
  if (it != regSet.begin() && (--it)->range.second > start)
    return false;
  regSet.insert(info);
  return true;
}

struct SubAllocator {
  explicit SubAllocator(RiscvRegAllocator &allocator,
                        const RegisterConfig &config)
      : config(config), allocator(allocator) {
    for (uint32_t i = 0; i < 32; i++)
      idleRegs.insert(i);
  }

  void spill(const std::string &vReg) {
    // if we come here, no physical register is available
    // we search in the available spill slots
    assert(!regMap.contains(vReg));
    auto liveRange =
        allocator.regWeightInfo.livenessAnalysisPass.livenessInfo.at(vReg);
    auto info = PhysRegUseInfo{liveRange, vReg};
    for (uint32_t i = 0; i < spillSlots; i++) {
      if (!tryInsert(spillSlotUseInfo[i], info))
        continue;
      // we successfully insert the new vReg into a spill slot
      spillSlotMap[vReg] = i;
      return;
    }
    // if we reach here, we need to allocate a new spill slot
    spillSlots++;
    spillSlotUseInfo[spillSlots].insert(info);
    spillSlotMap[vReg] = spillSlots;
  }

  void allocate(const std::string &vReg) {
    if (!idleRegs.empty()) {
      // this happens at the beginning, when only a few vRegs are considered
      auto regIdx = *idleRegs.begin();
      idleRegs.erase(regIdx);
      regMap[vReg] = config.regNames[regIdx];
      regUseInfo[config.regNames[regIdx]].insert(PhysRegUseInfo{
          allocator.regWeightInfo.livenessAnalysisPass.livenessInfo.at(vReg),
          vReg});
      return;
    }
    // try insert into a suitable place
    auto liveRange =
        allocator.regWeightInfo.livenessAnalysisPass.livenessInfo.at(vReg);
    PhysRegUseInfo info{liveRange, vReg};
    for (auto &[physReg, useInfo] : regUseInfo) {
      if (!tryInsert(useInfo, info))
        continue;
      regMap[vReg] = physReg;
      spill(vReg);
      return;
    }
    // if reach here, we either spill, or we choose an argument to spill
    if (argsInRegs.empty()) {
      // sadly, no argument is in the registers
      spill(vReg);
      return;
    }
    auto [weight, arg] = argsInRegs.top();
    // if even the lightest arg is heavier than the new vReg, we can't spill it
    if (weight < allocator.regWeightInfo.regWeight.at(vReg)) {
      spill(vReg);
      return;
    }

    argsInRegs.pop();
    auto physReg = regMap.at(arg);
    const auto &argInfo = *regUseInfo.at(regMap.at(arg)).begin();
    assert(argInfo.range.first == 0 && argInfo.vReg == arg);
    // we try to remove the arg from current register and see if we can insert
    // the new vReg
    std::erase_if(regUseInfo.at(physReg),
                  [&](const auto &pair) { return pair.vReg == arg; });
    if (!tryInsert(regUseInfo[physReg], info)) {
      // even if we spill the arg, we can't insert the new vReg
      // in that case let's just spill the new vReg
      regUseInfo[physReg].insert(argInfo);
      argsInRegs.emplace(allocator.regWeightInfo.regWeight.at(arg), arg);
      spill(vReg);
      return;
    }
    // we successfully insert the new vReg, and in return, we spill the arg
    regMap.erase(arg);
    regMap[vReg] = physReg;
    spill(arg);
  }

  std::priority_queue<std::pair<double, std::string>,
                      std::vector<std::pair<double, std::string>>, std::less<>>
      argsInRegs{};
  // when needed, we can spill the args
  const RegisterConfig &config;
  RiscvRegAllocator &allocator;
  uint32_t spillSlots{};
  std::unordered_map<std::string, std::set<PhysRegUseInfo>> regUseInfo{};
  std::unordered_map<uint32_t, std::set<PhysRegUseInfo>> spillSlotUseInfo{};
  std::unordered_map<std::string, std::string> regMap{};
  std::unordered_map<std::string, uint32_t> spillSlotMap{};
  std::set<uint32_t> idleRegs{};
};

RegisterConfig RegisterConfig::standardConfig() {
  // some registers are reserved for specific purposes
  RegisterConfig config{};
  // these registers are reserved for instant load of spilled values
  // config.regNames.emplace_back("t0");
  // config.regNames.emplace_back("t1");
  // config.regNames.emplace_back("t2");
  config.regNames.emplace_back("t3");
  config.regNames.emplace_back("t4");
  config.regNames.emplace_back("t5");
  config.regNames.emplace_back("t6");
  config.regNames.emplace_back("a0");
  config.regNames.emplace_back("a1");
  config.regNames.emplace_back("a2");
  config.regNames.emplace_back("a3");
  config.regNames.emplace_back("a4");
  config.regNames.emplace_back("a5");
  config.regNames.emplace_back("a6");
  config.regNames.emplace_back("a7");
  config.regNames.emplace_back("s0");
  config.regNames.emplace_back("s1");
  config.regNames.emplace_back("s2");
  config.regNames.emplace_back("s3");
  config.regNames.emplace_back("s4");
  config.regNames.emplace_back("s5");
  config.regNames.emplace_back("s6");
  config.regNames.emplace_back("s7");
  config.regNames.emplace_back("s8");
  config.regNames.emplace_back("s9");
  config.regNames.emplace_back("s10");
  config.regNames.emplace_back("s11");
  config.maxRegsForArgs = kMaximumIntegerArgumentRegisters;
  config.numCalleeSavedRegs = 12;
  config.calleeSavedRegs = {"s0", "s1", "s2", "s3", "s4",  "s5",
                            "s6", "s7", "s8", "s9", "s10", "s11"};
  config.numCallerSavedRegs = 8;
  config.callerSavedRegs = {"t3", "t4", "t5", "t6", "a0", "a1", "a2", "a3"};
  config.isCalleeSaved = [&](std::string_view pReg) {
    return pReg == "s0" || pReg == "s1" || pReg == "s2" || pReg == "s3" ||
           pReg == "s4" || pReg == "s5" || pReg == "s6" || pReg == "s7" ||
           pReg == "s8" || pReg == "s9" || pReg == "s10" || pReg == "s11";
  };
  config.tmpReg = [&](uint32_t i) { return "t" + std::to_string(i); };
  return config;
}

RegisterConfig RegisterConfig::floatingPointConfig() {
  RegisterConfig config{};
  for (uint32_t i = 0; i < 29; i++)
    config.regNames.emplace_back("f" + std::to_string(i));
  // the last 3 registers are reserved for instant load of spilled values
  config.tmpReg = [&](uint32_t i) { return "f" + std::to_string(i + 29); };
  config.maxRegsForArgs = kMaximumFloatArgumentRegisters;
  return config;
}

RegAllocResult RiscvRegAllocator::allocate() {
  std::vector<SubAllocator> subAllocators{};
  for (const auto &config : regConfigs)
    subAllocators.emplace_back(*this, config);

  const auto &regWeight = regWeightInfo.regWeight;
  std::priority_queue<std::pair<double, std::string>,
                      std::vector<std::pair<double, std::string>>,
                      std::greater<>>
      heap{};

  // preallocate the arguments, but we might choose to spill them later
  std::vector<int> argRegCount{};
  argRegCount.resize(regConfigs.size(), 0);
  for (const auto &[reg, weight] : regWeight) {
    if (!func.hasArg(reg)) {
      heap.emplace(weight, reg);
      continue;
    }
    if (auto idx = dispatcher(reg);
        ++argRegCount[idx] < subAllocators[idx].config.maxRegsForArgs)
      subAllocators[idx].allocate(reg);
    else
      heap.emplace(weight, reg);
    // if we have used up all the argument registers, we
    // just allocate these arguments like normal registers
  }

  while (!heap.empty()) {
    auto [weight, reg] = heap.top();
    heap.pop();
    subAllocators[dispatcher(reg)].allocate(reg);
  }

  std::unordered_map<std::string, std::string> regMap{};
  std::unordered_map<std::string, uint32_t> spillSlotMap{};
  uint32_t totalSpillSlots{};
  for (const auto &sub : subAllocators) {
    for (const auto &[vReg, pReg] : sub.regMap)
      regMap[vReg] = pReg;
    totalSpillSlots += sub.spillSlots;
  }
  uint32_t prefixSum{};
  for (const auto &sub : subAllocators) {
    for (const auto &[vReg, slot] : sub.spillSlotMap)
      spillSlotMap[vReg] = prefixSum + slot;
    prefixSum += sub.spillSlots;
  }
  assert(totalSpillSlots == prefixSum);
  return RegAllocResult{regMap, spillSlotMap, totalSpillSlots};
}

} // namespace llvm