#pragma once

#include <cstdint>
#include <bgfx/bgfx.h>

struct GLFWwindow;

namespace engine {

class Camera;

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool Initialize(GLFWwindow* window, uint32_t width, uint32_t height);
  void Resize(uint32_t width, uint32_t height);
  void RenderFrame(float timeSeconds);
  void Shutdown();

private:
  bool initialized_;
  bgfx::VertexLayout vertexLayout_;
  bgfx::ProgramHandle program_;
  bgfx::VertexBufferHandle vbh_;
  bgfx::IndexBufferHandle ibh_;

  Camera* camera_; // not owned

  bool CreateCube();
  bool CreateShaderProgram();
};

} // namespace engine
