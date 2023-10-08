#!/bin/bash

# This script recompiles all the libraries in the libraries folder.
# It is useful when you want to recompile all the libraries for a new operating system.

libraries_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$libraries_path"

# test_lib
rm -rf test_lib/lib; mkdir test_lib/lib
cd test_lib/source
cmake . && make
mv libtest_lib.a ../lib
cd "$libraries_path"

# sequence_lib
rm -rf sequence_lib/lib; mkdir sequence_lib/lib
cd sequence_lib/source
cmake . && make
mv libsequence_lib.a ../lib
cd "$libraries_path"

# container_lib
rm -rf container_lib/lib; mkdir container_lib/lib
cd container_lib/source
cmake . && make
mv libcontainer_lib.a ../lib
cd "$libraries_path"
