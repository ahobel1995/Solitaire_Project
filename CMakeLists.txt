cmake_minimum_required(VERSION 3.26)
project(Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Project main.c
        solFunc.c
        gameLogic.c
        gameLogic.h)
