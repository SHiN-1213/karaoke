cmake_minimum_required(VERSION 3.26)

add_library(scene STATIC
        scene.cpp
        scene.hpp
)

target_link_libraries(scene PUBLIC
        common

        opengl32
        glew32
        glfw3
        libglew32
        glu32
)