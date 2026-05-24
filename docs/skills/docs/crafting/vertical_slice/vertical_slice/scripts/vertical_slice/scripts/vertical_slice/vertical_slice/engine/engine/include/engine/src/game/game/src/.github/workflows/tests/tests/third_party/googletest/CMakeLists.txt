cmake_minimum_required(VERSION 3.16)
project(googletest-placeholder LANGUAGES CXX)

# Minimal placeholder targets to satisfy tests when real googletest is not available.
# These targets do not implement real GoogleTest functionality; replace with real submodule for full tests.

add_library(gtest INTERFACE)
add_library(gtest_main INTERFACE)

target_include_directories(gtest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(gtest_main INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Provide alias names that some CMakeLists may expect
add_library(GTest::gtest ALIAS gtest)
add_library(GTest::gtest_main ALIAS gtest_main)
