cmake_minimum_required(VERSION 3.16)

add_executable(test_stats test_stats.cpp)
target_link_libraries(test_stats PRIVATE engine GTest::gtest_main)
add_test(NAME EngineStats COMMAND test_stats)

add_executable(test_crafting test_crafting.cpp)
target_link_libraries(test_crafting PRIVATE engine GTest::gtest)
add_test(NAME EngineCrafting COMMAND test_crafting)

add_executable(test_save_system test_save_system.cpp)
target_link_libraries(test_save_system PRIVATE engine GTest::gtest)
add_test(NAME EngineSaveSystem COMMAND test_save_system)
