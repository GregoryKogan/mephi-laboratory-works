cmake_minimum_required(VERSION 3.25)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


add_executable(lab4_run run.cpp trees/nary_tree.hpp trees/serializers/nary_tree_serializer.hpp UI/menus.cpp UI/menus.hpp)
add_executable(lab4_test test.cpp trees/nary_tree.hpp tests/nary_tree/nary_tree_tests.cpp tests/nary_tree/nary_tree_tests.hpp trees/serializers/nary_tree_serializer.hpp)


include(FindPkgConfig)

find_package(SequenceLib REQUIRED)
include_directories(${SEQUENCE-LIB_INCLUDE_DIR})
target_link_libraries(lab4_run ${SEQUENCE-LIB_LIBRARY})
target_link_libraries(lab4_test ${SEQUENCE-LIB_LIBRARY})

find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(lab4_run ${TEST-LIB_LIBRARY})
target_link_libraries(lab4_test ${TEST-LIB_LIBRARY})

find_package(ContainerLib REQUIRED)
include_directories(${CONTAINER-LIB_INCLUDE_DIR})
target_link_libraries(lab4_run ${CONTAINER-LIB_LIBRARY})
target_link_libraries(lab4_test ${CONTAINER-LIB_LIBRARY})
