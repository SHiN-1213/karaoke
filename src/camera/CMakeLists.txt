cmake_minimum_required(VERSION 3.26)

add_library(camera STATIC
        camera.cpp
        camera.hpp
)

target_link_libraries(camera PUBLIC
        opengl32
        glew32
        glfw3
        libglew32
        glu32
)