#include "wfiOpenCl.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char* readProgramFile(const char* filename);

void wfiOpenCl(int* matrix, int n, char* programPath, char* programFunction, cl_int status, cl_device_id* devices, int numDevices, cl_context context) {
    cl_kernel kernel = NULL;
    cl_command_queue cmdQueue = NULL;

    // STEP 5: Create a command queue
    cmdQueue = clCreateCommandQueue(context, devices[0], 0, &status);

    // STEP 6: Create program object
    char* programSource = readProgramFile(programPath);
    if (programSource == NULL)
    {
        perror("Error: Cannot read OpenCL file.\n");
        exit(1);
    }
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&programSource, NULL, &status);

    // STEP 7: Build program
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

    // STEP 8: Create kernel object
    kernel = clCreateKernel(program, programFunction, &status);

    // STEP 9: Create OpenCL buffers
    cl_mem matrixBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, n * n * sizeof(int), NULL, &status);
    status = clEnqueueWriteBuffer(cmdQueue, matrixBuffer, CL_TRUE, 0, n * n * sizeof(int), matrix, 0, NULL, NULL);

    // STEP 10: Configure work-item structure
    size_t globalWorkSize[2] = { n, n };
    //    printf("Global work size: %d, %d\n\n", (int)globalWorkSize[0], (int)globalWorkSize[1]);

    // STEP 11: Set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &matrixBuffer);
    status = clSetKernelArg(kernel, 2, sizeof(cl_int), &n);

    // STEP 12: Enqueue kernel for execution and execute for each k = 0, 1, ..., n - 1
    for (int k = 0; k < n; k++)
    {
        status = clSetKernelArg(kernel, 1, sizeof(int), &k);
        status = clEnqueueNDRangeKernel(cmdQueue, kernel, 2, NULL, globalWorkSize, NULL, 0, NULL, NULL);
    }

    // STEP 13: Read the output buffer back to the host
    status = clEnqueueReadBuffer(cmdQueue, matrixBuffer, CL_TRUE, 0, n * n * sizeof(int), matrix, 0, NULL, NULL);

    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(cmdQueue);
    clReleaseMemObject(matrixBuffer);
    free(programSource);
}

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
