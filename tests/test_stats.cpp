#include <gtest/gtest.h>
#include "StatsManager.h"
#include "SkillManager.h"
#include "WantedManager.h"
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
  bool loaded = skills.LoadFromJSON("../docs/skills/FullSkillTrees.json");
  if (!loaded) {
    loaded = skills.LoadFromJSON("docs/skills/FullSkillTrees.json");
  }

  if (loaded) {
    EXPECT_EQ(skills.GetSkillLevel("angelic_aura"), 0);
    skills.LevelUpSkill("angelic_aura");
    EXPECT_EQ(skills.GetSkillLevel("angelic_aura"), 1);
    skills.LevelUpSkill("shadow_strike");
    EXPECT_GT(skills.GetSkillEffect("shadow_strike"), 0.0f);
  } else {
    std::cerr << "Warning: Could not load SkillTrees.json for test\n";
  }
}

TEST(WantedTest, CrimeAndDecay) {
  engine::WantedManager wanted;
  wanted.ReportCrime("Ashbourne", 50);
  EXPECT_EQ(wanted.GetWantedLevel("Ashbourne"), engine::WantedLevel::Medium);

  wanted.Update(100.0f); // Should decay 50 points
  EXPECT_EQ(wanted.GetCrimePoints("Ashbourne"), 0);
  EXPECT_EQ(wanted.GetWantedLevel("Ashbourne"), engine::WantedLevel::Clean);
}
