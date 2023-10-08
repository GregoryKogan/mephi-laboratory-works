cmake_minimum_required(VERSION 3.22)
project(test_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(
    test_lib STATIC 
    test_lib.cpp 
    test_lib.hpp 
    tests/Test.cpp 
    tests/Test.hpp 
    tests/Tester.cpp 
    tests/Tester.hpp
    tests/TestSuite.cpp 
    tests/TestSuite.hpp 
    IO/colored_logs.cpp 
    IO/colored_logs.hpp 
    exceptions/BaseException.cpp 
    exceptions/BaseException.hpp 
    exceptions/AssertionFailedException/AssertionFailedException.cpp 
    exceptions/AssertionFailedException/AssertionFailedException.hpp 
)
