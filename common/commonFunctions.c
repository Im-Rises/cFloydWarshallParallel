#include "commonFunctions.h"

#include <stdlib.h>
#include <stdio.h>

#define PRINT_MATRIX_THRESHOLD 30

int* generateMatrix(int n) {
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