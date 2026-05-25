#include "Terrain.h"
#include <iostream>

namespace engine {

bool Terrain::Initialize(int width, int height) {
  std::cout << "[Terrain] Initialize " << width << "x" << height << std::endl;
  // TODO: generate heightmap, chunks, etc.
  return true;
}

void Terrain::Update(float dt) {
  (void)dt;
  // TODO: LOD, streaming, etc.
}

} // namespace engine
