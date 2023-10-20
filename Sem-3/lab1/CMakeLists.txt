cmake_minimum_required(VERSION 3.24)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(
    test
    test.cpp

    exceptions/EmptyPointerException/EmptyPointerException.hpp
    exceptions/EmptyPointerException/EmptyPointerException.cpp
    exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp
    exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.cpp

    smart_pointers/UniquePtr/UniquePtr.hpp
    smart_pointers/UniquePtr/UniquePtr.hh
    smart_pointers/ControlBlock/ControlBlock.hpp
    smart_pointers/ControlBlock/ControlBlock.hh
    smart_pointers/SharedPtr/SharedPtr.hpp
    smart_pointers/SharedPtr/SharedPtr.hh
    smart_pointers/WeakPtr/WeakPtr.hpp
    smart_pointers/WeakPtr/WeakPtr.hh

    data_structures/SmartPtrDynamicArray/SmartPtrDynamicArray.hpp
    data_structures/SmartPtrDynamicArray/SmartPtrDynamicArray.hh
    data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hpp
    data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hh

    sequences/SmartPtrSequence.hpp
    sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp
    sequences/SmartPtrArraySequence/SmartPtrArraySequence.hh
    sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp
    sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hh

    tests/UniquePtr_tests/UniquePtr_tests.hpp
    tests/UniquePtr_tests/UniquePtr_tests.cpp
    tests/SharedPtr_tests/SharedPtr_tests.hpp
    tests/SharedPtr_tests/SharedPtr_tests.cpp
    tests/WeakPtr_tests/WeakPtr_tests.hpp
    tests/WeakPtr_tests/WeakPtr_tests.cpp

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
    benchmark
    benchmark.cpp

    exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp
    exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.cpp
    
    smart_pointers/UniquePtr/UniquePtr.hpp
    smart_pointers/UniquePtr/UniquePtr.hh
    smart_pointers/SharedPtr/SharedPtr.hpp
    smart_pointers/SharedPtr/SharedPtr.hh
)

add_executable(
    run
    interface/backend/run.cpp

    interface/backend/dependencies/cpp-httplib/httplib.h

    interface/backend/Logger/Logger.hpp
    interface/backend/Logger/Logger.cpp

    interface/backend/State/State.hpp
    interface/backend/State/State.cpp

    interface/backend/routes/ping/set_ping_routes.hpp
    interface/backend/routes/ping/set_ping_routes.cpp
    interface/backend/routes/ping/endpoints/endpoints.hpp
    interface/backend/routes/ping/endpoints/endpoints.cpp

    interface/backend/routes/records/set_records_routes.hpp
    interface/backend/routes/records/set_records_routes.cpp
    interface/backend/routes/records/endpoints/endpoints.hpp
    interface/backend/routes/records/endpoints/endpoints.cpp

    exceptions/EmptyPointerException/EmptyPointerException.hpp
    exceptions/EmptyPointerException/EmptyPointerException.cpp
    exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp
    exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.cpp
    sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp
    sequences/SmartPtrArraySequence/SmartPtrArraySequence.hh
    sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp
    sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hh
)

include(FindPkgConfig)

find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(test ${TEST-LIB_LIBRARY})

find_package(ExceptionLib REQUIRED)
include_directories(${EXCEPTION-LIB_INCLUDE_DIR})
target_link_libraries(test ${EXCEPTION-LIB_LIBRARY})
target_link_libraries(benchmark ${EXCEPTION-LIB_LIBRARY})
target_link_libraries(run ${EXCEPTION-LIB_LIBRARY})
