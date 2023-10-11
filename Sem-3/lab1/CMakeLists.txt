cmake_minimum_required(VERSION 3.24)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(
    test
    test.cpp
    smart_pointers/UniquePtr.hpp
    smart_pointers/SharedPtr.hpp
    data_structures/SmartPtrDynamicArray.hpp
    data_structures/SmartPtrLinkedList.hpp
    sequences/SmartPtrSequence.hpp
    sequences/SmartPtrArraySequence.hpp
    sequences/SmartPtrLinkedListSequence.hpp
    tests/UniquePtr_tests/UniquePtr_tests.hpp
    tests/UniquePtr_tests/UniquePtr_tests.cpp
    tests/SharedPtr_tests/SharedPtr_tests.hpp
    tests/SharedPtr_tests/SharedPtr_tests.cpp
    tests/SmartPtrDynamicArray_tests/SmartPtrDynamicArray_tests.hpp
    tests/SmartPtrDynamicArray_tests/SmartPtrDynamicArray_tests.cpp
    tests/SmartPtrLinkedList_tests/SmartPtrLinkedList_tests.hpp
    tests/SmartPtrLinkedList_tests/SmartPtrLinkedList_tests.cpp
    tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.hpp
    tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.cpp
    tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.hpp
    tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.cpp
)

add_executable(
    load_test
    load_test.cpp
    smart_pointers/UniquePtr.hpp
    smart_pointers/SharedPtr.hpp
)

include(FindPkgConfig)

find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(test ${TEST-LIB_LIBRARY})

find_package(ExceptionLib REQUIRED)
include_directories(${EXCEPTION-LIB_INCLUDE_DIR})
target_link_libraries(test ${EXCEPTION-LIB_LIBRARY})
