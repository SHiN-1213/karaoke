cmake_minimum_required(VERSION 3.26)

add_library(object STATIC
        interface/object.cpp
        interface/object.hpp

        interface/transform.cpp
        interface/transform.hpp

        basic/plane.cpp
        basic/plane.hpp

        basic/tex_planes.cpp
        basic/tex_planes.hpp

        karaoke/karaoke_line.cpp
        karaoke/karaoke_line.hpp
)

target_link_libraries(object PUBLIC
        common

        opengl32
        glew32
        glfw3
        libglew32
        glu32
)