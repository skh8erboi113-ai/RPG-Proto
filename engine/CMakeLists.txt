cmake_minimum_required(VERSION 3.16)

set(ENGINE_SOURCES
    src/Camera.cpp
    src/CharacterController.cpp
    src/StatsManager.cpp
    src/SkillManager.cpp
    src/Inventory.cpp
    src/CraftingManager.cpp
    src/WantedManager.cpp
    src/Mesh.cpp
    src/ShaderUtils.cpp
    src/Terrain.cpp
    src/Engine.cpp
    src/Renderer.cpp
    src/WorldStreamer.cpp
)

add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC include)

# Link dependencies
target_link_libraries(engine PUBLIC bgfx bx bimg nlohmann_json::nlohmann_json glfw)

# Platform-specific dependencies
if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(engine PRIVATE Threads::Threads)
    if(APPLE)
        target_link_libraries(engine PRIVATE "-framework Cocoa" "-framework Metal" "-framework QuartzCore" "-framework IOKit" "-framework CoreFoundation" "-framework Foundation")
    else()
        # Linux
        find_package(X11 REQUIRED)
        target_link_libraries(engine PRIVATE ${X11_LIBRARIES})
        find_package(OpenGL REQUIRED)
        target_link_libraries(engine PRIVATE OpenGL::GL)
    endif()
endif()
