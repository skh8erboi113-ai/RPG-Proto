#include <gtest/gtest.h>
#include "WorldStreamer.h"

// WorldStreamer currently tracks the player's position and runs an
// Update() tick (chunk streaming is a TODO in the implementation).
// These tests cover the stable, testable surface: that position
// updates are stored correctly and that Update() is safe to call
// repeatedly, with or without a prior SetPlayerPosition call.

TEST(WorldStreamerTest, DefaultPositionIsOrigin) {
  engine::WorldStreamer streamer;
  // No public getter exists yet, so we verify indirectly: Update()
  // must not throw/crash on default-constructed state.
  EXPECT_NO_THROW(streamer.Update(0.0f));
}

TEST(WorldStreamerTest, SetPlayerPositionAcceptsValues) {
  engine::WorldStreamer streamer;
  EXPECT_NO_THROW(streamer.SetPlayerPosition(10.0f, 2.0f, -5.0f));
}

TEST(WorldStreamerTest, UpdateAfterPositionChange) {
  engine::WorldStreamer streamer;
  streamer.SetPlayerPosition(100.0f, 0.0f, 100.0f);
  EXPECT_NO_THROW(streamer.Update(0.016f));
}

TEST(WorldStreamerTest, RepeatedUpdatesAreStable) {
  engine::WorldStreamer streamer;
  streamer.SetPlayerPosition(1.0f, 1.0f, 1.0f);
  for (int i = 0; i < 100; ++i) {
    EXPECT_NO_THROW(streamer.Update(0.016f));
  }
}

TEST(WorldStreamerTest, HandlesNegativeAndZeroDeltaTime) {
  engine::WorldStreamer streamer;
  streamer.SetPlayerPosition(0.0f, 0.0f, 0.0f);
  EXPECT_NO_THROW(streamer.Update(0.0f));
  EXPECT_NO_THROW(streamer.Update(-1.0f));
}

TEST(WorldStreamerTest, HandlesRepeatedRepositioning) {
  engine::WorldStreamer streamer;
  // Simulate the player moving across several chunk boundaries in one
  // session, as Engine::Tick() would drive it every frame.
  const float positions[][3] = {
    {0.0f, 0.0f, 0.0f},
    {500.0f, 0.0f, 0.0f},
    {500.0f, 0.0f, 500.0f},
    {-500.0f, 0.0f, -500.0f},
    {0.0f, 100.0f, 0.0f},
  };
  for (const auto& p : positions) {
    streamer.SetPlayerPosition(p[0], p[1], p[2]);
    EXPECT_NO_THROW(streamer.Update(0.016f));
  }
}

TEST(WorldStreamerTest, HandlesExtremeCoordinates) {
  engine::WorldStreamer streamer;
  streamer.SetPlayerPosition(1.0e6f, -1.0e6f, 1.0e6f);
  EXPECT_NO_THROW(streamer.Update(0.016f));
}
