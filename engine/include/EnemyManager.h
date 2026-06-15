#pragma once
#include <vector>
#include <string>

namespace engine {

struct Enemy {
  std::string id;
  float pos[3];
  float health;
  std::string state; // Idle, Chase, Attack
  bool dead = false;
};

class EnemyManager {
public:
  EnemyManager();
  void SpawnEnemy(const std::string& type, float x, float y, float z);
  void Update(float dt, const float* playerPos);

  void TakeDamage(size_t index, float amount);
  std::vector<Enemy>& GetEnemies() { return enemies_; }

private:
  std::vector<Enemy> enemies_;
};

} // namespace engine
