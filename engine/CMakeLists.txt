cmake_minimum_required(VERSION 3.16)

add_library(engine
    src/Camera.cpp
    src/Mesh.cpp
    src/ShaderUtils.cpp
    src/Terrain.cpp
    src/Engine.cpp
    src/Renderer.cpp
    src/WorldStreamer.cpp
)

# Create the engine library
add_library(engine STATIC ${ENGINE_SOURCES})

# Public include directory
target_include_directories(engine PUBLIC include)
target_link_libraries(engine PUBLIC bgfx bx bimg)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
target_link_libraries(engine PRIVATE ${GLFW_LIBRARIES})
target_include_directories(engine PRIVATE ${GLFW_INCLUDE_DIRS})

# Shader compilation
set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SHADER_BIN_DIR ${CMAKE_BINARY_DIR}/game/shaders)

file(MAKE_DIRECTORY ${SHADER_BIN_DIR})

set(SHADERC_EXE ${CMAKE_BINARY_DIR}/_deps/bgfx-build/cmake/bgfx/shaderc)
set(BGFX_SRC_DIR ${CMAKE_BINARY_DIR}/_deps/bgfx-src)

macro(compile_shader SHADER_NAME TYPE PLATFORM PROFILE)
    add_custom_command(
        OUTPUT ${SHADER_BIN_DIR}/${SHADER_NAME}.bin
        COMMAND ${SHADERC_EXE}
                -f ${SHADER_SRC_DIR}/${SHADER_NAME}.sc
                -o ${SHADER_BIN_DIR}/${SHADER_NAME}.bin
                --type ${TYPE}
                --platform ${PLATFORM}
                -p ${PROFILE}
                -i ${BGFX_SRC_DIR}/bgfx/src
                --varyingdef ${SHADER_SRC_DIR}/varying.def.sc
        DEPENDS ${SHADER_SRC_DIR}/${SHADER_NAME}.sc ${SHADER_SRC_DIR}/varying.def.sc ${SHADERC_EXE}
        COMMENT "Compiling shader ${SHADER_NAME}"
    )
    list(APPEND SHADER_BINS ${SHADER_BIN_DIR}/${SHADER_NAME}.bin)
endmacro()

if(LINUX)
    compile_shader(vs_basic vertex linux 120)
    compile_shader(fs_basic fragment linux 120)
elseif(WIN32)
    compile_shader(vs_basic vertex windows s_5_0)
    compile_shader(fs_basic fragment windows s_5_0)
endif()

add_custom_target(engine_shaders ALL DEPENDS ${SHADER_BINS})
add_dependencies(engine engine_shaders)
