cmake_minimum_required(VERSION 3.22)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2 main.cpp data_structures/DynamicArray.h exceptions/Exception.cpp exceptions/Exception.h data_structures/LinkedList.h sequences/Sequence.h sequences/ArraySequence.h)
