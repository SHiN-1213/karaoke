cmake_minimum_required(VERSION 3.26)

add_library(shader STATIC
        shader.cpp
        shader.hpp
)

target_link_libraries(shader PUBLIC
        common

        opengl32
        glew32
        glfw3
        libglew32
        glu32
)