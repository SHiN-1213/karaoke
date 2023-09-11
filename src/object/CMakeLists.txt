cmake_minimum_required(VERSION 3.26)

add_library(object STATIC
        object.cpp
        object.hpp

        tex_planes.cpp
        tex_planes.hpp

        karaoke_line.cpp
        karaoke_line.hpp
)

target_link_libraries(object PUBLIC
        common

        opengl32
        glew32
        glfw3
        libglew32
        glu32
)