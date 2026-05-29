add_library(engine
    src/Camera.cpp
    src/Mesh.cpp
    src/ShaderUtils.cpp
    src/Terrain.cpp
)

target_include_directories(engine PUBLIC include)

# Link bgfx (this also links bx + bimg automatically)
target_link_libraries(engine PUBLIC bgfx)
