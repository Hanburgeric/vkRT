cmake_minimum_required(VERSION 3.25)
project(vkRT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(
    vkRT
    src/main.cpp
    src/Core/Application.cpp
    src/Core/Application.h
)
