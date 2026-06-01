cmake_minimum_required(VERSION 3.16)
add_executable(game src/main.cpp)
target_link_libraries(game PRIVATE engine)
