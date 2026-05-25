#include "Renderer.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>

namespace engine {

Renderer::Renderer()
  : initialized_(false) {}

Renderer::~Renderer() {
  if (initialized_) {
    Shutdown();
  }
}

bool Renderer::Initialize(GLFWwindow* window, uint32_t width, uint32_t height) {
  bgfx::Init init;
  init.type = bgfx::RendererType::Count; // auto-detect
  init.resolution.width  = width;
  init.resolution.height = height;
  init.resolution.reset  = BGFX_RESET_VSYNC;

  bgfx::PlatformData pd{};
  pd.nwh = glfwGetWin32Window(window); // Windows handle
  init.platformData = pd;

  if (!bgfx::init(init)) {
    return false;
  }

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, width, height);

  initialized_ = true;
  return true;
}

void Renderer::Resize(uint32_t width, uint32_t height) {
  if (!initialized_) return;
  bgfx::reset(width, height, BGFX_RESET_VSYNC);
  bgfx::setViewRect(0, 0, 0, width, height);
}

void Renderer::RenderFrame() {
  if (!initialized_) return;
  bgfx::touch(0);
  bgfx::frame();
}

void Renderer::Shutdown() {
  if (!initialized_) return;
  bgfx::shutdown();
  initialized_ = false;
}

} // namespace engine
