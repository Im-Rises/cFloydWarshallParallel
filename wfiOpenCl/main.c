// #ifdef __APPLE__
// #include <OpenCL/opencl.h>
// #else
// #include <CL/cl.h>
// #endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../common/commonFunctions.h"
#include "wfiOpencl.h"

#define PRINT_MATRIX_THRESHOLD 30

int main(int argc, char* argv[]) {
    printf("|-----Floyd-Warshall parallel OpenCL algorithm-----|\n\n");

    // Check the command line arguments
    if (argc != 2)
    {
        printf("Usage: %s <n value>\n", argv[0]);
        return 1;
    }
    cl_int n = atoi(argv[1]);

    //    // Or Read from command line
    //    cl_int n = 10;
    //    scanf("%d", &n);

    // STEP 0: Init variables
    char* programSourceFilename = "data/program.cl";
    char* programFunction = "floydWarshall";
    cl_int status = 0;
    cl_uint numPlatforms = 0;
    cl_platform_id* platforms = NULL;
    cl_uint numDevices = 0;
    cl_device_id* devices = NULL;
    cl_context context = NULL;
    char platformName[1000];

    // STEP 1: Discover and initialize the platforms
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    printf("Number of platforms = %d\n", numPlatforms);
    platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    clGetPlatformInfo(*platforms, CL_PLATFORM_NAME, sizeof(platformName), platformName, NULL);
    printf("Name of platform : %s\n", platformName);

    // STEP 2: Discover and initialize the devices
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
    printf("Number of devices = %d\n", (int)numDevices);
    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
    for (int i = 0; i < numDevices; i++)
    {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(platformName), platformName, NULL);
        printf("Name of device %d: %s\n", i, platformName);
    }

    // STEP 3: Create a context
    context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);

    // STEP 4: Create matrix and print it
    int* A = generateTestMatrix(n);
    printf("Initial matrix:\n");
    printMatrix(A, n);

    // STEP 5-13: Call OpenCL functions
    wfiOpenCl(A, n, programSourceFilename, programFunction, status, devices, numDevices, context);

    // STEP 14: Display the result
    printf("Result:\n");
    printMatrix(A, n);

    // STEP 15: Release OpenCL resources
    clReleaseContext(context);
    free(A);
    free(devices);
    free(platforms);

    return 0;
}
