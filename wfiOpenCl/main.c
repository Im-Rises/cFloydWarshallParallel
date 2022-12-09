#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MAX_VALUE 9999

char* readProgramFile(const char* filename) {
    FILE* fp;
    char* source;
    int sz = 0;
    struct stat status;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    if (stat(filename, &status) == 0)
        sz = (int)status.st_size;

    source = (char*)malloc(sz + 1);
    fread(source, sz, 1, fp);
    source[sz] = '\0';
    return source;
}

int main(int argc, char* argv[]) {
    printf("|-----Floyd-Warshall parallel algorithm-----|\n\n");

    if (argc != 2)
    {
        printf("Usage: %s <n value>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    // STEP 0: Init variables
    char* programSourceFilename = "data/program.cl";
    cl_int status = 0;
    cl_uint numPlatforms = 0;
    cl_platform_id* platforms = NULL;
    cl_uint numDevices = 0;
    cl_device_id* devices = NULL;
    cl_context context = NULL;
    cl_command_queue cmdQueue = NULL;
    cl_kernel kernel = NULL;
    char platformName[1000];

    // STEP 1: Discover and initialize the platforms
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    printf("Number of platforms = %d\n", numPlatforms);
    platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    clGetPlatformInfo(*platforms, CL_PLATFORM_NAME, sizeof(platformName), platformName, NULL);
    printf("Name of platform : %s\n", platformName);
    fflush(stdout);

    // STEP 2: Discover and initialize the devices
    status = clGetDeviceIDs(*platforms, CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
    printf("Number of devices = %d\n", (int)numDevices);
    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(*platforms, CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
    for (int i = 0; i < numDevices; i++)
    {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(platformName), platformName, NULL);
        printf("Name of device %d: %s\n\n", i, platformName);
    }

    // STEP 3: Create a context
    context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);

    // STEP 4: Create a command queue
    cmdQueue = clCreateCommandQueue(context, devices, 0, &status);

    // STEP 5: Create program object
    char* programSource = readProgramFile(programSourceFilename);
    if (programSource == NULL)
    {
        perror("Cannot read OpenCL file.\n");
        return 1;
    }
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&programSource, NULL, &status);

    // STEP 6: Build program
    status = clBuildProgram(program, numDevices, devices, NULL, NULL, NULL);
    if (status != CL_SUCCESS)
    {
        printf("Error in building program.\n");
        fflush(stdout);
        size_t len;
        char buffer[2048];
        clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s \n", buffer);
        fflush(stdout);
        exit(1);
    }

    // STEP 7: Create kernel object
    kernel = clCreateKernel(program, "floydWarshall", &status);

    // STEP 8: Create buffers
    int* A = (int*)malloc(n * n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i * n + j] = 0;
    A[0 * n + 1] = 1;
    A[0 * n + 2] = 2;
    A[0 * n + 3] = 3;
    A[1 * n + 2] = 4;
    A[1 * n + 3] = 5;
    A[2 * n + 3] = 6;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && A[i * n + j] == 0)
                A[i * n + j] = MAX_VALUE;
    //          A[i * n + j] = n + 1;
    cl_mem A_buf = clCreateBuffer(context, CL_MEM_READ_WRITE, n * n * sizeof(int), NULL, &status);
    status = clEnqueueWriteBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 9: Configure work-item structure
    size_t globalWorkSize[2] = { n, n };
    size_t localWorkSize[2] = { 1, 1 };

    // STEP 10: Set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &A_buf);
    status = clSetKernelArg(kernel, 1, sizeof(int), &n);

    //    // STEP 11: Enqueue kernel for execution
    //    status = clEnqueueNDRangeKernel(cmdQueue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    //
    //    // STEP 12: Read the output buffer back to the host
    //    status = clEnqueueReadBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 11: Enqueue kernel for execution
    for (int k = 0; k < n; k++)
    {
        status = clSetKernelArg(kernel, 2, sizeof(int), &k);
        status = clEnqueueNDRangeKernel(cmdQueue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    }

    // STEP 12: Read the output buffer back to the host
    status = clEnqueueReadBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 13: Display the result
    printf("Result:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%04d ", A[i * n + j]);
        printf("\n");
    }

    // STEP 14: Release OpenCL resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(cmdQueue);
    clReleaseContext(context);
    clReleaseMemObject(A_buf);
    free(A);
    free(devices);
    free(platforms);
    free(programSource);

    return 0;
}
