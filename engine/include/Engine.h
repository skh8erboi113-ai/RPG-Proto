#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace engine {

class Renderer;
class Camera;
class WorldStreamer;
class CharacterController;
class StatsManager;
class SkillManager;
class Inventory;
class CraftingManager;

class Engine {
public:
  Engine();
  ~Engine();

  bool Initialize();
  void Tick(float dt);
  void Shutdown();

  std::string GetName() const;
  bool IsRunning() const { return initialized_; }

  StatsManager& GetStats() { return *statsManager_; }
  SkillManager& GetSkills() { return *skillManager_; }
  Inventory& GetInventory() { return *inventory_; }
  CraftingManager& GetCrafting() { return *craftingManager_; }
  CharacterController& GetCharacter() { return *characterController_; }

private:
  bool initialized_;
  std::string name_;

  GLFWwindow* window_;
  std::unique_ptr<Renderer> renderer_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<WorldStreamer> worldStreamer_;
  std::unique_ptr<CharacterController> characterController_;

  std::unique_ptr<StatsManager> statsManager_;
  std::unique_ptr<SkillManager> skillManager_;
  std::unique_ptr<Inventory> inventory_;
  std::unique_ptr<CraftingManager> craftingManager_;

  float timeSeconds_;
};

} // namespace engine
