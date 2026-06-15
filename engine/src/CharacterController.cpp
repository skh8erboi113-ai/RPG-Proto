#include "CharacterController.h"
#include "Engine.h"
#include "StatsManager.h"
#include "EnemyManager.h"
#include <cmath>
#include <iostream>

namespace engine {

CharacterController::CharacterController() {
  pos_[0] = 0.0f;
  pos_[1] = 0.0f;
  pos_[2] = 0.0f;
}

void CharacterController::SetPosition(float x, float y, float z) {
  pos_[0] = x;
  pos_[1] = y;
  pos_[2] = z;
}

void CharacterController::Move(float dx, float dy, float dz) {
  pos_[0] += dx;
  pos_[1] += dy;
  pos_[2] += dz;
}

void CharacterController::Update(float dt) {
  (void)dt;
}

bool CharacterController::PrimaryAttack(Engine& engine) {
  auto& stats = engine.GetStats();
  if (stats.ConsumeStamina(15.0f)) {
    std::cout << "[Combat] Player attacks!\n";

    auto& enemies = engine.GetEnemies().GetEnemies();
    for (size_t i = 0; i < enemies.size(); ++i) {
      if (enemies[i].dead) continue;

      float dx = pos_[0] - enemies[i].pos[0];
      float dy = pos_[1] - enemies[i].pos[1];
      float dz = pos_[2] - enemies[i].pos[2];
      float dist = std::sqrt(dx*dx + dy*dy + dz*dz);

      if (dist < 3.0f) {
        engine.GetEnemies().TakeDamage(i, 25.0f);
      }
    }
    return true;
  }
  return false;
}

} // namespace engine
