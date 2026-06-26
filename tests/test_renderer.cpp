#include <gtest/gtest.h>
#include "Renderer.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Renderer wraps bgfx + GLFW lifecycle calls (bgfx::init, buffer
// creation, frame submission) that require a real graphics context.
// There is no abstraction seam to mock the GPU out, so these are
// integration-style smoke tests rather than pure unit tests: they spin
// up a real (offscreen/Xvfb-backed) window, exactly as Engine::Initialize()
// does, and verify the Renderer lifecycle doesn't crash and behaves
// sanely. Per the project README, these are intended to run under
// `xvfb-run` in headless environments.
//
// If no display/GL context can be created at all (e.g. GLFW itself
// fails to init), the fixture skips rather than failing the whole
// suite, so this file is still safe to run on a machine with no X
// server and no Xvfb configured.

class RendererTest : public ::testing::Test {
 protected:
  void SetUp() override {
    if (!glfwInit()) {
      GTEST_SKIP() << "GLFW could not initialize (no display available); "
                       "run under xvfb-run for full Renderer coverage.";
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    window_ = glfwCreateWindow(64, 64, "RendererTest", nullptr, nullptr);
    if (!window_) {
      GTEST_SKIP() << "Could not create a GLFW window (no usable display).";
    }
  }

  void TearDown() override {
    if (window_) {
      glfwDestroyWindow(window_);
      window_ = nullptr;
    }
    glfwTerminate();
  }

  GLFWwindow* window_ = nullptr;
};

TEST_F(RendererTest, InitializeSucceedsWithValidWindow) {
  engine::Renderer renderer;
  bool ok = renderer.Initialize(window_, 64, 64);
  EXPECT_TRUE(ok);
  renderer.Shutdown();
}

TEST_F(RendererTest, RenderFrameAfterInitializeDoesNotCrash) {
  engine::Renderer renderer;
  ASSERT_TRUE(renderer.Initialize(window_, 64, 64));

  engine::Camera camera;
  renderer.SetCamera(&camera);

  EXPECT_NO_THROW(renderer.RenderFrame(0.0f));
  EXPECT_NO_THROW(renderer.RenderFrame(0.5f));

  renderer.Shutdown();
}

TEST_F(RendererTest, ResizeAfterInitializeDoesNotCrash) {
  engine::Renderer renderer;
  ASSERT_TRUE(renderer.Initialize(window_, 64, 64));

  EXPECT_NO_THROW(renderer.Resize(128, 128));
  EXPECT_NO_THROW(renderer.RenderFrame(0.0f));

  renderer.Shutdown();
}

TEST_F(RendererTest, ShutdownIsSafeWithoutInitialize) {
  engine::Renderer renderer;
  // Destructor / Shutdown should be a no-op when Initialize was never
  // called successfully.
  EXPECT_NO_THROW(renderer.Shutdown());
}

TEST_F(RendererTest, DoubleShutdownIsSafe) {
  engine::Renderer renderer;
  ASSERT_TRUE(renderer.Initialize(window_, 64, 64));
  renderer.Shutdown();
  EXPECT_NO_THROW(renderer.Shutdown());
}
