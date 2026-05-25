#pragma once

#include <cstdint>

struct GLFWwindow;

namespace engine {

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool Initialize(GLFWwindow* window, uint32_t width, uint32_t height);
  void Resize(uint32_t width, uint32_t height);
  void RenderFrame();
  void Shutdown();

private:
  bool initialized_;
};

} // namespace engine
