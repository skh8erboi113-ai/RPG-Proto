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

  std::cout << "Running Modern Gothic RPG Prototype - E2E Alignment Loop\n";

  auto& charCtrl = eng.GetCharacter();
  auto& enemies = eng.GetEnemies();
  auto& inventory = eng.GetInventory();
  auto& stats = eng.GetStats();
  auto& ritual = eng.GetRitual();

  // Setup scenario
  enemies.SpawnEnemy("Elite_Ghost", 5.0f, 0.0f, 5.0f, "MAT_SPIRIT_ASH");

  int frameCount = 0;
  bool ritualStarted = false;

  while (eng.IsRunning()) {
    eng.Tick(1.0f / 60.0f);
    frameCount++;

    // 1. Move to enemy
    if (frameCount == 10) {
      std::cout << "[Step 1] Moving to elite ghost...\n";
      charCtrl.SetPosition(4.0f, 0.0f, 4.0f);
    }

    // 2. Attack and defeat enemy to get MAT_SPIRIT_ASH
    if (frameCount >= 20 && frameCount <= 22) {
      charCtrl.PrimaryAttack(eng);
    }

    // 3. Collect loot and adjust alignment
    if (frameCount == 30) {
      if (inventory.GetItemCount("MAT_SPIRIT_ASH") > 0) {
        std::cout << "[Step 2] MAT_SPIRIT_ASH collected! Adjusting alignment to Angelic...\n";
        stats.AdjustAlignment(0.8f);
      }
    }

    // 4. Start ritual
    if (frameCount == 40 && inventory.GetItemCount("MAT_SPIRIT_ASH") > 0) {
        std::cout << "[Step 3] Starting Purify Ritual...\n";
        inventory.RemoveItem("MAT_SPIRIT_ASH", 1);
        ritual.StartRitual("Purify");
        ritualStarted = true;
    }

    // 5. Update ritual
    if (ritualStarted) {
      if (ritual.Update(1.0f/60.0f, 82, eng)) { // Pass 'R' to speed up
        std::cout << "[Step 4] Ritual complete!\n";
        ritualStarted = false;
      }
    }

    if (getenv("CI") && frameCount > 500) break;
    if (frameCount > 300) break;
  }

  std::cout << "\n--- Final State ---\n";
  std::cout << "Alignment: " << stats.GetAlignment() << " (" << (int)stats.GetAlignmentType() << ")\n";
  std::cout << "Inventory HOLY_RELICT: " << inventory.GetItemCount("HOLY_RELICT") << "\n";
  std::cout << "Inventory SPIRIT_ESSENCE: " << inventory.GetItemCount("SPIRIT_ESSENCE") << "\n";
  std::cout << "Inventory DEMON_HEART: " << inventory.GetItemCount("DEMON_HEART") << "\n";

  eng.Shutdown();
  return 0;
}
