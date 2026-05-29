#pragma once

#include <string>
#include <bgfx/bgfx.h>

class ShaderUtils
{
public:
    // Loads and compiles a shader from a file
    static bgfx::ShaderHandle loadShader(const std::string& filePath);

    // Creates a program from vertex + fragment shaders
    static bgfx::ProgramHandle loadProgram(const std::string& vertexPath,
                                           const std::string& fragmentPath);
};
