#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char* floyProgramSource = "kernel void floy(global int *a, int n) {"
                          "int i = get_global_id(0);"
                          "int j = get_global_id(1);"
                          "int k = get_global_id(2);"
                          "int ij = i*n+j;"
                          "int ik = i*n+k;"
                          "int kj = k*n+j;"
                          "if (a[ik] + a[kj] < a[ij]) {"
                          "a[ij] = a[ik] + a[kj];"
                          "}"
                          "}\0";


char* readProgramFile(const char* filename) {
    FILE* fp;
    char* source;
    int sz = 0;
    struct stat status;

    fp = fopen(filename, "r");
    if (fp == 0)
    {
        printf("Cannot read OpenCL file.\n");
        return 0;
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

    // STEP 0: Init variables
    cl_int status;
    cl_uint numPlatforms = 0;
    cl_platform_id* platforms = NULL;
    cl_uint numDevices;
    cl_device_id* devices = NULL;
    cl_context context = NULL;
    cl_command_queue cmdQueue;
    cl_kernel kernel = NULL;

    // STEP 1: Discover and initialize the platforms
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    printf("Number of platforms = %d\n", numPlatforms);
    platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    char Name[1000];
    clGetPlatformInfo(*platforms, CL_PLATFORM_NAME, sizeof(Name), Name, NULL);
    printf("Name of platform : %s\n", Name);
    fflush(stdout);


    // STEP 2: Discover and initialize the devices
    status = clGetDeviceIDs(*platforms, CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
    printf("Number of devices = %d\n", (int)numDevices);
    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(*platforms, CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
    for (int i = 0; i < numDevices; i++)
    {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(Name), Name, NULL);
        printf("Name of device %d: %s\n\n", i, Name);
    }

    // STEP 3: Create a context
    context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);

    // STEP 4: Create a command queue
    cmdQueue = clCreateCommandQueue(context, devices, 0, &status);

    // STEP 5: Create program object
    char* programSource = readProgramFile("data/program.cl");
    programSource = floyProgramSource;
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
    int n = 4;
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
                A[i * n + j] = 9999;
    cl_mem A_buf = clCreateBuffer(context, CL_MEM_READ_WRITE, n * n * sizeof(int), NULL, &status);
    status = clEnqueueWriteBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 9: Set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &A_buf);
    status = clSetKernelArg(kernel, 1, sizeof(int), &n);

    // STEP 10: Configure work-item structure
    size_t globalWorkSize[2] = { n, n };
    size_t localWorkSize[2] = { 1, 1 };

    // STEP 11: Enqueue kernel for execution
    status = clEnqueueNDRangeKernel(cmdQueue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);

    // STEP 12: Read the output buffer back to the host
    status = clEnqueueReadBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 13: Display the result
    printf("Result:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i * n + j]);
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
