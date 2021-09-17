cmake_minimum_required(VERSION 3.18)
project(homework_3_yuhao12345 C)

set(CMAKE_C_STANDARD 99)

add_executable(homework_3_yuhao12345 Barnes-Hut.c)

target_link_libraries(homework_3_yuhao12345 m)