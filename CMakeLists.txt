cmake_minimum_required(VERSION 3.0)
project(RubiksCube C)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 11)
include_directories(src)

add_executable(RubiksCube
        src/cube_main.c
        src/rotation.h
        src/rotation.c
        src/cube.h
        src/cube.c
        src/command.h
        src/input.h
        src/input.c)
