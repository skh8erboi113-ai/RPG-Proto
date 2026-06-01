#include <iostream>
#include "Engine.h"

int main(int argc, char** argv) {
  (void)argc; (void)argv;

  engine::Engine eng;
  if (!eng.Initialize()) {
    std::cerr << "Failed to initialize engine\n";
    return 1;
  }

  std::cout << "Running engine: " << eng.GetName() << std::endl;

  // Reduced iteration count for demonstration/CI if needed,
  // but usually a game loop runs until exit.
  int frameCount = 0;
  while (eng.IsRunning()) {
    eng.Tick(1.0f / 60.0f);
    frameCount++;
    // Auto-exit after 100 frames if in CI
    if (getenv("CI") && frameCount > 100) break;
  }

  eng.Shutdown();
  return 0;
}
