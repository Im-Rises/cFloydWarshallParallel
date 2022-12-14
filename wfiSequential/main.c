#include <stdio.h>
#include <stdlib.h>

#include "../common/commonFunctions.h"
#include "wfiSequential.h"

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

    int* graph = generateTestMatrix(n);

    printf("Init matrix:\n");
    printMatrix(graph, n);

    floydWarshall(graph, n);

    printf("Result matrix is:\n");
    printMatrix(graph, n);

    free(graph);

    return 0;
}
