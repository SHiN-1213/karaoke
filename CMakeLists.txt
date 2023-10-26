cmake_minimum_required(VERSION 3.26)
project(opengl_learn)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(C:/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/include)
include_directories(C:/glm)
include_directories(C:/Program Files (x86) /Windows Kits/10/Include/10.0.22000.0/um)
include_directories(C:/glew-mingw/include)

link_directories(C:/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/lib-mingw-w64)
link_directories(C:/glew-mingw/lib)
link_directories(C:/glew-mingw/bin)
link_directories(dlls)

add_executable(opengl_learn src/main.cpp)

add_subdirectory(src/common)
add_subdirectory(src/window)
add_subdirectory(src/input)
add_subdirectory(src/shader)
add_subdirectory(src/texture)
add_subdirectory(src/scene)
add_subdirectory(src/object)
add_subdirectory(src/vertex)
add_subdirectory(src/camera)
add_subdirectory(src/karaoke)

target_link_libraries(opengl_learn
        common
        window
        input
        shader
        texture
        scene
        object
        vertex
        camera
        karaoke

        opengl32
        glew32
        glfw3
        libglew32
        glu32
        librtaudio
        libfftw3f
)