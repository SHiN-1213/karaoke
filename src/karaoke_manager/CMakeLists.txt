cmake_minimum_required(VERSION 3.26)

add_library(karaoke_manager STATIC
        karaoke_manager.cpp
        karaoke_manager.hpp
)

target_link_libraries(karaoke_manager PUBLIC
        object

        opengl32
        glew32
        glfw3
        libglew32
        glu32
)