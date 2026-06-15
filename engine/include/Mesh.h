#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <bgfx/bgfx.h>

namespace engine {

struct MeshVertex {
  float x, y, z;
};

class Mesh {
public:
  Mesh();
  ~Mesh();

  bool LoadFromOBJ(const std::string& path);
  void Submit(bgfx::ViewId viewId, bgfx::ProgramHandle program, const float* mtx);

private:
  std::vector<MeshVertex> vertices_;
  std::vector<uint16_t> indices_;

  bgfx::VertexBufferHandle vbh_;
  bgfx::IndexBufferHandle ibh_;
  bgfx::VertexLayout layout_;

  void CreateBuffers();
};

} // namespace engine
