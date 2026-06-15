#include <gtest/gtest.h>
#include "Inventory.h"
#include "CraftingManager.h"

TEST(CraftingTest, InventoryManagement) {
  engine::Inventory inv;
  inv.AddItem("HERB_A", 5);
  EXPECT_EQ(inv.GetItemCount("HERB_A"), 5);
  EXPECT_TRUE(inv.RemoveItem("HERB_A", 2));
  EXPECT_EQ(inv.GetItemCount("HERB_A"), 3);
  EXPECT_FALSE(inv.RemoveItem("HERB_A", 10));
}

TEST(CraftingTest, BasicCrafting) {
  engine::Inventory inv;
  engine::CraftingManager cm;

  bool loaded = cm.LoadFromJSON("../docs/crafting/FullRecipes.json");
  if (!loaded) {
    loaded = cm.LoadFromJSON("docs/crafting/FullRecipes.json");
  }

  if (loaded) {
    inv.AddItem("HERB_A", 10);
    inv.AddItem("COIN_SMALL", 100);

    EXPECT_TRUE(cm.Craft("health_tonic_minor", inv));
    EXPECT_EQ(inv.GetItemCount("POTION_MINOR_HEAL"), 1);
    EXPECT_EQ(inv.GetItemCount("HERB_A"), 8);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
