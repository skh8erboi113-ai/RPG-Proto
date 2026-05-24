#include <iostream>
#include "Engine.h"

int main(int argc, char** argv) {
  (void)argc; (void)argv;
  engine::Engine eng;
  if (!eng.Initialize()) {
    std::cerr << "Failed to initialize engine\n";
    return 1;
  }

  std::cout << "Running vertical slice stub with engine: " << eng.GetName() << std::endl;

  // Simple loop stub
  for (int i = 0; i < 3; ++i) {
    eng.Tick(1.0f / 60.0f);
  }

  eng.Shutdown();
  return 0;
}
