cmake_minimum_required(VERSION 3.24)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(
    lab1_test
    test.cpp
    smart_pointers/UniquePtr.hpp
    smart_pointers/SharedPtr.hpp
    sequences/SmartPtrSequence.hpp
    sequences/SmartPtrArraySequence.hpp
    sequences/SmartPtrLinkedListSequence.hpp
    tests/UniquePtr_tests/UniquePtr_tests.hpp
    tests/UniquePtr_tests/UniquePtr_tests.cpp
    tests/SharedPtr_tests/SharedPtr_tests.hpp
    tests/SharedPtr_tests/SharedPtr_tests.cpp
    tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.hpp
    tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.cpp
    tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.hpp
    tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.cpp
)

include(FindPkgConfig)

find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(lab1_test ${TEST-LIB_LIBRARY})

find_package(SequenceLib REQUIRED)
include_directories(${SEQUENCE-LIB_INCLUDE_DIR})
target_link_libraries(lab1_test ${SEQUENCE-LIB_LIBRARY})
