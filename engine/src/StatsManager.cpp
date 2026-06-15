#include "StatsManager.h"
#include <cmath>
#include <algorithm>

namespace engine {

StatsManager::StatsManager()
  : level_(1), xp_(0.0f), alignment_(0.0f),
    health_(100.0f), maxHealth_(100.0f),
    stamina_(50.0f), maxStamina_(50.0f) {}

void StatsManager::AddXP(f32 amount) {
  xp_ += amount;
  while (xp_ >= GetXPForNextLevel()) {
    xp_ -= GetXPForNextLevel();
    level_++;
    // Boost max health on level up
    maxHealth_ += 10.0f;
    health_ = maxHealth_;
  }
}

f32 StatsManager::GetXPForNextLevel() const {
  return CalculateXPForLevel(level_);
}

void StatsManager::AdjustAlignment(f32 delta) {
  alignment_ = std::clamp(alignment_ + delta, -1.0f, 1.0f);
}

void StatsManager::Damage(f32 amount) {
  health_ = std::max(0.0f, health_ - amount);
}

void StatsManager::Heal(f32 amount) {
  health_ = std::min(maxHealth_, health_ + amount);
}

bool StatsManager::ConsumeStamina(f32 amount) {
  if (stamina_ >= amount) {
    stamina_ -= amount;
    return true;
  }
  return false;
}

void StatsManager::Update(f32 dt) {
  // Regenerate stamina
  stamina_ = std::min(maxStamina_, stamina_ + 5.0f * dt);
}

f32 StatsManager::CalculateXPForLevel(u32 level) const {
  return 100.0f * std::pow(1.08f, static_cast<f32>(level - 1));
}

} // namespace engine
