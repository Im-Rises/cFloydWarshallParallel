#include "wfiSequential.h"

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
