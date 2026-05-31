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

target_include_directories(engine PUBLIC include)
target_link_libraries(engine PUBLIC bgfx bx bimg)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
target_link_libraries(engine PRIVATE ${GLFW_LIBRARIES})
target_include_directories(engine PRIVATE ${GLFW_INCLUDE_DIRS})
