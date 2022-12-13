#include <stdlib.h>
#include <stdio.h>

#include "../common/commonFunctions.h"
#include "../wfiSequential/wfiSequential.h"

int testFloydWarshall(const int n, const int errorCode) {
    int* matrix = generateTestMatrix(n);
    int* outputTestMatrix = generateOutputTestMatrix(n);
    floydWarshall(matrix, n);
    //    printMatrix(matrix, n);
    //    printMatrix(outputTestMatrix, n);
    int matricesEquality = checkMatricesEquality(matrix, outputTestMatrix, n);
    free(matrix);
    free(outputTestMatrix);
    if (!matricesEquality)
    {
        printf("- WFI for n = %d, fail!\n", n);
        return errorCode;
    }

    printf("- WFI for n = %d, pass!\n", n);
    return 0;
}

int main(int argc, char* argv[]) {
    printf("WFI Sequential Test:\n");
    int errorCode = 0;
    errorCode += testFloydWarshall(10, 1);
    errorCode += testFloydWarshall(100, 2);
    errorCode += testFloydWarshall(1000, 4);

    if (errorCode == 0)
    {
        printf("All tests passed!\n");
    }
    else
    {
        printf("Some tests failed!\n");
        printf("Error code: %d : 0X%02X\n", errorCode, errorCode);
    }

    return errorCode;
}
