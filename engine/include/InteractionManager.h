#pragma once
#include <vector>
#include <string>

namespace engine {

class Inventory;

struct Interactable {
  std::string id;
  float pos[3];
  std::string itemReward;
  bool active = true;
};

class InteractionManager {
public:
  InteractionManager();
  void AddInteractable(const std::string& id, float x, float y, float z, const std::string& reward);
  void Update(const float* playerPos, Inventory& inventory);

private:
  std::vector<Interactable> interactables_;
};

} // namespace engine
