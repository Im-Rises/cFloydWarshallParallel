#include "commonFunctions.h"

#include <stdlib.h>
#include <stdio.h>

#define PRINT_MATRIX_THRESHOLD 30

int* generateTestMatrix(int n) {
    /*
     * Generate a test matrix looks like this (for n = 4):
     * 0  1  3  4
     * 1  0  2  3
     * 3  2  0  1
     * 4  3  1  0
     */
    int* matrix = (int*)malloc(n * n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                matrix[i * n + j] = 0;
            else if (i == j - 1)
                matrix[i * n + j] = 1;
            else
                matrix[i * n + j] = n + 1;
        }
    }
    matrix[(n - 1) * n] = 1;
    return matrix;
}

int* generateOutputTestMatrix(const int n) {
    /*
     * Create a matrix looks like this (for n = 4):
     * 0  1  2  3
     * 1  0  1  2
     * 2  1  0  1
     * 3  2  1  0
     */
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

int countDigit(long long n) {
    if (n / 10 == 0)
        return 1;
    return 1 + countDigit(n / 10);
}

void printMatrix(int* matrix, int n) {
    if (n > PRINT_MATRIX_THRESHOLD)
    {
        printf("Matrix is too large to printed completely.\n");
        printf("- First row: ");
        for (int i = 0; i < n; i++)
        {
            if (matrix[i] == n + 1)
                printf("%*s ", countDigit(n + 1), "INF");
            else
                printf("%*d ", countDigit(n + 1), matrix[i]);
        }
        printf("\n");

        printf("- Last row: ");
        for (int i = (n - 1) * n; i < n * n; i++)
        {
            if (matrix[i] == n + 1)
                printf("%*s ", countDigit(n + 1), "INF");
            else
                printf("%*d ", countDigit(n + 1), matrix[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i * n + j] == n + 1)
                    printf("%4s", "INF");
                else
                    printf("%4d", matrix[i * n + j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}
