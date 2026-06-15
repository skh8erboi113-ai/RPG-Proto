#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"
#include "WorldStreamer.h"
#include "CharacterController.h"
#include "StatsManager.h"
#include "SkillManager.h"
#include "Inventory.h"
#include "CraftingManager.h"
#include "WantedManager.h"
#include "RitualManager.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace engine {

Engine::Engine()
  : initialized_(false),
    name_("ModernGothicEngine"),
    window_(nullptr),
    timeSeconds_(0.0f) {}

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

  camera_ = std::make_unique<Camera>();
  worldStreamer_ = std::make_unique<WorldStreamer>();
  characterController_ = std::make_unique<CharacterController>();

  statsManager_ = std::make_unique<StatsManager>();
  skillManager_ = std::make_unique<SkillManager>();
  inventory_ = std::make_unique<Inventory>();
  craftingManager_ = std::make_unique<CraftingManager>();
  wantedManager_ = std::make_unique<WantedManager>();
  ritualManager_ = std::make_unique<RitualManager>();

  // Load data
  if (!skillManager_->LoadFromJSON("docs/skills/FullSkillTrees.json")) {
    std::cerr << "[engine] Failed to load skill trees\n";
  }
  if (!craftingManager_->LoadFromJSON("docs/crafting/FullRecipes.json")) {
    std::cerr << "[engine] Failed to load crafting recipes\n";
  }

  renderer_ = std::make_unique<Renderer>();
  if (!renderer_->Initialize(window_, 1280, 720)) {
    std::cerr << "[engine] Failed to initialize renderer\n";
    glfwDestroyWindow(window_);
    glfwTerminate();
    return false;
  }
  renderer_->SetCamera(camera_.get());

  initialized_ = true;
  std::cout << "[engine] Initialized " << name_ << std::endl;
  return true;
}

void Engine::Tick(float dt) {
  if (!initialized_) return;

  if (glfwWindowShouldClose(window_)) {
    initialized_ = false;
    return;
  }

  glfwPollEvents();

  timeSeconds_ += dt;

  // Update logic
  characterController_->Update(dt);

  const float* p = characterController_->GetPosition();
  worldStreamer_->SetPlayerPosition(p[0], p[1], p[2]);
  worldStreamer_->Update(dt);

  wantedManager_->Update(dt);
  statsManager_->Update(dt);
  ritualManager_->Update(dt, 0);

  // Make camera follow player (offset)
  camera_->SetPosition(p[0], p[1] + 5.0f, p[2] - 10.0f);
  camera_->LookAt(p[0], p[1], p[2]);

  renderer_->RenderFrame(timeSeconds_);
}

void Engine::Shutdown() {
  if (!initialized_) return;

  renderer_.reset();
  camera_.reset();
  worldStreamer_.reset();
  characterController_.reset();
  statsManager_.reset();
  skillManager_.reset();
  inventory_.reset();
  craftingManager_.reset();
  wantedManager_.reset();
  ritualManager_.reset();

  if (window_) {
    glfwDestroyWindow(window_);
    window_ = nullptr;
  }
  glfwTerminate();

  initialized_ = false;
  std::cout << "[engine] Shutdown " << name_ << std::endl;
}

} // namespace engine
