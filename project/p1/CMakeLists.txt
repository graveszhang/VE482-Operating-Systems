cmake_minimum_required(VERSION 3.16)
project(p1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

add_executable(p1 main.c read.c read.h parse.c parse.h execute.c execute.h redirect.c redirect.h)
