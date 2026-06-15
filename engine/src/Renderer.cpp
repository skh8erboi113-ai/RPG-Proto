#include "Renderer.h"
#include "Camera.h"
#include "ShaderUtils.h"
#include "Mesh.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <GLFW/glfw3.h>
#include <iostream>

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3native.h>
#endif

namespace engine {

Renderer::Renderer()
  : initialized_(false),
    program_(BGFX_INVALID_HANDLE),
    camera_(nullptr) {
}

Renderer::~Renderer() {
  if (initialized_) {
    Shutdown();
  }
}

bool Renderer::Initialize(GLFWwindow* window, uint32_t width, uint32_t height) {
  bgfx::Init init;
  init.type = bgfx::RendererType::Count;
  init.resolution.width  = width;
  init.resolution.height = height;
  init.resolution.reset  = BGFX_RESET_VSYNC;

#if BX_PLATFORM_LINUX
  init.platformData.ndt = glfwGetX11Display();
  init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#endif

  if (!bgfx::init(init)) {
    std::cerr << "[Renderer] bgfx init failed\n";
    return false;
  }

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, width, height);

  if (!CreateShaderProgram()) {
    std::cerr << "[Renderer] Failed to create shader program\n";
  }

  characterMesh_ = std::make_unique<Mesh>();
  if (!characterMesh_->LoadFromOBJ("assets/simple_box.obj")) {
    std::cerr << "[Renderer] Failed to load assets/simple_box.obj\n";
  }

  initialized_ = true;
  return true;
}

bool Renderer::CreateShaderProgram() {
  program_ = ShaderUtils::loadProgram("shaders/vs_basic.bin", "shaders/fs_basic.bin");
  return bgfx::isValid(program_);
}

void Renderer::Resize(uint32_t width, uint32_t height) {
  if (!initialized_) return;
  bgfx::reset(width, height, BGFX_RESET_VSYNC);
  bgfx::setViewRect(0, 0, 0, width, height);
}

void Renderer::RenderFrame(float timeSeconds) {
  if (!initialized_) return;

  bgfx::touch(0);

  if (camera_) {
    bgfx::setViewTransform(0, camera_->GetViewMatrix(), camera_->GetProjMatrix());
  }

  float mtx[16];
  bx::mtxRotateY(mtx, timeSeconds);

  if (bgfx::isValid(program_)) {
    characterMesh_->Submit(0, program_, mtx);
  }

  bgfx::frame();
}

void Renderer::Shutdown() {
  if (!initialized_) return;

  characterMesh_.reset();
  if (bgfx::isValid(program_)) bgfx::destroy(program_);

  bgfx::shutdown();
  initialized_ = false;
}

} // namespace engine
