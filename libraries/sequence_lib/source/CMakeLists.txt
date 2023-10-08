cmake_minimum_required(VERSION 3.22)
project(sequence_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(
    sequence_lib STATIC 
    sequence_lib.cpp 
    sequence_lib.hpp 
    data_structures/DynamicArray.hpp 
    data_structures/LinkedList.hpp 
    sequences/Sequence.hpp 
    sequences/ArraySequence.hpp 
    sequences/LinkedListSequence.hpp 
    exceptions/BaseException.cpp 
    exceptions/BaseException.hpp 
    exceptions/IndexOutOfRangeException/IndexOutOfRangeException.cpp 
    exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp 
    exceptions/InvalidArgumentException/InvalidArgumentException.hpp 
    exceptions/InvalidArgumentException/InvalidArgumentException.cpp 
    exceptions/EmptyContainerException/EmptyContainerException.cpp 
    exceptions/EmptyContainerException/EmptyContainerException.hpp
)
