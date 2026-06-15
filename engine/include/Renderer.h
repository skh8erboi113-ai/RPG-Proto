#pragma once

#include <cstdint>
#include <memory>
#include <bgfx/bgfx.h>

struct GLFWwindow;

namespace engine {

class Camera;
class Mesh;

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool Initialize(GLFWwindow* window, uint32_t width, uint32_t height);
  void Resize(uint32_t width, uint32_t height);
  void RenderFrame(float timeSeconds);
  void Shutdown();

  void SetCamera(Camera* cam) { camera_ = cam; }

private:
  bool initialized_;
  bgfx::ProgramHandle program_;

  std::unique_ptr<Mesh> characterMesh_;

  Camera* camera_; // not owned

  bool CreateShaderProgram();
};

} // namespace engine
