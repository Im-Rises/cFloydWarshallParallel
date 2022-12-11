#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

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
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
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
    printf("|-----Floyd-Warshall parallel OpenCL algorithm-----|\n\n");

    // Check the command line arguments
    if (argc != 2)
    {
        printf("Usage: %s <n value>\n", argv[0]);
        return 1;
    }
    cl_int n = atoi(argv[1]);

    // STEP 0: Init variables
    char* programSourceFilename = "data/program.cl";
    char* programFunction = "floydWarshall";
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

    // STEP 2: Discover and initialize the devices
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
    printf("Number of devices = %d\n", (int)numDevices);
    devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
    for (int i = 0; i < numDevices; i++)
    {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(platformName), platformName, NULL);
        printf("Name of device %d: %s\n\n", i, platformName);
    }

    // STEP 3: Create a context
    context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);

    // STEP 4: Create a command queue
    cmdQueue = clCreateCommandQueue(context, devices[0], 0, &status);

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
        size_t len;
        char buffer[2048];
        clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s \n", buffer);
        exit(1);
    }

    // STEP 7: Create kernel object
    kernel = clCreateKernel(program, programFunction, &status);

    // STEP 8: Create buffers
    int* A = generateMatrix(n);
    cl_mem A_buf = clCreateBuffer(context, CL_MEM_READ_WRITE, n * n * sizeof(int), NULL, &status);
    status = clEnqueueWriteBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 9: Configure work-item structure
    size_t globalWorkSize[2] = { n, n };
    // V1:
    size_t localWorkSize[2] = { 1, 1 }; // TODO: change to something else

    // V2:
    //    size_t localWorkSize[3] = { 1, 1, 1 };
    //    clGetDeviceInfo(devices[0], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * 3, localWorkSize, NULL);
    //    if (localWorkSize[0] > globalWorkSize[0])
    //        localWorkSize[0] = globalWorkSize[0];
    //    if (localWorkSize[1] > globalWorkSize[1])
    //        localWorkSize[1] = globalWorkSize[1];

    // V3:
    //    size_t localWorkSize[3] = { 16, 16, 16 };
    //    if (localWorkSize[0] > globalWorkSize[0])
    //        localWorkSize[0] = globalWorkSize[0];
    //    if (localWorkSize[1] > globalWorkSize[1])
    //        localWorkSize[1] = globalWorkSize[1];


    printf("Global work size: %d\n", (int)globalWorkSize[0]);
    printf("Local work size: %d, %d\n\n", (int)localWorkSize[0], (int)localWorkSize[1]);

    // STEP 10: Print initial matrix
    printf("Initial matrix:\n");
    printMatrix(A, n);

    // STEP 11: Set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &A_buf);
    status = clSetKernelArg(kernel, 2, sizeof(cl_int), &n);

    // STEP 12: Enqueue kernel for execution and execute for each k = 0, 1, ..., n - 1
    for (int k = 0; k < n; k++)
    {
        status = clSetKernelArg(kernel, 1, sizeof(int), &k);
        status = clEnqueueNDRangeKernel(cmdQueue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    }

    // STEP 13: Read the output buffer back to the host
    status = clEnqueueReadBuffer(cmdQueue, A_buf, CL_TRUE, 0, n * n * sizeof(int), A, 0, NULL, NULL);

    // STEP 14: Display the result
    printf("Result:\n");
    printMatrix(A, n);

    // STEP 15: Release OpenCL resources
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
