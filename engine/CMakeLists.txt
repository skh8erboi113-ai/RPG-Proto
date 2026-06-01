cmake_minimum_required(VERSION 3.20)

# ============================================================================
# Engine Core Library - High Performance Game Engine
# ============================================================================

# Source files - organized by module for clarity
set(ENGINE_SOURCES
  src/Engine.cpp
  src/Camera.cpp
  src/Mesh.cpp
  src/Renderer.cpp
  src/Terrain.cpp
  src/WorldStreamer.cpp
  src/ShaderUtils.cpp
  src/Types.cpp
)

# Create the engine library
add_library(engine STATIC ${ENGINE_SOURCES})

# Public include directory
target_include_directories(engine PUBLIC include)

# ============================================================================
# Compiler Optimizations for Engine
# ============================================================================
target_compile_options(engine PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /permissive- /std:c++20>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Weffc++ -march=native -mtune=native>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic -Weffc++ -march=native>
)

# Enable SIMD if requested
if(RPG_ENABLE_SIMD)
  target_compile_options(engine PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-mavx2 -mfma>
    $<$<CXX_COMPILER_ID:Clang>:-mavx2 -mfma>
  )
  target_compile_definitions(engine PRIVATE RPG_ENABLE_SIMD=1)
endif()

# ============================================================================
# Optional Graphics Dependencies (BGFX)
# ============================================================================
if(RPG_ENABLE_GRAPHICS)
  message(STATUS "Linking BGFX graphics engine...")
  target_link_libraries(engine PUBLIC bgfx bx bimg)
  target_compile_definitions(engine PUBLIC RPG_GRAPHICS_ENABLED=1)
else()
  target_compile_definitions(engine PUBLIC RPG_GRAPHICS_DISABLED=1)
endif()

# ============================================================================
# Optional Physics Dependencies (Bullet3)
# ============================================================================
if(RPG_ENABLE_PHYSICS)
  message(STATUS "Linking Bullet3 physics engine...")
  target_link_libraries(engine PUBLIC Bullet3::Bullet3Common Bullet3::Bullet3Dynamics)
  target_compile_definitions(engine PUBLIC RPG_PHYSICS_ENABLED=1)
endif()

# ============================================================================
# Optional GLFW for Input/Window Management
# ============================================================================
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(GLFW QUIET glfw3)
  if(GLFW_FOUND)
    target_link_libraries(engine PRIVATE ${GLFW_LIBRARIES})
    target_include_directories(engine PRIVATE ${GLFW_INCLUDE_DIRS})
    target_compile_definitions(engine PRIVATE RPG_GLFW_AVAILABLE=1)
    message(STATUS "GLFW found and linked")
  else()
    message(STATUS "GLFW not found - window/input will use fallback")
  endif()
endif()

# ============================================================================
# Profiling Support
# ============================================================================
if(RPG_ENABLE_PROFILING)
  target_compile_definitions(engine PRIVATE RPG_PROFILING_ENABLED=1)
endif()

# ============================================================================
# Standard Libraries
# ============================================================================
target_link_libraries(engine PRIVATE
  $<$<PLATFORM_ID:Linux>:m>
  $<$<PLATFORM_ID:Linux>:pthread>
)
