#include <iostream>
#include "Engine.h"
#include "StatsManager.h"
#include "Inventory.h"
#include "CraftingManager.h"
#include "CharacterController.h"

int main(int argc, char** argv) {
  (void)argc; (void)argv;

  engine::Engine eng;
  if (!eng.Initialize()) {
    std::cerr << "Failed to initialize engine\n";
    return 1;
  }

  std::cout << "Running Modern Gothic RPG Prototype\n";

  // Demonstrate RPG systems
  auto& stats = eng.GetStats();
  auto& inv = eng.GetInventory();
  auto& cm = eng.GetCrafting();
  auto& charCtrl = eng.GetCharacter();

  stats.AddXP(50.0f);
  std::cout << "Player Level: " << stats.GetLevel() << " XP: " << stats.GetXP() << "\n";

  inv.AddItem("HERB_A", 10);
  inv.AddItem("COIN_SMALL", 50);

  if (cm.Craft("health_tonic_minor", inv)) {
    std::cout << "Successfully crafted Minor Health Tonic!\n";
  }

  charCtrl.Move(1.0f, 0.0f, 1.0f);

  int frameCount = 0;
  while (eng.IsRunning()) {
    eng.Tick(1.0f / 60.0f);
    frameCount++;
    if (getenv("CI") && frameCount > 100) break;
    // Break after some frames for non-interactive demo
    if (frameCount > 60) break;
  }

  eng.Shutdown();
  return 0;
}
