cmake_minimum_required(VERSION 3.20)
project(RPG-Proto CXX)

# ============================================================================
# Compiler Configuration for Maximum Performance
# ============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG -flto")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-inline")

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

# ============================================================================
# Graphics & Dependencies
# ============================================================================

# bgfx.cmake - Graphics abstraction layer
FetchContent_Declare(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG master
)
FetchContent_MakeAvailable(bgfx)

# GoogleTest - Unit testing
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# nlohmann/json - JSON parsing
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# ============================================================================
# Shader Compilation Setup (Optional - graceful fallback if shaderc unavailable)
# ============================================================================
set(SHADER_SRC_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(SHADER_BIN_DIR "${CMAKE_BINARY_DIR}/shaders")
set(GAME_SHADER_BIN_DIR "${CMAKE_BINARY_DIR}/game/shaders")

file(MAKE_DIRECTORY "${SHADER_BIN_DIR}")
file(MAKE_DIRECTORY "${GAME_SHADER_BIN_DIR}")

# Detect if shaderc is available from bgfx
find_program(SHADERC_EXE NAMES shaderc PATHS "${bgfx_BINARY_DIR}/bin" NO_DEFAULT_PATH)

if(SHADERC_EXE)
  message(STATUS "[Shaders] Found shaderc at: ${SHADERC_EXE}")
  set(SHADER_COMPILE_ENABLED ON)
else()
  message(STATUS "[Shaders] shaderc not found. Shaders will not be compiled. (Graphics may not work)")
  set(SHADER_COMPILE_ENABLED OFF)
endif()

# Platform and profile detection for shader compilation
if(SHADER_COMPILE_ENABLED)
  if(LINUX)
    set(SHADER_PLATFORM "linux")
    set(SHADER_PROFILE "120")
  elseif(WIN32)
    set(SHADER_PLATFORM "windows")
    set(SHADER_PROFILE "s_5_0")
  elseif(APPLE)
    set(SHADER_PLATFORM "osx")
    set(SHADER_PROFILE "metal")
  else()
    set(SHADER_PLATFORM "linux")
    set(SHADER_PROFILE "120")
  endif()

  message(STATUS "[Shaders] Compiling for platform: ${SHADER_PLATFORM}, profile: ${SHADER_PROFILE}")

  # Macro to compile a single shader
  macro(compile_shader SHADER_NAME TYPE)
    set(SHADER_SRC "${SHADER_SRC_DIR}/${SHADER_NAME}.sc")
    set(SHADER_OUT "${SHADER_BIN_DIR}/${SHADER_NAME}.bin")
    set(SHADER_OUT_GAME "${GAME_SHADER_BIN_DIR}/${SHADER_NAME}.bin")
    
    add_custom_command(
      OUTPUT "${SHADER_OUT}"
      COMMAND "${SHADERC_EXE}"
              -f "${SHADER_SRC}"
              -o "${SHADER_OUT}"
              --type ${TYPE}
              --platform ${SHADER_PLATFORM}
              -p ${SHADER_PROFILE}
              -i "${bgfx_SOURCE_DIR}/src"
              --varyingdef "${SHADER_SRC_DIR}/varying.def.sc"
      DEPENDS "${SHADER_SRC}" "${SHADER_SRC_DIR}/varying.def.sc"
      COMMENT "[Shaders] Compiling ${SHADER_NAME} (${TYPE})..."
      VERBATIM
    )
    
    # Copy to game working directory
    add_custom_command(
      OUTPUT "${SHADER_OUT_GAME}"
      COMMAND "${CMAKE_COMMAND}" -E copy "${SHADER_OUT}" "${SHADER_OUT_GAME}"
      DEPENDS "${SHADER_OUT}"
      COMMENT "[Shaders] Copying ${SHADER_NAME}.bin to game directory..."
    )
    
    list(APPEND SHADER_BINS "${SHADER_OUT_GAME}")
  endmacro()

  # Compile all shaders
  compile_shader(vs_basic vertex)
  compile_shader(fs_basic fragment)

  # Create shader build target
  add_custom_target(engine_shaders ALL DEPENDS ${SHADER_BINS})
else()
  # Stub target if shaderc not available
  add_custom_target(engine_shaders)
endif()

# ============================================================================
# Build Subdirectories
# ============================================================================

enable_testing()

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)
