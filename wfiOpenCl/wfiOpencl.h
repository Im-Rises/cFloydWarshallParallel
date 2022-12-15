#ifndef WFIOPENCL_H
#define WFIOPENCL_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

void wfiOpenCl(int* A, int n, char* programSourceFilename, char* programFunction, cl_int status, cl_device_id* devices, int numDevices, cl_context context);

#endif // WFIOPENCL_H
