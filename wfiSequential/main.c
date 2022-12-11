#include <stdio.h>
#include <stdlib.h>

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

void printMatrix(int* matrix, int n) {
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
    printf("\n");
}

int main(int argc, char* argv[]) {
    printf("|-----Floyd-Warshall algorithm-----|\n\n");
    //    if (argc != 2)
    //    {
    //        printf("Usage: %s <matrix size>\n", argv[0]);
    //        return 1;
    //    }
    //    int n = atoi(argv[1]);
    int n = 4;
    int* graph = generateMatrix(n);

    printf("Init matrix:\n");
    printMatrix(graph, n);

    floydWarshall(graph, n);

    printf("Result matrix is:\n");
    printMatrix(graph, n);

    //    free(graph);

    return 0;
}
