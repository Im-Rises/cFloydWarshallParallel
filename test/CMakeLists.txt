set(SRCS_TEST "wfiOpenClTest.c" "wfiSequentialTest.c")

set(HDRS "../common/commonFunctions.h" "../wfiSequential/wfiSequential.h")
set(SRCS "../common/commonFunctions.c" "../wfiSequential/wfiSequential.C")

enable_testing()

foreach (test ${SRCS_TEST})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test} ${HDRS} ${SRCS})
    add_test(${testName} ${testName})
endforeach ()

