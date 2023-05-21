set(FIND_CONTAINER-LIB_PATHS
        ${PROJECT_SOURCE_DIR}/../../libraries/container_lib)

find_path(CONTAINER-LIB_INCLUDE_DIR container_lib.hpp
        PATH_SUFFIXES include
        PATHS ${FIND_CONTAINER-LIB_PATHS})

find_library(CONTAINER-LIB_LIBRARY
        NAMES container_lib
        PATH_SUFFIXES lib
        PATHS ${FIND_CONTAINER-LIB_PATHS})