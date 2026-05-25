cmake_minimum_required(VERSION 3.16)
project(engine)

add_library(engine STATIC
  src/Engine.cpp
  src/Renderer.cpp
)

target_include_directories(engine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC
  bgfx
  bx
  bimg
  glfw
)

target_compile_features(engine PUBLIC cxx_std_17)
