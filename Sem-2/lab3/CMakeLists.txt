cmake_minimum_required(VERSION 3.24)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(lab3 main.cpp)

include(FindPkgConfig)
find_package(SequenceLib REQUIRED)
include_directories(${SEQUENCE-LIB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SEQUENCE-LIB_LIBRARY})
