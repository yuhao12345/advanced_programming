cmake_minimum_required(VERSION 3.17)
project(homework_1_yuhao12345)

set(CMAKE_C_STANDARD 99)

add_executable(homework_1_yuhao12345 test_list2.c list.c)

target_link_libraries(homework_1_yuhao12345 m)