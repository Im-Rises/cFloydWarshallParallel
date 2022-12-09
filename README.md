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

<!--
The algorithm is implemented using the following steps:
1. Read the input file and store the graph in a matrix
2. Create a buffer for the graph matrix and copy the graph matrix to the buffer
3. Create a buffer for the result matrix and copy the graph matrix to the result buffer
4. Create a kernel and set the arguments
5. Execute the kernel
6. Read the result matrix from the result buffer
7. Print the result matrix
8. Free the memory
9. Exit
10. PROFIT!
11. (Optional) Write the result matrix to a file
12. (Optional) Print the execution time
13. (Optional) Print the execution time for each kernel execution
14. (Optional) Print the execution time for each kernel execution and the total execution time
15. (Optional) Print the execution time for each kernel execution and the total execution time and write the result matrix to a file
-->

## Algorithm

PLACEHOLDER

## Results

The results of the programs are shown in the following table:

### Prime Number Algorithm

| Number of processes | Time (s) |
|---------------------|----------|
| 1                   | 0.000    |
| 2                   | 0.000    |
| 4                   | 0.000    |
| 8                   | 0.000    |
| 16                  | 0.000    |
| 32                  | 0.000    |
| 64                  | 0.000    |
| 128                 | 0.000    |

<details>
<summary>Click to see the detailed results</summary>
| Number of processes | Time (s) |
| ------------------- | -------- |
| 1                   | 0.000    |
| 2                   | 0.000    |
| 4                   | 0.000    |
| 8                   | 0.000    |
| 16                  | 0.000    |
| 32                  | 0.000    |
| 64                  | 0.000    |
| 128                 | 0.000    |
</details>

### Twin Prime Number Algorithm

| Number of processes | Time (s) |
|---------------------|----------|
| 1                   | 0.000    |
| 2                   | 0.000    |
| 4                   | 0.000    |
| 8                   | 0.000    |
| 16                  | 0.000    |
| 32                  | 0.000    |
| 64                  | 0.000    |
| 128                 | 0.000    |

<details>
<summary>Click to see the detailed results</summary>
| Number of processes | Time (s) |
| ------------------- | -------- |
| 1                   | 0.000    |
| 2                   | 0.000    |
| 4                   | 0.000    |
| 8                   | 0.000    |
| 16                  | 0.000    |
| 32                  | 0.000    |
| 64                  | 0.000    |
| 128                 | 0.000    |
</details>

## Quick Start

PLACEHOLDER

## Project Architecture

~~~
ParticleEngine
├── .github
|  ├── labels.yml
|  ├── release.yml
│  ├── workflows
│  │   |── cmake.yml
│  │   |── codeql.yml
│  │   |── cpp-cmake-publish.yml
│  │   |── cpp-linter.yml
│  │   |── dependency-review.yml
│  │   |── flawfinder.yml
│  │   |── greetings.yml
│  │   |── label.yml
│  │   |── msvc.yml
│  │   |── stale.yml
├── dependencies
|  ├── glad
|  ├── glfw
|  ├── glfwglm
|  ├── imgui
|  ├── stb
├── ParticleEngine
│  │   |── *
|  ├── Particle
│  │   |── *
|  ├── Scene
│  │   |── *
|  ├── CMakeLists.txt
|  ├── InputManager.cpp
|  ├── InputManager.h
|  ├── main.cpp
|  ├── ParticleEngine.cpp
|  ├── ParticleEngine.h
├── test
|  ├── TestParticle
│  │   |── *
|  ├── CMakeLists.txt
|  ├── integratorTest.cpp
|  ├── physicHandlerTest.cpp
|  ├── particleTest.cpp
├── .clang-format
├── .editorconfig
├── .gitattributes
├── .gitignore
├── CMakelists.txt
├── CMakePresets.json
├── CMakeSettings.json
├── imgui.ini
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

PLACEHOLDER

### CMake build

PLACEHOLDER

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

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/cTwinPrimeNumberParallel)](https://github.com/Im-Rises/cTwinPrimeNumberParallel/graphs/contributors)
