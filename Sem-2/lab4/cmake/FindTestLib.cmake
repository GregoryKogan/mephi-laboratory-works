set(FIND_TEST-LIB_PATHS
        ${PROJECT_SOURCE_DIR}/../../libraries/test_lib)

find_path(TEST-LIB_INCLUDE_DIR test_lib.hpp
        PATH_SUFFIXES include
        PATHS ${FIND_TEST-LIB_PATHS})

find_library(TEST-LIB_LIBRARY
        NAMES test_lib
        PATH_SUFFIXES lib
        PATHS ${FIND_TEST-LIB_PATHS})