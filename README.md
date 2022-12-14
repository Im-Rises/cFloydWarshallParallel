# cFloydWarshallParallel

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/206360390-76940955-0a28-43b5-83fb-46409c4324f7.png" alt="openclLogo" style="height:60px;"/>
</p>

## Description

This is a parallel implementation of the Floyd-Warshall algorithm using OpenCL.

The algorithm is implemented in C and the OpenCL kernel is written in OpenCL C. The program is compiled using CMake.

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

### Prime Number Algorithm

| Number of vertices (n) | Sequential Time (s) | Parallel OpenCL Time (s) |
|------------------------|---------------------|--------------------------|
| 100                    | 0.000000            | 0.000000                 |
| 1000                   | 0.000000            | 0.000000                 |
| 10000                  | 0.000000            | 0.000000                 |

## Quick Start

PLACEHOLDER

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

## Dependencies

- C17 compiler
- CMake
- Makefile
- OpenCL

## Compilation

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
```

### CMake build

To compile the program using CMake, you can use the following commands:

```bash
cmake -B . -DCMAKE_BUILD_TYPE=Release
```

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
