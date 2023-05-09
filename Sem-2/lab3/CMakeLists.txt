cmake_minimum_required(VERSION 3.24)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(lab3_run run.cpp)
add_executable(lab3_test test.cpp)

include(FindPkgConfig)
find_package(SequenceLib REQUIRED)
include_directories(${SEQUENCE-LIB_INCLUDE_DIR})
target_link_libraries(lab3_run ${SEQUENCE-LIB_LIBRARY})

include(FindPkgConfig)
find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(lab3_test ${TEST-LIB_LIBRARY})
