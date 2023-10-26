cmake_minimum_required(VERSION 3.26)

add_library(common STATIC
        audio_manager.cpp
        audio_manager.hpp
        file.cpp
        file.hpp
        image.cpp
        image.hpp
        gltf.cpp
        gltf.hpp
        fft_manager.cpp
        fft_manager.hpp
)