#include <stdio.h>
#include <stdlib.h>

#include "../common/commonFunctions.h"
#include "wfiSequential.h"

#include <time.h>

int main(int argc, char* argv[]) {
    printf("|-----Floyd-Warshall algorithm-----|\n\n");
    //     Check the command line arguments
    if (argc != 2)
    {
        printf("Usage: %s <n value>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    //    // Or Read from command line
    //    int n = 10;
    //    scanf("%d", &n);

    int* graph = generateTestMatrix(n);

    printf("Init matrix:\n");
    printMatrix(graph, n);

    clock_t start = clock();
    floydWarshall(graph, n);
    clock_t end = clock();

    printf("Result matrix is:\n");
    printMatrix(graph, n);

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);

    free(graph);
    return 0;
}
