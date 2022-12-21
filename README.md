# cFloydWarshallParallel

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/206360390-76940955-0a28-43b5-83fb-46409c4324f7.png" alt="openclLogo" style="height:60px;"/>
</p>

## Description

This is a parallel implementation of the Floyd-Warshall algorithm using OpenCL.

The algorithm is implemented in C and the OpenCL kernel is written in OpenCL C. The program is compiled using CMake.

- [x] Sequential implementation
- [x] Parallel implementation using OpenCL

Available for Linux, macOS and Windows.

## Dependencies

- C17 compiler
- CMake
- Makefile
- OpenCL

## Table of Contents

- [Description](#description)
- [Dependencies](#Dependencies)
- [Table of Contents](#table-of-contents)
- [Quickstart](#Quick-start)
- [Algorithm](#Algorithm)
    - [Sequential algorithm](#Sequential-algorithm)
    - [Parallel OpenCL algorithm](#Parallel-OpenCL-algorithm)
- [Results](#Results)
- [Compilation](#Compilation)
    - [Compilation set up](#Compilation-set-up)
    - [Makefile build](#Makefile-build)
    - [CMake build](#CMake-build)
- [How to use](#How-to-use)
- [Project Architecture](#Project-Architecture)
- [GitHub Actions](#GitHub-Actions)
- [Documentations](#Documentation)
- [Contributors](#Contributors)

## Quick start

The project can be compiled using the Makefile or CMake, please refer to the [Compilation](#Compilation) section for
more details.

You can find details about the algorithms and the results in the [Algorithms](#Algorithms) and [Results](#Results)
sections.

> **Note**  
> The builed project is an exemple of the Floyd-Warshall algorithm.
> If you want to use it in your program, you can find the functions in the [wfiOpenCl.h](wfiOpenCl/wfiOpenCl.h)
> and [wfiOpenCl.c](wfiOpenCl/wfiOpenCl.c) file. You can find more details about its use in
> the [How to use](#How-to-use) section.

> **Note**  
> A version of the Floyd-Warshall Parallel version also exist in the [oneFileVer/main.c](oneFileVer/main.c), 
> It is exactly the same code but in a single file (for more readability).

> **Warning**  
> Be sure to set the working directory of your projet to the root. To correctely load the `program.cl` or simply change the path in your code.

## Algorithm

The Floyd-Warshall algorithm is an algorithm for finding the shortest paths between all pairs of vertices in a weighted
graph. The algorithm is based on the idea of dynamic programming. The algorithm is implemented in a parallel way using
OpenCL.

### Sequential algorithm

```algorithm
for k from 1 to n
    for i from 1 to n
        for j from 1 to n
            if dist[i][j] > dist[i][k] + dist[k][j]
                dist[i][j] = dist[i][k] + dist[k][j]
```

### Parallel OpenCL algorithm

```algorithm
for k from 1 to n
    All threads in the work group with i = get_global_id(0) and j = get_global_id(1)
        if dist[i][j] > dist[i][k] + dist[k][j]
        dist[i][j] = dist[i][k] + dist[k][j]
```

## Results

The results of the programs are shown in the following table:

| Number of vertices (n) | Sequential Time (s) | Parallel OpenCL Time using GPU (s) |
|------------------------|---------------------|------------------------------------|
| 100                    | 0.002               | 0.016                              |
| 500                    | 0.322               | 0.022                              |
| 1000                   | 2.999               | 0.097                              |
| 5000                   | 311.6               | 9.453                              |
| 10000                  | $\infty$            | 109.0                              |

> **Note**
> The results may vary depending on the hardware used.
> Do not use the sequential version for n > 10000, it will take too long.

## Compilation

### Compilation set up

First, you need to install the OpenCL SDK. You can download it from the following link:
<https://www.khronos.org/opencl/sdk/>

If you are using Windows, you need to install the OpenCL SDK from the link above. If you are using Linux, you can
install the OpenCL SDK using the following command:

```bash
sudo apt install ocl-icd-opencl-dev
```

for macOS, you can install the OpenCL SDK using the following command:

```bash
brew install opencl-headers
```

Then, you need to install CMake. You can download it from the following link:
<https://cmake.org/download/>

To compile the program, you can use the makefile or the CMakelists.txt file.
The makefile is for the GNU compiler collection (GCC) and the CMakelists.txt file is for the CMake build system.

### Makefile build

To compile the program using the makefile, you can use the following commands:

```bash
make
```

You can also compile separately the sequential and parallel programs:

```bash
make wfiSeq
make wfiPar
make wfiParOneFile
```

The output files are in the `buildMakeFile` folder.

### CMake build

To compile the program using CMake, you can use the following commands:

```bash
cmake -B . -DCMAKE_BUILD_TYPE=Release
```

### How to use

The program is an example of the Floyd-Warshall algorithm. If you want to use it in your program, you can find the
functions in the [wfiOpenCl.h](wfiOpenCl/wfiOpenCl.h) and [wfiOpenCl.c](wfiOpenCl/wfiOpenCl.c) file.

Then in your program create a one dimensional array of size n * n and fill it with the values of the graph.
You can then call the function `wfiFloydWarshall` to get the shortest path between all pairs of vertices in the graph by
returning the input graph with the shortest path values.

A complete example of the use of the function is shown in the [wfiOpenCl/main.c](wfiOpenCl/main.c) file.

To print the graph, you can use the functions in the [common/commonFiles.h](common/commonFiles.h)
and [common/commonFiles.c](common/commonFiles.c) files.

It will only print the last and first 10 rows of the graph if the graph is too big (you can change the threashold in
the [common/commonFiles.c](common/commonFiles.c)).

## Project Architecture

~~~
cFloydWarshallParallel
├── .github
│  ├── workflows
│  │   |── c-cpp.yml
│  │   |── cmake.yml
│  │   |── codeql.yml
│  │   |── cpp-linter.yml
│  │   |── dependency-review.yml
│  │   |── flawfinder.yml
│  │   |── greetings.yml
│  │   |── label.yml
│  │   |── stale.yml
|  ├── labels.yml
|  ├── release.yml
├── buildMakeFile
│  ├── placeholder
├── common
|  ├── commonFunctions.c
|  ├── commonFunctions.h
├── data
|  ├── program.cl
├── test
|  ├── CMakelists.txt
|  ├── wfiOpenCLTest.c
|  ├── wfiSequentialTest.c
├── wfiOpenCL
|  ├── CMakeLists.txt
|  ├── main
|  ├── wfiOpenCL.c
|  ├── wfiOpenCL.h
├── wfiOpenCLOneFile
|  ├── main.c
├── wfiSequential
|  ├── CMakeLists.txt
|  ├── main
|  ├── wfiSequential.c
|  ├── wfiSequential.h
├── .clang-format
├── .clang-tidy
├── .editorconfig
├── .gitattributes
├── .gitignore
├── CMakelists.txt
├── CMakePresets.json
├── CMakeSettings.json
├── Makefile
├── README.md
~~~

## GitHub Actions

[![C/C++ CI](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/c-cpp.yml)
[![CMake](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/cmake.yml)
[![CodeQL](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/codeql.yml/badge.svg)](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/codeql.yml)
[![cpp-linter](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/cpp-linter.yml)
[![flawfinder](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/cFloydWarshallParallel/actions/workflows/flawfinder.yml)

This project uses GitHub Actions to build and test the program.

C/C++ CI : This workflow will build the program using the makefile.  
CMake : This workflow will build the program using the CMake build system.  
CodeQL : This workflow will analyze the code to find security vulnerabilities.  
cpp-linter : This workflow will analyze the code to find bugs and potential vulnerabilities.  
flawfinder : This workflow will analyze the code to find bugs and potential vulnerabilities.

> **Note:**  
> The CMake workflow is not working yet for Windows.

## Documentation

Wikipedia:  
<https://en.wikipedia.org/wiki/Floyd–Warshall_algorithm>  
<https://en.wikipedia.org/wiki/Parallel_all-pairs_shortest_path_algorithm#Parallelization>

programiz:  
<https://www.programiz.com/dsa/floyd-warshall-algorithm>

geekeforgeeks:  
<https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/>

moorejs:  
<https://moorejs.github.io/APSP-in-parallel/>

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/cTwinPrimeNumberParallel)](https://github.com/Im-Rises/cTwinPrimeNumberParallel/graphs/contributors)
