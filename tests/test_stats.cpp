#include <gtest/gtest.h>
#include "Engine.h"

// Minimal smoke test to verify engine link and basic lifecycle.
// Add real unit tests for Stats, Inventory, CraftingManager later.

TEST(EngineSmoke, InitializeShutdown) {
  engine::Engine eng;
  EXPECT_FALSE(eng.GetName().empty());
  EXPECT_TRUE(eng.Initialize());
  eng.Tick(1.0f / 60.0f);
  eng.Shutdown();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
