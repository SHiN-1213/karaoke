cmake_minimum_required(VERSION 3.26)

add_library(window STATIC
        window.cpp
        window.hpp
)

target_link_libraries(window PUBLIC
        opengl32
        glew32
        glfw3
        libglew32
        glu32
)