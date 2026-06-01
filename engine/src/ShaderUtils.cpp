#include "ShaderUtils.h"
#include <bx/file.h>
#include <bx/allocator.h>
#include <iostream>
#include <vector>
#include <filesystem>

namespace {

bx::DefaultAllocator s_allocator;

const bgfx::Memory* loadFileToMemory(const std::string& path) {
  std::vector<std::string> searchPaths = {
    path,
    "game/" + path,
    "../" + path,
    "../../" + path,
    "build/game/" + path
  };

  bx::FileReader reader;
  bx::Error err;
  bool opened = false;
  std::string finalPath;

  for (const auto& p : searchPaths) {
    if (bx::open(&reader, p.c_str(), &err)) {
      opened = true;
      finalPath = p;
      break;
    }
    err.reset();
  }

  if (!opened) {
    std::cerr << "[Shader] Failed to open: " << path << " (tried multiple paths)\n";
    return nullptr;
  }

  int64_t size = bx::getSize(&reader);
  const bgfx::Memory* mem = bgfx::alloc((uint32_t)size + 1);
  bx::read(&reader, mem->data, (int32_t)size, &err);
  bx::close(&reader);
  mem->data[size] = '\0';

  std::cout << "[Shader] Successfully loaded: " << finalPath << " (" << size << " bytes)\n";
  return mem;
}

} // namespace

bgfx::ShaderHandle ShaderUtils::loadShader(const std::string& path) {
  const bgfx::Memory* mem = loadFileToMemory(path);
  if (!mem) {
    return BGFX_INVALID_HANDLE;
  }
  return bgfx::createShader(mem);
}

bgfx::ProgramHandle ShaderUtils::loadProgram(const std::string& vsPath, const std::string& fsPath) {
  bgfx::ShaderHandle vsh = loadShader(vsPath);
  bgfx::ShaderHandle fsh = loadShader(fsPath);
  if (!bgfx::isValid(vsh) || !bgfx::isValid(fsh)) {
    std::cerr << "[Shader] Failed to load shaders: " << vsPath << " / " << fsPath << "\n";
    if (bgfx::isValid(vsh)) bgfx::destroy(vsh);
    if (bgfx::isValid(fsh)) bgfx::destroy(fsh);
    return BGFX_INVALID_HANDLE;
  }
  bgfx::ProgramHandle prog = bgfx::createProgram(vsh, fsh, true);
  return prog;
}
