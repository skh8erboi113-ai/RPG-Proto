cmake_minimum_required(VERSION 3.20)

if(NOT RPG_BUILD_TESTS)
  return()
endif()

add_executable(test_stats test_stats.cpp)
target_link_libraries(test_stats PRIVATE engine GTest::gtest GTest::gtest_main)

target_compile_options(test_stats PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
)

add_test(NAME EngineTests COMMAND test_stats)

set_target_properties(test_stats PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
)
