#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
   
/* Kernel (function to be run on device) */    
const char *code =
 "__kernel void arrayadd(__global int *x, __global int *y, __global int *z)\n"
    "{\n"
    "  size_t id = get_global_id(0);\n"
    "  z[id] = x[id] + y[id];\n"
    "}\n";

int main()
{
  cl_context context;
  cl_context_properties properties[3];
  cl_kernel kernel;
  cl_command_queue commandqueue;
  cl_program program;
  cl_int err;
  cl_uint num_of_platforms;
  cl_platform_id platform_id;
  cl_device_id device_id;
  cl_uint num_of_devices;
  cl_mem buffer1, buffer2, outputbuffer;

  size_t global;
  int arraysize;
  int a[20];
  int b[20];
  int results[20];
  int i;

  printf("Enter the size of arrays\n");
  scanf("%d",&arraysize);

  printf("Enter %d elements of First Array\n",arraysize);
  for(i=0;i<arraysize;i++)
        scanf("%d",&a[i]);

  printf("Enter %d elements of Second Array\n",arraysize);
  for(i=0;i<arraysize;i++)
        scanf("%d",&b[i]);

  /* Get a list of platforms available on your system. (i.e. OpenCL installations on your system).*/
  if (clGetPlatformIDs(1, &platform_id, &num_of_platforms)!= CL_SUCCESS)
   {
    printf("Not getting Platform id\n");
    return 1;
   }
  
  /* Get a list of devices(cpu or gpu) supported for available OpenCL platforms.*/
  if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id, &num_of_devices) != CL_SUCCESS)
   {
    printf("Not getting Device id\n");
    return 1;
   }
   
   /* Get context properties list.*/
  properties[0]= CL_CONTEXT_PLATFORM;
  properties[1]= (cl_context_properties) platform_id;
  properties[2]= 0;

  /* Create a context (i.e. collection of GPU and CPU).*/
  context = clCreateContext(properties,1,&device_id,NULL,NULL,&err);
  
  /* Create command queue for the context and device.*/
  commandqueue = clCreateCommandQueue(context, device_id, 0, &err);
   
   /* Create a program object for all kernels.*/
   program = clCreateProgramWithSource(context,1,(const char **) &code, NULL, &err);
    
  /* Build/Compile the program.*/
  if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS)
   {
    printf("Error during building program\n");
    return 1;
   }
     
  /* Create kernel object for the specific kernel which you want to execute.*/
  kernel = clCreateKernel(program, "arrayadd", &err);


  buffer1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * arraysize, NULL, NULL);
  buffer2 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * arraysize, NULL, NULL);
  outputbuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * arraysize, NULL, NULL);   

  /* Load data into the input buffer.*/
  clEnqueueWriteBuffer(commandqueue, buffer1, CL_TRUE, 0, sizeof(int) * arraysize, a, 0, NULL, NULL);
  clEnqueueWriteBuffer(commandqueue, buffer2, CL_TRUE, 0, sizeof(int) * arraysize, b, 0, NULL, NULL);
  
  /* Set the arguments for the kernel.*/
  clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer1);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer2);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputbuffer);
   
  global=arraysize;
    
  /* Enqueue the kernel for execution. */
  clEnqueueNDRangeKernel(commandqueue, kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
  clFinish(commandqueue);

  /* Copy the results from Output buffer to Host(CPU) variable. */
  clEnqueueReadBuffer(commandqueue, outputbuffer, CL_TRUE, 0, sizeof(int) *arraysize, results, 0, NULL, NULL);

  /* Print the results. */
  printf("Addition of Two Arrays is as follows: \n");
  
  for(i=0;i<arraysize; i++)
   {
    printf("%d\n",results[i]);
   }
   
 /* Free OpenCL resources. */
  clReleaseMemObject(buffer1);
  clReleaseMemObject(buffer2);
  clReleaseMemObject(outputbuffer);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(commandqueue);
  clReleaseContext(context);
    
  return 0;
}
