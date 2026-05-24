cmake_minimum_required(VERSION 3.16)
project(tests)

# Find or add GoogleTest
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest EXCLUDE_FROM_ALL)
  set(GTEST_LIB gtest gtest_main)
else()
  set(GTEST_LIB GTest::gtest GTest::gtest_main)
endif()

enable_testing()

add_executable(test_stats
  test_stats.cpp
)

target_link_libraries(test_stats PRIVATE engine ${GTEST_LIB})
target_compile_features(test_stats PRIVATE cxx_std_17)

add_test(NAME StatsTests COMMAND test_stats)
