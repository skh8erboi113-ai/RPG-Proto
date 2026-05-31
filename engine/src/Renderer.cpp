#include "Renderer.h"
#include "Camera.h"
#include "ShaderUtils.h"

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

namespace {

struct PosColorVertex {
  float x, y, z;
  uint32_t abgr;
};

static PosColorVertex s_cubeVertices[] = {
  {-1.0f,  1.0f,  1.0f, 0xff0000ff},
  { 1.0f,  1.0f,  1.0f, 0xff00ff00},
  {-1.0f, -1.0f,  1.0f, 0xffff0000},
  { 1.0f, -1.0f,  1.0f, 0xffffffff},
  {-1.0f,  1.0f, -1.0f, 0xff0000ff},
  { 1.0f,  1.0f, -1.0f, 0xff00ff00},
  {-1.0f, -1.0f, -1.0f, 0xffff0000},
  { 1.0f, -1.0f, -1.0f, 0xffffffff},
};

static const uint16_t s_cubeIndices[] = {
  0, 1, 2, 1, 3, 2,
  4, 6, 5, 5, 6, 7,
  0, 2, 4, 4, 2, 6,
  1, 5, 3, 5, 7, 3,
  0, 4, 1, 4, 1, 5,
  2, 3, 6, 6, 3, 7,
};

} // namespace

namespace engine {

Renderer::Renderer()
  : initialized_(false),
    program_(BGFX_INVALID_HANDLE),
    vbh_(BGFX_INVALID_HANDLE),
    ibh_(BGFX_INVALID_HANDLE),
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

  vertexLayout_.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
    .end();

  if (!CreateCube()) {
    return false;
  }

  if (!CreateShaderProgram()) {
    std::cerr << "[Renderer] Failed to create shader program\n";
  }

  initialized_ = true;
  return true;
}

bool Renderer::CreateCube() {
  vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
    vertexLayout_
  );
  ibh_ = bgfx::createIndexBuffer(
    bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices))
  );
  return bgfx::isValid(vbh_) && bgfx::isValid(ibh_);
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

  float mtx[16];
  bx::mtxRotateY(mtx, timeSeconds);

  bgfx::setTransform(mtx);
  bgfx::setVertexBuffer(0, vbh_);
  bgfx::setIndexBuffer(ibh_);
  bgfx::setState(BGFX_STATE_DEFAULT);

  if (bgfx::isValid(program_)) {
    bgfx::submit(0, program_, 0, BGFX_DISCARD_ALL);
  } else {
    bgfx::submit(0, BGFX_INVALID_HANDLE, 0, BGFX_DISCARD_ALL);
  }

  bgfx::frame();
}

void Renderer::Shutdown() {
  if (!initialized_) return;

  if (bgfx::isValid(vbh_)) bgfx::destroy(vbh_);
  if (bgfx::isValid(ibh_)) bgfx::destroy(ibh_);
  if (bgfx::isValid(program_)) bgfx::destroy(program_);

  bgfx::shutdown();
  initialized_ = false;
}

} // namespace engine
