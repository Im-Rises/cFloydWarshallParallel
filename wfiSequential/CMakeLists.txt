set(HDRS "../common/commonFunctions.h" "wfiSequential.h")
set(SRCS "../common/commonFunctions.c" "wfiSequential.c")

add_executable(${PROJECT_NAME} main.c ${HDRS} ${SRCS})
