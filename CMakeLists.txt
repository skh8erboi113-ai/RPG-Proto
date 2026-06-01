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

# bgfx.cmake
FetchContent_Declare(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG master
)
FetchContent_MakeAvailable(bgfx)

# GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# nlohmann/json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

enable_testing()

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)
