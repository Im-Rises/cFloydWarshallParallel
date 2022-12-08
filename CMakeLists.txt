cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project("OpenCLTestProject")
add_subdirectory(${PROJECT_NAME})

project("wfiSequential")
add_subdirectory(${PROJECT_NAME})

project("wfiOpenCl")
add_subdirectory(${PROJECT_NAME})

enable_testing()
add_subdirectory("test")
