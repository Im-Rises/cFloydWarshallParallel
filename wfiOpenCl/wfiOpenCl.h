#ifndef WFIOPENCL_H
#define WFIOPENCL_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

void wfiOpenCl(int* matrix, int n, char* programPath, char* programFunction, cl_int status, cl_device_id* devices, int numDevices, cl_context context);

#endif // WFIOPENCL_H
