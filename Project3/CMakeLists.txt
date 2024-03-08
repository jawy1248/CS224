cmake_minimum_required(VERSION 3.27)
project(Project3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project3
        utils.c
        y86-64.c)
