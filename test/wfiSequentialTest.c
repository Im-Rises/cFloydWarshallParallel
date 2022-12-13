#include <stdlib.h>
#include <stdio.h>

#include "../common/commonFunctions.h"
#include "../wfiSequential/wfiSequential.h"

int* generateOutputTestMatrix(const int n) {
    int* matrix = malloc(n * n * sizeof(int));

    // Fill the beginning
    for (int i = 0; i < n; i++)
    {
        int value = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                matrix[i * n + j] = 0;
                value = 1;
            }
            else
            {
                matrix[i * n + j] = value++;
            }
        }
    }

    // Fill the rest
    for (int j = 0; j < n; j++)
    {
        int value = n - 1;
        int hasReachedZero = 0;
        for (int i = 0; i < n; i++)
        {
            if (i == j)
            {
                matrix[i * n + j] = 0;
                value = n - 1;
                hasReachedZero = 1;
            }
            else if (hasReachedZero)
            {
                matrix[i * n + j] = value--;
            }
        }
    }
    return matrix;
}

int checkMatrix(const int* matrix1, const int* matrix2, int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix1[i * n + j] != matrix2[i * n + j])
                return 0;
        }
    }
    return 1;
}

int testFloydWarshall(const int n, const int errorCode) {
    int* matrix = generateMatrix(n);
    int* outputTestMatrix = generateOutputTestMatrix(n);
    floydWarshall(matrix, n);
    //    printMatrix(matrix, n);
    //    printMatrix(outputTestMatrix, n);
    int matricesEquality = checkMatrix(matrix, outputTestMatrix, n);
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
