cmake_minimum_required(VERSION 0.0)
project(WS2040 C)

set(CMAKE_C_STANDARD 99)

link_directories(lib)
include_directories(lib)
add_executable(WS2040 main.c lib/ch9326.h)
target_link_libraries(WS2040 ch9326)