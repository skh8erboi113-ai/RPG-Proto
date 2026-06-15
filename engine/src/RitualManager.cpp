#include "RitualManager.h"

namespace engine {

RitualManager::RitualManager() {}

void RitualManager::StartRitual(const std::string& type) {
  active_ = true;
  progress_ = 0.0f;
  success_ = false;
  currentType_ = type;
}

bool RitualManager::Update(float dt, int inputKey) {
  if (!active_) return false;

  progress_ += dt * 0.2f; // Takes 5 seconds

  // Simple minigame placeholder
  if (inputKey == 82) {
    progress_ += 0.1f;
  }

  if (progress_ >= 1.0f) {
    active_ = false;
    success_ = true;
    return true;
  }
  return false;
}

} // namespace engine
