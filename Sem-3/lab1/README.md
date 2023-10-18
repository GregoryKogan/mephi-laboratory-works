# Smart pointers implementation

## Description
This project contains implementation of smart pointers and benchmark of them.

## Dependencies
To install web interface dependencies run the following command:
```bash
./interface/backend/install_dependencies.sh
```
Make sure you have compiled static libraries in `mephi-laboratory-works/libraries` directory by running the compile script from repository root:
```bash
./libraries/compile_all.sh
```

## Build
To build this project you need to have `cmake` installed. Then you need to run the following commands:
```bash
mkdir build
cd build
cmake ..
make
```

## Run
Inside `build` there will be 3 executables:
- `test` - runs tests
- `benchmark` - runs benchmark
- `run` - runs web interface

## Benchmark results
<p align="center">
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/4624195b675eee2e7a679e6b60ea78b1c3fb8c00/Sem-3/lab1/load_testing_results/std%20qsort%20array%20of%20pointers%20relative%20execution%20time.png" />
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/4624195b675eee2e7a679e6b60ea78b1c3fb8c00/Sem-3/lab1/load_testing_results/std%20qsort%20array%20of%20pointers%20execution%20time%20(microseconds).png" />
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/4624195b675eee2e7a679e6b60ea78b1c3fb8c00/Sem-3/lab1/load_testing_results/array%20of%20pointers%20relative%20memory%20consumption.png" />
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/4624195b675eee2e7a679e6b60ea78b1c3fb8c00/Sem-3/lab1/load_testing_results/array%20of%20pointers%20memory%20consumption%20(KiB).png" />
</p>
