cmake_minimum_required(VERSION 3.16)
project(RubiksCube C)

set(CMAKE_C_STANDARD 11)

add_executable(RubiksCube
        src/cube_main.c
        src/rotation.h
        src/rotation.c
        src/cube.h
        src/cube.c
        src/command.h)
