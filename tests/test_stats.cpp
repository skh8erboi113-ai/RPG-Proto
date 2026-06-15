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

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
