cmake_minimum_required(VERSION 3.24)
project(container_lib)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_library(
    container_lib STATIC 
    container_lib.cpp 
    container_lib.hpp 
    containers/queue/queue.hpp 
    containers/stack/stack.hpp 
    containers/deque/deque.hpp 
    containers/base_container.hpp
    containers/i_enumerable.hpp 
    containers/i_enumerator.hpp
)

include(FindPkgConfig)

find_package(SequenceLib REQUIRED)
include_directories(${SEQUENCE-LIB_INCLUDE_DIR})

find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
