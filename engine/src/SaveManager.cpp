#include "SaveManager.h"
#include "Engine.h"
#include "StatsManager.h"
#include "Inventory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace engine {

bool SaveManager::SaveGame(const std::string& path, Engine& engine) {
  nlohmann::json j;

  auto& stats = engine.GetStats();
  j["stats"]["level"] = stats.GetLevel();
  j["stats"]["xp"] = stats.GetXP();
  j["stats"]["alignment"] = stats.GetAlignment();
  j["stats"]["health"] = stats.GetHealth();
  j["stats"]["maxHealth"] = stats.GetMaxHealth();

  // Simple inventory serialization would go here

  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << j.dump(4);
  return true;
}

bool SaveManager::LoadGame(const std::string& path, Engine& engine) {
  std::ifstream file(path);
  if (!file.is_open()) return false;

  nlohmann::json j;
  file >> j;

  auto& stats = engine.GetStats();
  // stats would need setters, or we manually apply
  // For prototype, let's just log
  std::cout << "[SaveManager] Loaded save from " << path << "\n";
  return true;
}

} // namespace engine
