cmake_minimum_required(VERSION 3.8)

include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} "main.c")

find_package(OpenCL REQUIRED)

LINK_DIRECTORIES(${OpenCL_LIBRARY})

target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)
