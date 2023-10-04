cmake_minimum_required(VERSION 3.24)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(
    lab1_run
    run.cpp
    smart_pointers/UniquePtr.hpp
)
add_executable(
    lab1_test
    test.cpp
    smart_pointers/UniquePtr.hpp
    tests/UniquePtr_tests/UniquePtr_tests.hpp
    tests/UniquePtr_tests/UniquePtr_tests.cpp
)

include(FindPkgConfig)

find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(lab1_test ${TEST-LIB_LIBRARY})
