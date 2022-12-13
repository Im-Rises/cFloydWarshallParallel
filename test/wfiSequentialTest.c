#include <stdlib.h>

#include "../common/commonFunctions.h"
#include "../wfiSequential/wfiSequential.h"

int checkMatrix(int* matrix1, int* matrix2, int n) {
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

int testFloydWarshall() {
    int errorCode = 0;
    int n = 10;
    int* graph = generateMatrix(n);
    floydWarshall(graph, n);
    if (checkMatrix(graph, graph, n))
    {
        errorCode = 1;
    }

    free(graph);
    return errorCode;
}

int main(int argc, char* argv[]) {
    testFloydWarshall();
    return 0;
}
