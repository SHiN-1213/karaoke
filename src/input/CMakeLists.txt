cmake_minimum_required(VERSION 3.26)

add_library(input STATIC
        input.cpp
        input.hpp
)

target_link_libraries(input PUBLIC
        opengl32
        glew32
        glfw3
        libglew32
        glu32
)