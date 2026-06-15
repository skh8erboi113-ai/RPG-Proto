#pragma once
#include "engine/Types.h"

namespace engine {

class StatsManager {
public:
  StatsManager();

  void AddXP(f32 amount);
  u32 GetLevel() const { return level_; }
  f32 GetXP() const { return xp_; }
  f32 GetXPForNextLevel() const;

  void AdjustAlignment(f32 delta);
  f32 GetAlignment() const { return alignment_; } // -1.0 (Demonic) to 1.0 (Angelic)

  f32 GetHealth() const { return health_; }
  f32 GetMaxHealth() const { return maxHealth_; }
  void Damage(f32 amount);
  void Heal(f32 amount);

  f32 GetStamina() const { return stamina_; }
  f32 GetMaxStamina() const { return maxStamina_; }
  bool ConsumeStamina(f32 amount);
  void Update(f32 dt);

private:
  u32 level_;
  f32 xp_;
  f32 alignment_;

  f32 health_;
  f32 maxHealth_;
  f32 stamina_;
  f32 maxStamina_;

  f32 CalculateXPForLevel(u32 level) const;
};

} // namespace engine
