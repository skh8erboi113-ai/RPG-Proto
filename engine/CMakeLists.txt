cmake_minimum_required(VERSION 3.16)

set(ENGINE_SOURCES
    src/Camera.cpp
    src/CharacterController.cpp
    src/StatsManager.cpp
    src/SkillManager.cpp
    src/Inventory.cpp
    src/CraftingManager.cpp
    src/Mesh.cpp
    src/ShaderUtils.cpp
    src/Terrain.cpp
    src/Engine.cpp
    src/Renderer.cpp
    src/WorldStreamer.cpp
)

# Create the engine library
add_library(engine STATIC ${ENGINE_SOURCES})

# Public include directory
target_include_directories(engine PUBLIC include)
target_link_libraries(engine PUBLIC bgfx bx bimg nlohmann_json::nlohmann_json)

# Robust finding of GLFW
if(APPLE)
    # macOS specific robust search
    find_library(GLFW_LIB NAMES glfw glfw3 PATHS /usr/local/lib /opt/homebrew/lib)
    if(GLFW_LIB)
        target_link_libraries(engine PRIVATE ${GLFW_LIB})
        # Try to find headers too
        find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h PATHS /usr/local/include /opt/homebrew/include)
        if(GLFW_INCLUDE_DIR)
            target_include_directories(engine PRIVATE ${GLFW_INCLUDE_DIR})
        endif()
    else()
        target_link_libraries(engine PRIVATE glfw)
    endif()

    # macOS frameworks
    target_link_libraries(engine PRIVATE "-framework Cocoa" "-framework Metal" "-framework QuartzCore" "-framework IOKit" "-framework CoreFoundation" "-framework Foundation")

elseif(WIN32)
    # Windows robust search
    find_package(glfw3 CONFIG QUIET)
    if(glfw3_FOUND)
        if(TARGET glfw)
            target_link_libraries(engine PRIVATE glfw)
        else()
            target_link_libraries(engine PRIVATE glfw3)
        endif()
    else()
        find_package(GLFW QUIET)
        if(GLFW_FOUND)
            target_link_libraries(engine PRIVATE GLFW::GLFW)
        else()
            target_link_libraries(engine PRIVATE glfw)
        endif()
    endif()

else()
    # Linux / Others
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
    target_link_libraries(engine PRIVATE ${GLFW_LIBRARIES})
    target_include_directories(engine PRIVATE ${GLFW_INCLUDE_DIRS})

    find_package(Threads REQUIRED)
    target_link_libraries(engine PRIVATE Threads::Threads)

    find_package(X11 REQUIRED)
    target_link_libraries(engine PRIVATE ${X11_LIBRARIES})

    find_package(OpenGL REQUIRED)
    target_link_libraries(engine PRIVATE OpenGL::GL)
endif()
