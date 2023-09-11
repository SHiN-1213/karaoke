cmake_minimum_required(VERSION 3.26)

add_library(texture STATIC
        texture.cpp
        texture.hpp
)

target_link_libraries(texture PUBLIC
        opengl32
        glew32
        glfw3
        libglew32
        glu32
)