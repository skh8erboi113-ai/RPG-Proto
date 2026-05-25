#include "ShaderUtils.h"

#include <bx/file.h>
#include <bx/allocator.h>
#include <iostream>

namespace {

bx::DefaultAllocator s_allocator;

const bgfx::Memory* loadFileToMemory(const std::string& path) {
  bx::FileReader reader;
  if (!bx::open(&reader, path.c_str())) {
    std::cerr << "[Shader] Failed to open: " << path << "\n";
    return nullptr;
  }

  uint32_t size = (uint32_t)bx::getSize(&reader);
  const bgfx::Memory* mem = bgfx::alloc(size + 1);
  bx::read(&reader, mem->data, size);
  bx::close(&reader);
  mem->data[size] = '\0';
  return mem;
}

} // namespace

namespace engine {

bgfx::ShaderHandle LoadShader(const std::string& path) {
  const bgfx::Memory* mem = loadFileToMemory(path);
  if (!mem) {
    return BGFX_INVALID_HANDLE;
  }
  return bgfx::createShader(mem);
}

bgfx::ProgramHandle LoadProgram(const std::string& vsPath, const std::string& fsPath) {
  bgfx::ShaderHandle vsh = LoadShader(vsPath);
  bgfx::ShaderHandle fsh = LoadShader(fsPath);
  if (!bgfx::isValid(vsh) || !bgfx::isValid(fsh)) {
    std::cerr << "[Shader] Failed to load shaders: " << vsPath << " / " << fsPath << "\n";
    if (bgfx::isValid(vsh)) bgfx::destroy(vsh);
    if (bgfx::isValid(fsh)) bgfx::destroy(fsh);
    return BGFX_INVALID_HANDLE;
  }
  bgfx::ProgramHandle prog = bgfx::createProgram(vsh, fsh, true);
  return prog;
}

} // namespace engine
