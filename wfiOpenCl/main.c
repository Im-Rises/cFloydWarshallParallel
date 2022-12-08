#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <stdio.h>
#include <stdlib.h>

char* programSource = "__kernel void add(__global int* a, __global int* b, __global int* c) { int i = get_global_id(0); c[i] = a[i] + b[i]; }";

int main(int argc, char* argv[]) {
    printf("|-----Floyd–Warshall parallel algorithm-----|\n\n");
    if (argc < 2)
    {
        printf("Usage: %s <matrix size> ", argv[0]);
        return 1;
    }

    int nV = atoi(argv[1]);

    // Create the two input vectors
    int i;
    int* A = (int*)malloc(sizeof(int) * nV * nV);
    int* B = (int*)malloc(sizeof(int) * nV * nV);
    for (i = 0; i < nV * nV; i++)
    {
        A[i] = i;
        B[i] = i;
    }

    // Load the kernel source code into the array source_str
    FILE* fp;
    char fileName[] = "../data/program.cl";
    char* source_str;
    size_t source_size;

    fp = fopen(fileName, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    source_str = (char*)malloc(0x100000);
    source_size = fread(source_str, 1, 0x100000, fp);
    fclose(fp);



    return 0;
}
