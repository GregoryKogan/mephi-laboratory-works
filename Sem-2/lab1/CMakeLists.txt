cmake_minimum_required(VERSION 3.24)
project(lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab1 main.c libs/type.c libs/matrix.c libs/types/int_type.c libs/IO/logger.c)
