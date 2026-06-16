#include "RitualManager.h"
#include "Engine.h"
#include "StatsManager.h"
#include "Inventory.h"
#include <iostream>

namespace engine {

RitualManager::RitualManager() {}

void RitualManager::StartRitual(const std::string& type) {
  active_ = true;
  progress_ = 0.0f;
  success_ = false;
  currentType_ = type;
}

bool RitualManager::Update(float dt, int inputKey, Engine& engine) {
  if (!active_) return false;

  progress_ += dt * 0.2f; // Takes 5 seconds base

  // Simple minigame placeholder: press 'R' (82) to speed up
  if (inputKey == 82) {
    progress_ += 0.1f;
  }

  if (progress_ >= 1.0f) {
    active_ = false;
    success_ = true;

    // Reward based on alignment
    auto& stats = engine.GetStats();
    auto& inv = engine.GetInventory();
    auto alignment = stats.GetAlignmentType();

    if (alignment == AlignmentType::ANGELIC) {
      std::cout << "[Ritual] Angelic alignment detected. Rewarding HOLY_RELICT.\n";
      inv.AddItem("HOLY_RELICT", 1);
      stats.AddXP(50.0f);
    } else if (alignment == AlignmentType::DEMONIC) {
      std::cout << "[Ritual] Demonic alignment detected. Rewarding DEMON_HEART and shifting further demonic.\n";
      inv.AddItem("DEMON_HEART", 1);
      stats.AdjustAlignment(-0.1f);
    } else {
      std::cout << "[Ritual] Neutral alignment detected. Rewarding SPIRIT_ESSENCE.\n";
      inv.AddItem("SPIRIT_ESSENCE", 1);
    }

    return true;
  }
  return false;
}

} // namespace engine
