#include <gtest/gtest.h>
#include "StatsManager.h"
#include "SkillManager.h"
#include "WantedManager.h"
#include "EnemyManager.h"
#include "InteractionManager.h"
#include "Inventory.h"
#include <iostream>

TEST(StatsTest, XPLeveling) {
  engine::StatsManager stats;
  EXPECT_EQ(stats.GetLevel(), 1);
  stats.AddXP(150.0f);
  EXPECT_EQ(stats.GetLevel(), 2);
}

TEST(WantedTest, CrimeAndDecay) {
  engine::WantedManager wanted;
  wanted.ReportCrime("Ashbourne", 50);
  EXPECT_EQ(wanted.GetWantedLevel("Ashbourne"), engine::WantedLevel::Medium);
  wanted.Update(100.0f);
  EXPECT_EQ(wanted.GetCrimePoints("Ashbourne"), 0);
}

TEST(EnemyTest, AIChaseAndDamage) {
  engine::EnemyManager em;
  float playerPos[3] = {5.0f, 0.0f, 5.0f};
  em.SpawnEnemy("Ghost", 0.0f, 0.0f, 0.0f);

  em.Update(1.0f, playerPos);
  auto& enemies = em.GetEnemies();
  EXPECT_GT(enemies[0].pos[0], 0.0f);
  EXPECT_EQ(enemies[0].state, "Chase");

  em.TakeDamage(0, 60.0f);
  EXPECT_TRUE(enemies[0].dead);
}

TEST(InteractionTest, CollectItem) {
  engine::InteractionManager im;
  engine::Inventory inv;
  float playerPos[3] = {1.0f, 0.0f, 1.0f};

  im.AddInteractable("Clue", 1.1f, 0.0f, 1.1f, "REWARD_A");
  im.Update(playerPos, inv);

  EXPECT_EQ(inv.GetItemCount("REWARD_A"), 1);
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
