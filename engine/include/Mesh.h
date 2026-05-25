#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace engine {

struct MeshVertex {
  float x, y, z;
};

class Mesh {
public:
  Mesh() = default;

  bool LoadFromOBJ(const std::string& path);

  const std::vector<MeshVertex>& GetVertices() const { return vertices_; }
  const std::vector<uint16_t>& GetIndices() const { return indices_; }

private:
  std::vector<MeshVertex> vertices_;
  std::vector<uint16_t> indices_;
};

} // namespace engine
