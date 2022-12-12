#include <stdio.h>
#include <stdlib.h>

#define PRINT_MATRIX_THRESHOLD 30

void floydWarshall(int* matrix, int n) {
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i * n + k] + matrix[k * n + j] < matrix[i * n + j])
                {
                    matrix[i * n + j] = matrix[i * n + k] + matrix[k * n + j];
                }
            }
        }
    }
}

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

int main(int argc, char* argv[]) {
    printf("|-----Floyd-Warshall algorithm-----|\n\n");
    // Check the command line arguments
    //    if (argc != 2)
    //    {
    //        printf("Usage: %s <n value>\n", argv[0]);
    //        return 1;
    //    }
    //    cl_int n = atoi(argv[1]);

    // Read from command line
    int n = 10;
    scanf("%d", &n);

    int* graph = generateMatrix(n);

    printf("Init matrix:\n");
    printMatrix(graph, n);

    floydWarshall(graph, n);

    printf("Result matrix is:\n");
    printMatrix(graph, n);

    free(graph);

    return 0;
}
