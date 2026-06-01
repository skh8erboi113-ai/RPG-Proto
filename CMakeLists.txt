cmake_minimum_required(VERSION 3.20)
project(RPG-Proto CXX)

# ============================================================================
# Compiler Configuration for Maximum Performance
# ============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG -flto")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-inline")

# Enable LTO for all configurations
include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

# Policy settings
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

# ============================================================================
# Project Configuration Flags
# ============================================================================
option(RPG_ENABLE_GRAPHICS "Enable BGFX graphics rendering" OFF)
option(RPG_ENABLE_PHYSICS "Enable physics engine (Bullet3)" OFF)
option(RPG_ENABLE_AUDIO "Enable audio support" OFF)
option(RPG_ENABLE_NETWORKING "Enable networking support" OFF)
option(RPG_BUILD_TESTS "Build unit tests" ON)
option(RPG_BUILD_GAME "Build game executable" ON)
option(RPG_ENABLE_PROFILING "Enable profiling and performance monitoring" ON)
option(RPG_ENABLE_SIMD "Enable SIMD optimizations" ON)

message(STATUS "RPG-Proto Configuration:")
message(STATUS "  Graphics Support: ${RPG_ENABLE_GRAPHICS}")
message(STATUS "  Physics Support: ${RPG_ENABLE_PHYSICS}")
message(STATUS "  Audio Support: ${RPG_ENABLE_AUDIO}")
message(STATUS "  Networking Support: ${RPG_ENABLE_NETWORKING}")
message(STATUS "  Build Tests: ${RPG_BUILD_TESTS}")
message(STATUS "  SIMD Optimizations: ${RPG_ENABLE_SIMD}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)
include(FindPackageHandleStandardArgs)

# ============================================================================
# GoogleTest (Always available for tests)
# ============================================================================
if(RPG_BUILD_TESTS)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  FetchContent_MakeAvailable(googletest)
  enable_testing()
endif()

# ============================================================================
# Optional: BGFX Graphics Engine
# ============================================================================
if(RPG_ENABLE_GRAPHICS)
  message(STATUS "Fetching BGFX graphics engine...")
  FetchContent_Declare(
    bgfx
    GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
    GIT_TAG master
    GIT_SHALLOW ON
  )
  FetchContent_MakeAvailable(bgfx)
endif()

# ============================================================================
# Optional: Bullet3 Physics Engine
# ============================================================================
if(RPG_ENABLE_PHYSICS)
  message(STATUS "Fetching Bullet3 physics engine...")
  FetchContent_Declare(
    bullet3
    GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
    GIT_TAG master
    GIT_SHALLOW ON
  )
  FetchContent_MakeAvailable(bullet3)
endif()

# ============================================================================
# Core Subdirectories
# ============================================================================
add_subdirectory(engine)

if(RPG_BUILD_GAME)
  add_subdirectory(game)
endif()

if(RPG_BUILD_TESTS)
  add_subdirectory(tests)
endif()

# ============================================================================
# Install Targets (optional)
# ============================================================================
install(DIRECTORY engine/include/engine DESTINATION include)
