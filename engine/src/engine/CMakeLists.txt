cmake_minimum_required(VERSION 3.16)

add_library(engine
    src/Camera.cpp
    src/Mesh.cpp
    src/ShaderUtils.cpp
    src/Terrain.cpp
)

target_include_directories(engine PUBLIC include)
