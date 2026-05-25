cmake_minimum_required(VERSION 3.16)
project(modern_gothic_rpg CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Third‑party libs
add_subdirectory(third_party/bx)
add_subdirectory(third_party/bimg)
add_subdirectory(third_party/bgfx)
add_subdirectory(third_party/glfw)

# Engine + Game + Tests
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)
