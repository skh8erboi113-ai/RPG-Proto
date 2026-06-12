#include "StatsManager.h"
#include <cmath>
#include <algorithm>

namespace engine {

StatsManager::StatsManager()
  : level_(1), xp_(0.0f), alignment_(0.0f) {}

void StatsManager::AddXP(f32 amount) {
  xp_ += amount;
  while (xp_ >= GetXPForNextLevel()) {
    xp_ -= GetXPForNextLevel();
    level_++;
  }
}

f32 StatsManager::GetXPForNextLevel() const {
  return CalculateXPForLevel(level_);
}

void StatsManager::AdjustAlignment(f32 delta) {
  alignment_ = std::clamp(alignment_ + delta, -1.0f, 1.0f);
}

f32 StatsManager::CalculateXPForLevel(u32 level) const {
  // Using a standard RPG curve: 100 * 1.1^(level-1)
  return 100.0f * std::pow(1.1f, static_cast<f32>(level - 1));
}

} // namespace engine
