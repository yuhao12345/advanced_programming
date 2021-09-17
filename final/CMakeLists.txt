cmake_minimum_required(VERSION 3.18)
project(final C)

set(CMAKE_C_STANDARD 99)

add_executable(final main.c heap.h heap.c encode_decode.c encode_decode.h)