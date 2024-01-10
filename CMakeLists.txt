cmake_minimum_required(VERSION 3.26)
project(opengl_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/sdl2 include/GL include/SFML include/glm include/glm/gtc include/stb-master include/assimp include)

add_library(sdl2 SHARED IMPORTED)
add_library(GL SHARED IMPORTED)
add_library(SMFL-graphics SHARED IMPORTED)
add_library(SMFL-system SHARED IMPORTED)
add_library(SMFL-window SHARED IMPORTED)
add_library(assimp SHARED IMPORTED)

SET_PROPERTY(TARGET sdl2 PROPERTY IMPORTED_LOCATION /Users/calebrutledge/CLionProjects/opengl_tests/lib/sdl2/libSDL2.dylib)
SET_PROPERTY(TARGET GL PROPERTY IMPORTED_LOCATION /Users/calebrutledge/CLionProjects/opengl_tests/lib/glew/lib/libGLEW.2.2.0.dylib)
SET_PROPERTY(TARGET SMFL-graphics PROPERTY IMPORTED_LOCATION /Users/calebrutledge/CLionProjects/opengl_tests/lib/smfl/libsfml-graphics.2.6.1.dylib)
SET_PROPERTY(TARGET SMFL-system PROPERTY IMPORTED_LOCATION /Users/calebrutledge/CLionProjects/opengl_tests/lib/smfl/libsfml-system.2.6.1.dylib)
SET_PROPERTY(TARGET SMFL-window PROPERTY IMPORTED_LOCATION /Users/calebrutledge/CLionProjects/opengl_tests/lib/smfl/libsfml-window.2.6.1.dylib)
SET_PROPERTY(TARGET assimp PROPERTY IMPORTED_LOCATION /Users/calebrutledge/CLionProjects/opengl_tests/lib/assimp/libassimp.5.3.0.dylib)

add_executable(opengl_tests
                src/main.cpp
        src/MainGame.cpp
        src/Shader.cpp
        src/Camera.cpp
        src/OpenGLWindow.cpp
        src/Mesh.cpp
        src/Model.cpp
)

target_link_libraries(opengl_tests "-framework OpenGL" sdl2 GL SMFL-graphics SMFL-system SMFL-window assimp)





