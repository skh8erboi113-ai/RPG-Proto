#include "HUD.h"
#include "Engine.h"
#include "StatsManager.h"
#include "WantedManager.h"
#include <iostream>

namespace engine {

void HUD::Draw(Engine& engine) {
  auto& stats = engine.GetStats();

  // For prototype, we'll log to console until ImGui is fully ready
  // (In a real build, we'd use ImGui::Begin/End here)
  // TODO: surface wanted-level info here once HUD has a notion of the
  // player's current city (see WantedManager::GetWantedLevel).
  static float timer = 0;
  timer += 0.016f;
  if (timer > 1.0f) {
    std::cout << "[HUD] HP: " << stats.GetHealth() << "/" << stats.GetMaxHealth()
              << " | Stamina: " << (int)stats.GetStamina()
              << " | Level: " << stats.GetLevel()
              << " | Alignment: " << stats.GetAlignment() << "\n";
    timer = 0;
  }
}

} // namespace engine
