#include "Engine.h"
#include <iostream>

namespace engine {

Engine::Engine()
  : initialized_(false), name_("ModernGothicEngine")
{}

Engine::~Engine() {
  if (initialized_) {
    Shutdown();
  }
}

bool Engine::Initialize() {
  // Minimal placeholder initialization
  initialized_ = true;
  std::cout << "[engine] Initialized " << name_ << std::endl;
  return initialized_;
}

void Engine::Tick(float dt) {
  if (!initialized_) return;
  // Placeholder tick
  (void)dt;
}

void Engine::Shutdown() {
  if (!initialized_) {
    return;
  }
  initialized_ = false;
  std::cout << "[engine] Shutdown " << name_ << std::endl;
}

std::string Engine::GetName() const {
  return name_;
}

} // namespace engine
