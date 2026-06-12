#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace engine {

class Inventory;

struct RecipeRequirement {
  std::string item_id;
  int count;
};

struct Recipe {
  std::string id;
  std::string name;
  std::string station;
  int craft_time_sec;
  std::vector<RecipeRequirement> materials;
  std::string output_item_id;
  int output_count;
};

class CraftingManager {
public:
  CraftingManager();
  bool LoadFromJSON(const std::string& path);

  bool Craft(const std::string& recipeId, Inventory& inventory);

private:
  std::vector<Recipe> recipes_;
};

} // namespace engine
