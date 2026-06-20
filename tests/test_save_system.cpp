#include <gtest/gtest.h>
#include "Engine.h"
#include "StatsManager.h"
#include "Inventory.h"
#include "SaveManager.h"
#include <cstdio>

TEST(SaveSystemTest, SaveLoadConsistency) {
    engine::Engine eng;

    // Set some state
    auto& stats = eng.GetStats();
    stats.SetLevel(10);
    stats.SetXP(500.5f);
    stats.SetAlignment(-0.5f);
    stats.SetHealth(80.0f);
    stats.SetStamina(40.0f);

    auto& inv = eng.GetInventory();
    inv.AddItem("POTION", 5);
    inv.AddItem("SWORD", 1);

    const std::string savePath = "test_save.json";

    // Save
    ASSERT_TRUE(engine::SaveManager::SaveGame(savePath, eng));

    // Clear state
    stats.SetLevel(1);
    stats.SetXP(0.0f);
    stats.SetAlignment(0.0f);
    stats.SetHealth(100.0f);
    stats.SetStamina(100.0f);
    inv.Clear();

    // Load
    ASSERT_TRUE(engine::SaveManager::LoadGame(savePath, eng));

    // Verify
    EXPECT_EQ(stats.GetLevel(), 10);
    EXPECT_FLOAT_EQ(stats.GetXP(), 500.5f);
    EXPECT_FLOAT_EQ(stats.GetAlignment(), -0.5f);
    EXPECT_FLOAT_EQ(stats.GetHealth(), 80.0f);
    EXPECT_FLOAT_EQ(stats.GetStamina(), 40.0f);

    EXPECT_EQ(inv.GetItemCount("POTION"), 5);
    EXPECT_EQ(inv.GetItemCount("SWORD"), 1);

    // Cleanup
    std::remove(savePath.c_str());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
