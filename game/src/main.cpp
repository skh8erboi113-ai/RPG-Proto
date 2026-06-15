#include <iostream>
#include "Engine.h"
#include "StatsManager.h"
#include "Inventory.h"
#include "CraftingManager.h"
#include "CharacterController.h"
#include "WantedManager.h"
#include "RitualManager.h"

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
  auto& wanted = eng.GetWanted();
  auto& ritual = eng.GetRitual();

  stats.AddXP(50.0f);
  std::cout << "Player Level: " << stats.GetLevel()
            << " | HP: " << stats.GetHealth() << "/" << stats.GetMaxHealth()
            << " | Stamina: " << stats.GetStamina() << "\n";

  inv.AddItem("HERB_A", 10);
  inv.AddItem("COIN_SMALL", 50);

  if (cm.Craft("health_tonic_minor", inv)) {
    std::cout << "Successfully crafted Minor Health Tonic!\n";
    stats.Heal(20.0f);
  }

  wanted.ReportCrime("Ashbourne", 15);
  std::cout << "Wanted Level in Ashbourne: " << (int)wanted.GetWantedLevel("Ashbourne") << "\n";

  ritual.StartRitual("Exorcism");
  std::cout << "Started Exorcism ritual...\n";

  charCtrl.Move(1.0f, 0.0f, 1.0f);

  int frameCount = 0;
  while (eng.IsRunning()) {
    eng.Tick(1.0f / 60.0f);
    frameCount++;

    if (frameCount % 10 == 0 && ritual.GetProgress() < 1.0f) {
       std::cout << "Ritual progress: " << (int)(ritual.GetProgress() * 100) << "%\n";
    }

    if (getenv("CI") && frameCount > 100) break;
    if (frameCount > 60) break;
  }

  if (ritual.WasSuccess()) {
    std::cout << "Ritual progress: 100% - Finished!\n";
  }

  eng.Shutdown();
  return 0;
}
