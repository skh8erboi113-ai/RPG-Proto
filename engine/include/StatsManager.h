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

private:
  u32 level_;
  f32 xp_;
  f32 alignment_;

  f32 CalculateXPForLevel(u32 level) const;
};

} // namespace engine
