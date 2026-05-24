cmake_minimum_required(VERSION 3.16)
project(ModernGothicRPG VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_SERVER "Build server binary" ON)
option(BUILD_CLIENT "Build client binary" ON)
option(BUILD_TESTS "Build unit tests" ON)

# Third party paths (adjust as needed)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

# Add nlohmann_json if available via package manager
find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
  add_subdirectory(${THIRD_PARTY_DIR}/nlohmann_json EXCLUDE_FROM_ALL)
endif()

# Add GoogleTest for unit tests if requested
if(BUILD_TESTS)
  find_package(GTest QUIET)
  if(NOT GTest_FOUND)
    add_subdirectory(${THIRD_PARTY_DIR}/googletest EXCLUDE_FROM_ALL)
  endif()
endif()

# Engine and game modules
add_subdirectory(engine)
add_subdirectory(game)

# Tests
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
