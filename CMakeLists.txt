﻿cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project("wfiSequential")
add_subdirectory(${PROJECT_NAME})

project("wfiOpenCl")
add_subdirectory(${PROJECT_NAME})

enable_testing()
add_subdirectory("test")
