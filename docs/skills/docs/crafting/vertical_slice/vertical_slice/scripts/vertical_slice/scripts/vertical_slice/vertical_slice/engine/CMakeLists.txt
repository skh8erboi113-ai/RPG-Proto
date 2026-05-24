cmake_minimum_required(VERSION 3.16)
project(engine)

add_library(engine STATIC
  src/Engine.cpp
)

target_include_directories(engine PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(engine PUBLIC cxx_std_17)
