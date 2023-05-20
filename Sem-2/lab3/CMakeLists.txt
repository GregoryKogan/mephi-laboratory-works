cmake_minimum_required(VERSION 3.24)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(lab3_run run.cpp containers/queue/queue.hpp containers/stack/stack.hpp containers/deque/deque.hpp containers/base_container.hpp persons/person.cpp persons/person.hpp containers/i_enumerable.hpp containers/i_enumerator.hpp UI/menus.cpp UI/menus.hpp)
add_executable(lab3_test test.cpp containers/queue/queue.hpp tests/queue/queue_tests.cpp tests/queue/queue_tests.hpp containers/stack/stack.hpp tests/stack/stack_tests.cpp tests/stack/stack_tests.hpp containers/deque/deque.hpp tests/deque/deque_tests.cpp tests/deque/deque_tests.hpp containers/base_container.hpp persons/person.cpp persons/person.hpp tests/person/person_tests.cpp tests/person/person_tests.hpp containers/i_enumerable.hpp containers/i_enumerator.hpp tests/base_container/base_container_tests.cpp tests/base_container/base_container_tests.hpp)

include(FindPkgConfig)
find_package(SequenceLib REQUIRED)
include_directories(${SEQUENCE-LIB_INCLUDE_DIR})
target_link_libraries(lab3_run ${SEQUENCE-LIB_LIBRARY})
target_link_libraries(lab3_test ${SEQUENCE-LIB_LIBRARY})

include(FindPkgConfig)
find_package(TestLib REQUIRED)
include_directories(${TEST-LIB_INCLUDE_DIR})
target_link_libraries(lab3_run ${TEST-LIB_LIBRARY})
target_link_libraries(lab3_test ${TEST-LIB_LIBRARY})
