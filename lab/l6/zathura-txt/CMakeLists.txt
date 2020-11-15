cmake_minimum_required(VERSION 3.17)
project(l6)

set(CMAKE_CXX_STANDARD 14)

add_executable(l6 document.c index.c internal.h plugin.c plugin.h render.c utils.c utils.h page.c)