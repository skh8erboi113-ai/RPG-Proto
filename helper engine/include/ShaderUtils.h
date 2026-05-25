#pragma once

#include <bgfx/bgfx.h>
#include <string>

namespace engine {

bgfx::ShaderHandle LoadShader(const std::string& path);
bgfx::ProgramHandle LoadProgram(const std::string& vsPath, const std::string& fsPath);

} // namespace engine
