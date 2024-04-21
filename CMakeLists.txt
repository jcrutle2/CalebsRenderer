cmake_minimum_required(VERSION 3.26)
project(CalebsRenderer)

enable_language(OBJCXX)
enable_language(OBJC)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/sdl2 include/GL include/glm include/glm/gtc include/stb-master include/assimp include/imgui include)

find_library(sdl SDL2 libSDL2.dylib)
find_library(gl GLEW libGLEW.dylib)
find_library(as assimp libassimp.dylib)

file(GLOB IMGUI_FILES include/imgui/*.cpp include/imgui/imgui_impl_osx.mm)
add_library(imgui ${IMGUI_FILES})

add_executable(
        Editor
        src/Editor/EditorMain.cpp
        src/Editor/Editor.cpp

        src/Rendering/Renderer.cpp
        src/Rendering/Camera.cpp

        src/Geometry/Models/Shader.cpp
        src/Geometry/Models/Mesh.cpp
        src/Geometry/Models/Model.cpp
        src/Scene/Scene.cpp

        src/Environment/Light/Light.cpp
        src/Environment/Skybox/Skybox.cpp

        src/UI/UI.cpp
        src/UI/UIGlobals.cpp
        src/UI/UIUtil.cpp
        src/UI/Windows/MainWindow.cpp
        src/UI/Windows/ModelWindow.cpp
        src/UI/Windows/BoxWindow.cpp
        src/UI/Windows/LightWindow.cpp
        src/UI/Windows/SkyboxWindow.cpp
        src/UI/Windows/SceneWindow.cpp

        src/Geometry/LevelGeometry/TileTypes/Tile.cpp
        src/Geometry/LevelGeometry/TileTypes/SquareTile.cpp
        src/Geometry/LevelGeometry/TileWrapper.cpp
        src/Geometry/LevelGeometry/Box/Box.cpp
        src/Geometry/LevelGeometry/Box/BoxAccess.cpp

        src/Geometry/Textures/Texture.cpp
        src/Geometry/Textures/TextureUtil.cpp

        src/Entities/Entity.cpp
        src/Entities/Hitbox.cpp
        src/Game/Game.cpp
        src/Entities/Player.cpp
        src/Physics/CollisionDetector.cpp
        src/Physics/Physics.h
        src/Physics/Physics.cpp
        "src/UI/Windows/LightMacros.h"
)

add_executable(
        Game
        src/Game/GameMain.cpp

        src/Geometry/Models/Shader.cpp
        src/Geometry/Models/Mesh.cpp
        src/Geometry/Models/Model.cpp
        src/Scene/Scene.cpp

        src/Rendering/Renderer.cpp
        src/Rendering/Camera.cpp

        src/Environment/Light/Light.cpp
        src/Environment/Skybox/Skybox.cpp

        src/UI/UI.cpp
        src/UI/UIGlobals.cpp
        src/UI/UIUtil.cpp
        src/UI/Windows/MainWindow.cpp
        src/UI/Windows/ModelWindow.cpp
        src/UI/Windows/BoxWindow.cpp
        src/UI/Windows/LightWindow.cpp
        src/UI/Windows/SkyboxWindow.cpp
        src/UI/Windows/SceneWindow.cpp

        src/Geometry/LevelGeometry/TileTypes/Tile.cpp
        src/Geometry/LevelGeometry/TileTypes/SquareTile.cpp
        src/Geometry/LevelGeometry/TileWrapper.cpp
        src/Geometry/LevelGeometry/Box/Box.cpp
        src/Geometry/LevelGeometry/Box/BoxAccess.cpp

        src/Geometry/Textures/Texture.cpp
        src/Geometry/Textures/TextureUtil.cpp

        src/Entities/Entity.cpp
        src/Entities/Hitbox.cpp
        src/Game/Game.cpp
        src/Entities/Player.cpp
        src/Physics/CollisionDetector.cpp
        src/Physics/Physics.h
        src/Physics/Physics.cpp
)

target_link_libraries(Editor "-framework QuartzCore -framework GameController -framework Cocoa -framework OpenGL" ${sdl} ${gl} ${as} imgui)
target_link_libraries(Game "-framework QuartzCore -framework GameController -framework Cocoa -framework OpenGL" ${sdl} ${gl} ${as} imgui)





