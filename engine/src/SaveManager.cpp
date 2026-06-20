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
  j["stats"]["stamina"] = stats.GetStamina();
  j["stats"]["maxStamina"] = stats.GetMaxStamina();

  auto& inv = engine.GetInventory();
  for (const auto& [id, count] : inv.GetItems()) {
    j["inventory"][id] = count;
  }

  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << j.dump(4);
  return true;
}

bool SaveManager::LoadGame(const std::string& path, Engine& engine) {
  std::ifstream file(path);
  if (!file.is_open()) return false;

  nlohmann::json j;
  try {
    file >> j;
  } catch (const std::exception& e) {
    std::cerr << "[SaveManager] Parse error: " << e.what() << "\n";
    return false;
  }

  auto& stats = engine.GetStats();
  if (j.contains("stats")) {
    const auto& s = j["stats"];
    if (s.contains("level")) stats.SetLevel(s["level"]);
    if (s.contains("xp")) stats.SetXP(s["xp"]);
    if (s.contains("alignment")) stats.SetAlignment(s["alignment"]);
    if (s.contains("health")) stats.SetHealth(s["health"]);
    if (s.contains("maxHealth")) stats.SetMaxHealth(s["maxHealth"]);
    if (s.contains("stamina")) stats.SetStamina(s["stamina"]);
    if (s.contains("maxStamina")) stats.SetMaxStamina(s["maxStamina"]);
  }

  auto& inv = engine.GetInventory();
  inv.Clear();
  if (j.contains("inventory")) {
    for (auto it = j["inventory"].begin(); it != j["inventory"].end(); ++it) {
      inv.AddItem(it.key(), it.value());
    }
  }

  std::cout << "[SaveManager] Loaded save from " << path << "\n";
  return true;
}

} // namespace engine
