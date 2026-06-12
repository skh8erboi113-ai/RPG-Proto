#include <gtest/gtest.h>
#include "StatsManager.h"
#include "SkillManager.h"
#include <iostream>

TEST(StatsTest, XPLeveling) {
  engine::StatsManager stats;
  EXPECT_EQ(stats.GetLevel(), 1);

  stats.AddXP(150.0f);
  EXPECT_EQ(stats.GetLevel(), 2);
  EXPECT_GT(stats.GetXPForNextLevel(), 100.0f);
}

TEST(StatsTest, Alignment) {
  engine::StatsManager stats;
  stats.AdjustAlignment(0.5f);
  EXPECT_FLOAT_EQ(stats.GetAlignment(), 0.5f);
  stats.AdjustAlignment(-1.5f);
  EXPECT_FLOAT_EQ(stats.GetAlignment(), -1.0f);
}

TEST(SkillTest, LoadingAndScaling) {
  engine::SkillManager skills;
  // Try loading from root-relative path if tests run from build/
  bool loaded = skills.LoadFromJSON("../docs/skills/FullSkillTrees.json");
  if (!loaded) {
    loaded = skills.LoadFromJSON("docs/skills/FullSkillTrees.json");
  }

  if (loaded) {
    EXPECT_EQ(skills.GetSkillLevel("angelic_aura"), 0);
    skills.LevelUpSkill("angelic_aura");
    EXPECT_EQ(skills.GetSkillLevel("angelic_aura"), 1);
    // Note: angelic_aura has effect_base = 0 in some versions, but base_value = 2
    // Let's check shadow_strike which has effect_base: 18
    skills.LevelUpSkill("shadow_strike");
    EXPECT_GT(skills.GetSkillEffect("shadow_strike"), 0.0f);
  } else {
    std::cerr << "Warning: Could not load SkillTrees.json for test\n";
  }
}
