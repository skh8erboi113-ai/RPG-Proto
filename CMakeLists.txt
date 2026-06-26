cmake_minimum_required(VERSION 3.20)
project(RPG-Proto CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
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

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Explicitly ensure glfw target has its include directory in the interface
FetchContent_GetProperties(glfw)
if(glfw_SOURCE_DIR)
    target_include_directories(glfw INTERFACE ${glfw_SOURCE_DIR}/include)
endif()

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

find_package(Python3 COMPONENTS Interpreter REQUIRED)

# --- Asset pipeline -----------------------------------------------------
# Renderer::Initialize() loads assets/simple_box.obj and shaders/*.bin at
# runtime relative to the working directory. A fresh clone has neither
# placeholder source assets nor the generated mesh, so without this step
# the engine builds fine but fails at runtime. These custom commands run
# the existing scripts/ pipeline (export placeholders -> generate mesh ->
# import/classify -> write metadata) automatically as part of the build,
# with real file outputs so ninja/make only reruns steps when their
# inputs actually change.

set(ASSET_DIR ${CMAKE_SOURCE_DIR}/assets)
set(IMPORTED_ASSET_DIR ${CMAKE_SOURCE_DIR}/imported_assets)
set(ASSET_METADATA_FILE ${CMAKE_SOURCE_DIR}/asset_metadata.json)
set(ASSET_STAMP_FILE ${CMAKE_BINARY_DIR}/asset_pipeline.stamp)

add_custom_command(
  OUTPUT ${ASSET_DIR}/placeholder_character.fbx
         ${ASSET_DIR}/placeholder_env_block.fbx
         ${ASSET_DIR}/placeholder_horse.fbx
  COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/export_placeholder_assets.sh
  DEPENDS ${CMAKE_SOURCE_DIR}/scripts/export_placeholder_assets.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Exporting placeholder source assets"
  VERBATIM
)

add_custom_command(
  OUTPUT ${ASSET_DIR}/simple_box.obj
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/generate_placeholder_mesh.py
  DEPENDS ${CMAKE_SOURCE_DIR}/scripts/generate_placeholder_mesh.py
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Generating placeholder character mesh (assets/simple_box.obj)"
  VERBATIM
)

add_custom_command(
  OUTPUT ${ASSET_STAMP_FILE}
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/import_assets.py
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/generate_asset_metadata.py
  COMMAND ${CMAKE_COMMAND} -E touch ${ASSET_STAMP_FILE}
  DEPENDS ${CMAKE_SOURCE_DIR}/scripts/import_assets.py
          ${CMAKE_SOURCE_DIR}/scripts/generate_asset_metadata.py
          ${ASSET_DIR}/placeholder_character.fbx
          ${ASSET_DIR}/placeholder_env_block.fbx
          ${ASSET_DIR}/placeholder_horse.fbx
          ${ASSET_DIR}/simple_box.obj
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Importing/classifying assets and generating asset_metadata.json"
  VERBATIM
)

add_custom_target(asset_pipeline ALL
  DEPENDS ${ASSET_STAMP_FILE}
)
# -------------------------------------------------------------------------

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)
