#include "Engine.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace engine {

Engine::Engine()
  : initialized_(false),
    name_("ModernGothicEngine"),
    window_(nullptr) {}

Engine::~Engine() {
  if (initialized_) {
    Shutdown();
  }
}

bool Engine::Initialize() {
  if (!glfwInit()) {
    std::cerr << "[engine] Failed to initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window_ = glfwCreateWindow(1280, 720, "Modern Gothic RPG", nullptr, nullptr);
  if (!window_) {
    std::cerr << "[engine] Failed to create window\n";
    glfwTerminate();
    return false;
  }

  renderer_ = std::make_unique<Renderer>();
  if (!renderer_->Initialize(window_, 1280, 720)) {
    std::cerr << "[engine] Failed to initialize renderer\n";
    glfwDestroyWindow(window_);
    glfwTerminate();
    return false;
  }

  initialized_ = true;
  std::cout << "[engine] Initialized " << name_ << std::endl;
  return true;
}

void Engine::Tick(float dt) {
  if (!initialized_) return;
  (void)dt;

  if (glfwWindowShouldClose(window_)) {
    Shutdown();
    return;
  }

  glfwPollEvents();
  renderer_->RenderFrame();
}

void Engine::Shutdown() {
  if (!initialized_) return;

  renderer_.reset();

  if (window_) {
    glfwDestroyWindow(window_);
    window_ = nullptr;
  }
  glfwTerminate();

  initialized_ = false;
  std::cout << "[engine] Shutdown " << name_ << std::endl;
}

std::string Engine::GetName() const {
  return name_;
}

} // namespace engine
