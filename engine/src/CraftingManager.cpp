#include "CraftingManager.h"
#include "Inventory.h"
#include <fstream>
#include <iostream>

namespace engine {

CraftingManager::CraftingManager() {}

bool CraftingManager::LoadFromJSON(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) return false;

  nlohmann::json j;
  file >> j;

  for (auto& recipeData : j["recipes"]) {
    Recipe r;
    r.id = recipeData["id"];
    r.name = recipeData["name"];
    r.station = recipeData["station"];
    r.craft_time_sec = recipeData["craft_time_sec"];
    for (auto& mat : recipeData["materials"]) {
      r.materials.push_back({mat["item_id"], mat["count"]});
    }
    r.output_item_id = recipeData["output"]["item_id"];
    r.output_count = recipeData["output"]["count"];
    recipes_.push_back(r);
  }
  return true;
}

bool CraftingManager::Craft(const std::string& recipeId, Inventory& inventory) {
  for (const auto& r : recipes_) {
    if (r.id == recipeId) {
      // Check materials
      for (const auto& mat : r.materials) {
        if (inventory.GetItemCount(mat.item_id) < mat.count) {
          return false;
        }
      }
      // Consume materials
      for (const auto& mat : r.materials) {
        inventory.RemoveItem(mat.item_id, mat.count);
      }
      // Add output
      inventory.AddItem(r.output_item_id, r.output_count);
      return true;
    }
  }
  return false;
}

} // namespace engine
