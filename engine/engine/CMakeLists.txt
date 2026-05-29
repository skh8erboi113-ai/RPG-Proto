cmake_minimum_required(VERSION 3.16)

# Engine library
add_library(engine
    src/Engine.cpp
    src/Renderer.cpp
    src/Camera.cpp
    src/MagicSystem.cpp
)

target_include_directories(engine PUBLIC include)
