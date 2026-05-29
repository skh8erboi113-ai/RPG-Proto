cmake_minimum_required(VERSION 3.16)
project(RPG-Proto CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add bgfx.cmake (this brings in bx, bimg, bgfx)
add_subdirectory(external/bgfx)

# Add your engine
add_subdirectory(engine)
