#include <stdlib.h>
#include <stdio.h>

#include "../common/commonFunctions.h"
#include "../wfiOpenCl/wfiOpenCl.h"

int testFloydWarshall(const int n, const int errorCode, char* programPath, char* programFunction, cl_int status, cl_device_id* devices, int numDevices, cl_context context) {
    int* matrix = generateTestMatrix(n);
    int* outputTestMatrix = generateOutputTestMatrix(n);
    wfiOpenCl(matrix, n, programPath, programFunction, status, devices, numDevices, context);
    //    floydWarshall(matrix, n);
    //    printMatrix(matrix, n);
    //    printMatrix(outputTestMatrix, n);
    int matricesEquality = checkMatricesEquality(matrix, outputTestMatrix, n);
    free(matrix);
    free(outputTestMatrix);
    if (!matricesEquality)
    {
        printf("- WFI for n = %d, fail!\n", n);
        return errorCode;
    }

    printf("- WFI for n = %d, pass!\n", n);
    return 0;
}

int main(int argc, char* argv[]) {
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

    // STEP 4-14: Test Floyd-Warshall algorithm
    printf("WFI OpenCL Test:\n");
    int errorCode = 0;

    errorCode += testFloydWarshall(10, 1, programSourceFilename, programFunction, status, devices, numDevices, context);
    errorCode += testFloydWarshall(100, 2, programSourceFilename, programFunction, status, devices, numDevices, context);
    errorCode += testFloydWarshall(1000, 4, programSourceFilename, programFunction, status, devices, numDevices, context);

    // STEP 15: Release OpenCL resources
    clReleaseContext(context);
    free(devices);
    free(platforms);

    if (errorCode == 0)
    {
        printf("All tests passed!\n");
    }
    else
    {
        printf("Some tests failed!\n");
        printf("Error code: %d : 0X%02X\n", errorCode, errorCode);
    }

    return errorCode;
}
