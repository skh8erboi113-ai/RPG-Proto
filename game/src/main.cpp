#include <iostream>
#include "Engine.h"
#include "StatsManager.h"
#include "Inventory.h"
#include "CraftingManager.h"
#include "CharacterController.h"
#include "WantedManager.h"
#include "RitualManager.h"
#include "EnemyManager.h"
#include "InteractionManager.h"

int main(int argc, char** argv) {
  (void)argc; (void)argv;

  engine::Engine eng;
  if (!eng.Initialize()) {
    std::cerr << "Failed to initialize engine\n";
    return 1;
  }

  std::cout << "Running Modern Gothic RPG Prototype\n";

  auto& charCtrl = eng.GetCharacter();
  auto& interaction = eng.GetInteraction();
  auto& enemies = eng.GetEnemies();
  auto& inventory = eng.GetInventory();

  // Setup Vertical Slice scenario
  interaction.AddInteractable("Clue_Manor_01", 5.0f, 0.0f, 5.0f, "ITEM_CLUE_A");
  enemies.SpawnEnemy("Minor_Ghost", 10.0f, 0.0f, 10.0f);

  int frameCount = 0;
  while (eng.IsRunning()) {
    eng.Tick(1.0f / 60.0f);
    frameCount++;

    // Simulate mission flow
    if (frameCount == 10) {
      std::cout << "[Mission] Moving to manor clue...\n";
      charCtrl.SetPosition(4.5f, 0.0f, 4.5f);
    }

    if (frameCount == 30) {
      std::cout << "[Mission] Clue collected. Moving to ghost encounter...\n";
      charCtrl.SetPosition(9.0f, 0.0f, 9.0f);
    }

    if (frameCount >= 40 && frameCount <= 42) {
      charCtrl.PrimaryAttack(eng);
    }

    if (getenv("CI") && frameCount > 100) break;
    if (frameCount > 80) break;
  }

  std::cout << "[Mission] Inventory CLUE count: " << inventory.GetItemCount("ITEM_CLUE_A") << "\n";

  eng.Shutdown();
  return 0;
}
