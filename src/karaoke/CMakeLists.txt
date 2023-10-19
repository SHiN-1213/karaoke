cmake_minimum_required(VERSION 3.26)

add_library(karaoke STATIC
        karaoke.cpp
        karaoke.hpp
)

target_link_libraries(karaoke PUBLIC
        object

        opengl32
        glew32
        glfw3
        libglew32
        glu32
)