# Smart pointers

## Description
This project contains implementation of unique, shared and weak smart pointers, implementation of dynamic array and linked list data strcutures built with them and abstract sequence system built upon these data strcutures. There are also tests for everything, benchmark for smart pointers and web interface for sequences.

## Dependencies

### Backend
Backend is built with [cpp-httplib](https://github.com/yhirose/cpp-httplib).
To install web interface backend dependencies run the following command:
```bash
./interface/backend/install_dependencies.sh
```
Make sure you have compiled static libraries in `mephi-laboratory-works/libraries` directory by running the compile script from **repository root**:
```bash
./libraries/compile_all.sh
```

### Frontend
Web interface frontend is build with [Vue.js](https://vuejs.org/), [Vite](https://vitejs.dev/) and [Vuetify](https://vuetifyjs.com/).
Vite requires Node.js version 14.18+, 16+. However, some templates require a higher Node.js version to work, please upgrade if your package manager warns about it.

**WARNING**: Vite does not support Node.js 21 yet. If you are using Node.js 21, please downgrade to Node.js 20.

You can use any Node.js package manager: `yarn`/`npm`/`pnpm`/`bun`, but only compatibility with `yarn` and `npm` was tested. The project was developed using `yarn`. Therefore, it is recommended to use `yarn`.
To install frontend dependencies `cd` into `interface/frontend` directory and run:
```bash
# yarn
yarn

# npm
npm install

# pnpm
pnpm install

# bun 
bun install
```
Don't forget to return to the **project root** directory after installing frontend dependencies.

## Build

### Backend
To build this project and web interface backend you need to have `cmake` installed. Then you need to run the following commands:
```bash
mkdir build
cd build
cmake ..
make
```

### Frontend
To build frontend `cd` into `interface/frontend` directory and run:
```bash
# yarn
yarn build

# npm
npm run build

# pnpm
pnpm build

# bun 
bun run build
```
Don't forget to return to the **project root** directory after building frontend.

## Run

### Backend
Inside `build` directory there will be 3 executables:
- `test` - runs tests
- `benchmark` - runs benchmark
- `run` - runs web interface backend

### Frontend
To run web interface frontend `cd` into `interface/frontend` directory and run:
```bash
# yarn
yarn preview

# npm
npm run preview

# pnpm
pnpm preview

# bun
bun run preview
```

Notice that for web interface to work you need to run web interface backend and frontend simultaneously.

## Web interface screenshots
<img width="395" alt="image" src="https://github.com/GregoryKogan/mephi-laboratory-works/assets/60318411/0f56f3b5-db0a-4a5a-bd1e-a33cdd308ba3">
<img width="395" alt="image" src="https://github.com/GregoryKogan/mephi-laboratory-works/assets/60318411/408f963f-7646-487a-9333-839ae22bdf35">

## Benchmark results

All benchmark results are located in `benchmark_results` directory.

In all benchmarks `std::qsort` was used to sort array of pointers to test objects. Array's size was increased by 10 times in each iteration.

- Execution time was measured using `std::chrono::high_resolution_clock` and averaged over 5 runs. 
- Memory consumption was measured using `valgrind --tool=massif`

Execution time benchmark results were obtained on M1 Pro 14-inch MacBook Pro (2021) with 16GB RAM, running macOS Sonoma 14.0

Memory consumption benchmark results were obtained on Lenovo Yoga X1 (2017) with Intel i7-8565U (8) @ 4.600GHz and 16GB RAM, running Fedora Linux 38 (Server Edition) x86_64

### Execution time benchmark results:
```
size: 10^1
raw pointers:           0μs
kogan's smart pointers: 0μs
std smart pointers:     0μs
size: 10^2
raw pointers:           5μs
kogan's smart pointers: 6μs
std smart pointers:     7μs
size: 10^3
raw pointers:           80μs
kogan's smart pointers: 89μs
std smart pointers:     112μs
size: 10^4
raw pointers:           993μs
kogan's smart pointers: 1252μs
std smart pointers:     1516μs
size: 10^5
raw pointers:           12596μs
kogan's smart pointers: 15582μs
std smart pointers:     19680μs
size: 10^6
raw pointers:           162038μs
kogan's smart pointers: 199379μs
std smart pointers:     254150μs
size: 10^7
raw pointers:           2302036μs
kogan's smart pointers: 3070649μs
std smart pointers:     4041950μs
size: 10^8
raw pointers:           31592781μs
kogan's smart pointers: 43441582μs
std smart pointers:     59107903μs
```

<p align="center">
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/2e684778d8bbc0badb12f8bdefd27acfc5f67571/Sem-3/lab1/benchmark_results/std%20qsort%20array%20of%20pointers%20relative%20execution%20time.png" />
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/2e684778d8bbc0badb12f8bdefd27acfc5f67571/Sem-3/lab1/benchmark_results/std%20qsort%20array%20of%20pointers%20execution%20time%20(microseconds).png" />
</p>

### Memory consumption benchmark results:
```
size: 10^1
raw pointers:           75.01KiB
kogan's smart pointers: 74.93KiB
std smart pointers:     75.80KiB
size: 10^2
raw pointers:           78.33KiB
kogan's smart pointers: 78.77KiB
std smart pointers:     78.72KiB
size: 10^3
raw pointers:           114.1KiB
kogan's smart pointers: 114.3KiB
std smart pointers:     114.5KiB
size: 10^4
raw pointers:           466.0KiB
kogan's smart pointers: 466.1KiB
std smart pointers:     466.3KiB
size: 10^5
raw pointers:           3982.34KiB
kogan's smart pointers: 3982.34KiB
std smart pointers:     3982.34KiB
size: 10^6
raw pointers:           39147.52KiB
kogan's smart pointers: 39147.52KiB
std smart pointers:     39147.52KiB
size: 10^7
raw pointers:           390758.4KiB
kogan's smart pointers: 390758.4KiB
std smart pointers:     390758.4KiB
```

<p>
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/2e684778d8bbc0badb12f8bdefd27acfc5f67571/Sem-3/lab1/benchmark_results/array%20of%20pointers%20relative%20memory%20consumption.png" />
  <img style="width: 100%;" src="https://github.com/GregoryKogan/mephi-laboratory-works/blob/2e684778d8bbc0badb12f8bdefd27acfc5f67571/Sem-3/lab1/benchmark_results/array%20of%20pointers%20memory%20consumption%20(KiB).png" />
</p>
