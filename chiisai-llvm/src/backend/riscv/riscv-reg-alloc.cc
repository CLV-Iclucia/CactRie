//
// Created by creeper on 1/11/25.
//
#include <chiisai-llvm/backend/riscv/riscv-backend-metadata.h>
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
  if (regSet.empty()) {
    regSet.insert(info);
    return true;
  }
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
    for (uint32_t i = 0; i < config.regNames.size(); i++)
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
    spillSlotUseInfo[spillSlots].insert(info);
    spillSlotMap[vReg] = spillSlots++;
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
      return;
    }
    // if reach here, we either spill, or we choose an argument to spill
    if (argsInRegs.empty()) {
      // sadly, no argument is in the registers
      spill(vReg);
      return;
    }
    for (const auto &[weight, arg] : argsInRegs) {
      if (weight >= allocator.regWeightInfo.regWeight.at(vReg))
        break;

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
        continue;
      }
      // we successfully insert the new vReg, and in return, we spill the arg
      regMap.erase(arg);
      regMap[vReg] = physReg;
      spill(arg);
      argsInRegs.erase({weight, arg});
      return;
    }
    spill(vReg);
  }

  std::set<std::pair<double, std::string>> argsInRegs{};
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
  // config.regNames.emplace_back("s0");
  // config.regNames.emplace_back("s1");
  // config.regNames.emplace_back("s2");
  config.regNames.emplace_back("a0");
  config.regNames.emplace_back("a1");
  config.regNames.emplace_back("a2");
  config.regNames.emplace_back("a3");
  config.regNames.emplace_back("a4");
  config.regNames.emplace_back("a5");
  config.regNames.emplace_back("a6");
  config.regNames.emplace_back("a7");
  config.regNames.emplace_back("t0");
  config.regNames.emplace_back("t1");
  config.regNames.emplace_back("t2");
  config.regNames.emplace_back("t3");
  config.regNames.emplace_back("t4");
  config.regNames.emplace_back("t5");
  config.regNames.emplace_back("t6");
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
  config.numCallerSavedRegs = 15;
  config.callerSavedRegs = {"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
                            "t0", "t1", "t2", "t3", "t4", "t5", "t6"};
  config.isCalleeSaved = [&](std::string_view pReg) {
    return pReg.starts_with("s");
  };
  config.argRegs = {"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"};
  config.tmpReg = [&](uint32_t i) { return "s" + std::to_string(i); };
  return config;
}

RegisterConfig RegisterConfig::floatingPointConfig() {
  RegisterConfig config{};
  // these registers are reserved for instant load of spilled values
  // config.regNames.emplace_back("fs0");
  // config.regNames.emplace_back("fs1");
  // config.regNames.emplace_back("fs2");
  config.regNames.emplace_back("fa0");
  config.regNames.emplace_back("fa1");
  config.regNames.emplace_back("fa2");
  config.regNames.emplace_back("fa3");
  config.regNames.emplace_back("fa4");
  config.regNames.emplace_back("fa5");
  config.regNames.emplace_back("fa6");
  config.regNames.emplace_back("fa7");
  config.regNames.emplace_back("ft0");
  config.regNames.emplace_back("ft1");
  config.regNames.emplace_back("ft2");
  config.regNames.emplace_back("ft3");
  config.regNames.emplace_back("ft4");
  config.regNames.emplace_back("ft5");
  config.regNames.emplace_back("ft6");
  config.regNames.emplace_back("ft7");
  config.regNames.emplace_back("ft8");
  config.regNames.emplace_back("ft9");
  config.regNames.emplace_back("ft10");
  config.regNames.emplace_back("ft11");
  config.regNames.emplace_back("fs3");
  config.regNames.emplace_back("fs4");
  config.regNames.emplace_back("fs5");
  config.regNames.emplace_back("fs6");
  config.regNames.emplace_back("fs7");
  config.regNames.emplace_back("fs8");
  config.regNames.emplace_back("fs9");
  config.regNames.emplace_back("fs10");
  config.regNames.emplace_back("fs11");
  config.maxRegsForArgs = kMaximumIntegerArgumentRegisters;
  config.numCalleeSavedRegs = 12;
  config.calleeSavedRegs = {"fs0", "fs1", "fs2", "fs3", "fs4",  "fs5",
                            "fs6", "fs7", "fs8", "fs9", "fs10", "fs11"};
  config.numCallerSavedRegs = 20;
  config.callerSavedRegs = {"fa0", "fa1", "fa2", "fa3", "fa4",  "fa5", "fa6",
                            "fa7", "ft0", "ft1", "ft2", "ft3",  "ft4", "ft5",
                            "ft6", "ft7", "ft8", "ft9", "ft10", "ft11"};
  config.isCalleeSaved = [&](std::string_view pReg) {
    return pReg.starts_with("fs");
  };
  config.argRegs = {"fa0", "fa1", "fa2", "fa3", "fa4", "fa5", "fa6", "fa7"};
  config.tmpReg = [&](uint32_t i) { return "fs" + std::to_string(i); };
  return config;
}

RegAllocResult RiscvRegAllocator::allocate() {
  std::vector<SubAllocator> subAllocators{};
  for (const auto &config : regConfigs)
    subAllocators.emplace_back(*this, config);

  const auto &regWeight = regWeightInfo.regWeight;
  std::priority_queue<std::pair<double, std::string>> heap{};

  // preallocate the arguments, but we might choose to spill them later
  std::vector<int> argRegCount{};
  argRegCount.resize(regConfigs.size(), 0);
  for (const auto &[reg, weight] : regWeight)
    if (!func.hasArg(reg))
      heap.emplace(weight, reg);

  for (auto regVal : func.args()) {
    const auto &reg = regVal->name();
    if (auto idx = dispatcher(reg);
        argRegCount[idx] < subAllocators[idx].config.maxRegsForArgs) {
      const auto &argReg = subAllocators[idx].config.argRegs[argRegCount[idx]];
      assert(tryInsert(
          subAllocators[idx].regUseInfo[argReg],
          PhysRegUseInfo{
              regWeightInfo.livenessAnalysisPass.livenessInfo.at(reg), reg}));
      subAllocators[idx].regMap[reg] = argReg;
      subAllocators[idx].idleRegs.erase(argRegCount[idx]);
      argRegCount[idx]++;
      subAllocators[idx].argsInRegs.insert({regWeight.at(reg), reg});
    } else
      heap.emplace(regWeight.at(reg), reg);
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