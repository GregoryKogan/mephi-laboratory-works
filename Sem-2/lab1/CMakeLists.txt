cmake_minimum_required(VERSION 3.22)
project(lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(lab1 main.c libs/type.c libs/matrix.c libs/types/int_type.c libs/IO/logger.c libs/types/float_type.c libs/types/float_type.h)
add_executable(lab1_test run_tests.c tests/matrix/matrix_tests.c tests/matrix/matrix_tests.h tests/test.c tests/test.h libs/IO/logger.c libs/IO/logger.h libs/type.c libs/matrix.c libs/types/int_type.c libs/types/float_type.c libs/types/float_type.h)