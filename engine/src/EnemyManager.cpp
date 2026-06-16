#include "EnemyManager.h"
#include "Inventory.h"
#include <cmath>
#include <iostream>

namespace engine {

EnemyManager::EnemyManager() {}

void EnemyManager::SpawnEnemy(const std::string& type, float x, float y, float z, const std::string& loot) {
  enemies_.push_back({type, {x, y, z}, 50.0f, "Idle", false, loot});
  std::cout << "[EnemyManager] Spawned " << type << " at (" << x << "," << y << "," << z << ") with loot: " << loot << "\n";
}

void EnemyManager::Update(float dt, const float* playerPos) {
  for (auto& e : enemies_) {
    if (e.dead) continue;

    float dx = playerPos[0] - e.pos[0];
    float dy = playerPos[1] - e.pos[1];
    float dz = playerPos[2] - e.pos[2];
    float dist = std::sqrt(dx*dx + dy*dy + dz*dz);

    if (dist < 10.0f) {
      e.state = "Chase";
      float speed = 2.0f;
      e.pos[0] += (dx / dist) * speed * dt;
      e.pos[1] += (dy / dist) * speed * dt;
      e.pos[2] += (dz / dist) * speed * dt;
    } else {
      e.state = "Idle";
    }
  }
}

void EnemyManager::TakeDamage(size_t index, float amount, Inventory* inventory) {
  if (index < enemies_.size()) {
    enemies_[index].health -= amount;
    if (enemies_[index].health <= 0 && !enemies_[index].dead) {
      enemies_[index].dead = true;
      std::cout << "[EnemyManager] " << enemies_[index].id << " defeated!\n";
      if (!enemies_[index].lootItemId.empty() && inventory) {
        inventory->AddItem(enemies_[index].lootItemId, 1);
        std::cout << "[Loot] Dropped " << enemies_[index].lootItemId << "\n";
      }
    }
  }
}

} // namespace engine
