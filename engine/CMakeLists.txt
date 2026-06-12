cmake_minimum_required(VERSION 3.16)

set(ENGINE_SOURCES
    src/Camera.cpp
    src/CharacterController.cpp
    src/StatsManager.cpp
    src/SkillManager.cpp
    src/Inventory.cpp
    src/CraftingManager.cpp
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
target_link_libraries(engine PUBLIC bgfx bx bimg nlohmann_json::nlohmann_json)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
target_link_libraries(engine PRIVATE ${GLFW_LIBRARIES})
target_include_directories(engine PRIVATE ${GLFW_INCLUDE_DIRS})
