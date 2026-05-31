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

  while (true) {
    eng.Tick(1.0f / 60.0f);
  }

  return 0;
}
