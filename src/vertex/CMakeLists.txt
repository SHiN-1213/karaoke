cmake_minimum_required(VERSION 3.26)

add_library(vertex STATIC
        vertex.cpp
        vertex.hpp
)

target_link_libraries(vertex PUBLIC
        opengl32
        glew32
        glfw3
        libglew32
        glu32
)