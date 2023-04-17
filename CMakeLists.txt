cmake_minimum_required(VERSION 3.24)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled3 main.cpp Internet.cpp Internet.h SFML/System.hpp SFML/Audio.hpp SFML/Config.hpp SFML/GpuPreference.hpp SFML/Graphics.hpp SFML/Main.hpp SFML/OpenGL.hpp SFML/Window.hpp
        file(GLOB SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}SFML/Window/*.hpp"))
