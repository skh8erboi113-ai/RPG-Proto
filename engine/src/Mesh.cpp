#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace engine {

bool Mesh::LoadFromOBJ(const std::string& path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "[Mesh] Failed to open OBJ: " << path << "\n";
    return false;
  }

  std::vector<MeshVertex> tempVerts;
  std::vector<uint16_t> tempIndices;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    std::string tag;
    iss >> tag;

    if (tag == "v") {
      float x, y, z;
      iss >> x >> y >> z;
      tempVerts.push_back({x, y, z});
    } else if (tag == "f") {
      uint32_t i1, i2, i3;
      char slash;
      // Very simple: "f a b c" or "f a/b/c ..."
      if (!(iss >> i1 >> i2 >> i3)) {
        iss.clear();
        iss.str(line.substr(2));
        std::string v1, v2, v3;
        iss >> v1 >> v2 >> v3;
        auto parseIndex = [](const std::string& v) {
          std::istringstream vs(v);
          uint32_t idx;
          vs >> idx;
          return idx;
        };
        i1 = parseIndex(v1);
        i2 = parseIndex(v2);
        i3 = parseIndex(v3);
      }
      tempIndices.push_back(static_cast<uint16_t>(i1 - 1));
      tempIndices.push_back(static_cast<uint16_t>(i2 - 1));
      tempIndices.push_back(static_cast<uint16_t>(i3 - 1));
    }
  }

  if (tempVerts.empty() || tempIndices.empty()) {
    std::cerr << "[Mesh] OBJ has no verts or indices: " << path << "\n";
    return false;
  }

  vertices_ = std::move(tempVerts);
  indices_ = std::move(tempIndices);
  std::cout << "[Mesh] Loaded OBJ: " << path
            << " (verts=" << vertices_.size()
            << ", indices=" << indices_.size() << ")\n";
  return true;
}

} // namespace engine
