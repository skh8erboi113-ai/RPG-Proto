cmake_minimum_required(VERSION 3.16)
project(game)

add_executable(game
  src/main.cpp
)

target_link_libraries(game PRIVATE engine)
target_compile_features(game PRIVATE cxx_std_17)
