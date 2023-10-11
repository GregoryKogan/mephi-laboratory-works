set(FIND_EXCEPTION-LIB_PATHS
        ${PROJECT_SOURCE_DIR}/../../libraries/exception_lib)

find_path(EXCEPTION-LIB_INCLUDE_DIR exception_lib.hpp
        PATH_SUFFIXES include
        PATHS ${FIND_EXCEPTION-LIB_PATHS})

find_library(EXCEPTION-LIB_LIBRARY
        NAMES exception_lib
        PATH_SUFFIXES lib
        PATHS ${FIND_EXCEPTION-LIB_PATHS})