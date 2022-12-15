set(SRCS_TEST "wfiOpenClTest.c" "wfiSequentialTest.c")

set(HDRS "../common/commonFunctions.h" "../wfiSequential/wfiSequential.h" "../wfiOpenCl/wfiOpenCl.h")
set(SRCS "../common/commonFunctions.c" "../wfiSequential/wfiSequential.c" "../wfiOpenCl/wfiOpenCl.c")

enable_testing()

find_package(OpenCL REQUIRED)

foreach (test ${SRCS_TEST})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test} ${HDRS} ${SRCS})
    LINK_DIRECTORIES(${OpenCL_LIBRARY})
    target_link_libraries(${testName} OpenCL::OpenCL)
    add_test(NAME ${testName} COMMAND ${testName} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endforeach ()
