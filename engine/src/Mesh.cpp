#include "Mesh.h"
#include <iostream>

namespace engine {

bool Mesh::LoadFromFile(const std::string& path) {
  std::cout << "[Mesh] Stub load from: " << path << std::endl;
  // TODO: implement real OBJ/GLTF loading.
  return true;
}

} // namespace engine
