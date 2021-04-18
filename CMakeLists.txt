cmake_minimum_required(VERSION 3.7)
project(WH2040 C)

set(CMAKE_C_STANDARD 99)

link_directories(lib)
include_directories(lib)
add_executable(WH2040 main.c lib/ch9326.h)
target_link_libraries(WH2040 ch9326)
