#include "InteractionManager.h"
#include "Inventory.h"
#include <cmath>
#include <iostream>

namespace engine {

InteractionManager::InteractionManager() {}

void InteractionManager::AddInteractable(const std::string& id, float x, float y, float z, const std::string& reward) {
  interactables_.push_back({id, {x, y, z}, reward, true});
}

void InteractionManager::Update(const float* playerPos, Inventory& inventory) {
  for (auto& i : interactables_) {
    if (!i.active) continue;

    float dx = playerPos[0] - i.pos[0];
    float dy = playerPos[1] - i.pos[1];
    float dz = playerPos[2] - i.pos[2];
    float dist = std::sqrt(dx*dx + dy*dy + dz*dz);

    if (dist < 2.0f) {
      std::cout << "[Interaction] Collected clue: " << i.id << "\n";
      inventory.AddItem(i.itemReward, 1);
      i.active = false;
    }
  }
}

} // namespace engine
