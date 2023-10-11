cmake_minimum_required(VERSION 3.22)
project(exception_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(
    exception_lib STATIC 
    exception_lib.cpp 
    exception_lib.hpp
    IO/colored_logs.cpp
    IO/colored_logs.hpp
    exceptions/BaseException.cpp 
    exceptions/BaseException.hpp 
    exceptions/AssertionFailedException/AssertionFailedException.cpp 
    exceptions/AssertionFailedException/AssertionFailedException.hpp
    exceptions/EmptyContainerException/EmptyContainerException.cpp
    exceptions/EmptyContainerException/EmptyContainerException.hpp
    exceptions/IndexOutOfRangeException/IndexOutOfRangeException.cpp
    exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp
    exceptions/InvalidArgumentException/InvalidArgumentException.cpp
    exceptions/InvalidArgumentException/InvalidArgumentException.hpp
)
