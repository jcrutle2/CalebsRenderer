cmake_minimum_required(VERSION 3.26)
project(CalebsRenderer)

enable_language(OBJCXX)
enable_language(OBJC)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/sdl2 include/GL include/glm include/glm/gtc include/stb-master include/assimp include/imgui include)
include_directories(SYSTEM include/boostGlob)

find_library(sdl SDL2 libSDL2.dylib)
find_library(gl GLEW libGLEW.dylib)
find_library(as assimp libassimp.dylib)
find_package(Boost 1.79.0 COMPONENTS system filesystem serialization REQUIRED)

file(GLOB IMGUI_FILES include/imgui/*.cpp include/imgui/imgui_impl_osx.mm)
add_library(imgui ${IMGUI_FILES})

add_executable(
        CalebsRenderer
        src/Editor/EditorMain.cpp
        src/Editor/EditorControls.cpp
        src/Geometry/Models/Shader.cpp
        src/Rendering/Camera.cpp
        src/Editor/EditorWindow.cpp
        src/Geometry/Models/Mesh.cpp
        src/Geometry/Models/Model.cpp
        src/Environment/Light/Light.cpp
        src/UI/UI.cpp
        src/Scene/Scene.cpp
        src/UI/UIGlobals.cpp
        src/UI/UIWindows.cpp
        src/UI/UIUtil.cpp
        src/Environment/Skybox/Skybox.cpp
        src/Geometry/LevelGeometry/Tile.cpp
        src/Geometry/LevelGeometry/TileTypes/SquareTile.cpp
        src/Geometry/LevelGeometry/TileWrapper.cpp
)

target_link_libraries(CalebsRenderer "-framework QuartzCore -framework GameController -framework Cocoa -framework OpenGL" ${sdl} ${gl} ${as} imgui)





