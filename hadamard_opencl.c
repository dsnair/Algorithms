# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <CL/cl.h>

// declare global variables
int n;
int rowVec = 0, colVec = 0;
float *vec1 = NULL;
float *vec2 = NULL;
float *hadaVec = NULL;
size_t dataSizeVec;

cl_int status;

cl_uint numPlatforms = 0, numDevices = 0;
cl_platform_id *platforms = NULL;
cl_device_id *devices = NULL;

cl_context context = NULL;
cl_command_queue queue = NULL;
cl_program program = NULL;
cl_kernel kernel = NULL;

cl_mem bufferA, bufferB, bufferC;

// declare functions
int InitializeVec();
float HadamardMult();
float VecSum();

// kernel for Hadamard product
const char *HadaMult =							
"__kernel                                       \n"
"void Hadamard(__global float *inputB,			\n"
"			   __global float *inputC,			\n"
"			   __global float *outputD,		  	\n"
"              int rowVec,                     	\n"
"              int colVec)                     	\n"
"{                                             	\n"
"   int i = get_global_id(0);  // NDRange = 1  	\n"
"   for (i = 0; i < rowVec * colVec; i++) {		\n"
"		outputD[i] = inputB[i] * inputC[i];		\n"
"	}                                          	\n"
"}												\n";

int main() {
	int i;
	float sum;
	clock_t start, stop;

	// step 1: query platform info
	status = clGetPlatformIDs(0, NULL, &numPlatforms);
	platforms = (cl_platform_id*)malloc(numPlatforms *sizeof(cl_platform_id));
	status = clGetPlatformIDs(numPlatforms, platforms, NULL);
	if (status != 0) {
		printf("Step 1: Failed to discover available platforms. Error code = %d. \n", status);
	}

  	// step 2: query devices
	status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
	devices = (cl_device_id*)malloc(numDevices *sizeof(cl_device_id));
	status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
	if (status != 0) {
		printf("Step 2: Failed to discover available devices. Error code = %d. \n", status);
	}

  	// step 3: create context
	context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);
	if (status != 0) {
		printf("Step 3: Failed to create the context. Error code = %d. \n", status);
	}

  	// step 4: set up command queue
	queue = clCreateCommandQueue(context, devices[0], 0, &status);
	if (status != 0) {
		printf("Step 4: Failed to set up the command queue. Error code = %d. \n", status);
	}

	InitializeVec();

	start = clock();
		HadamardMult();
	stop = clock();

	sum = VecSum();

	printf("%s \t %6s \t %6s \t %6s \n", "i", "vec1", "vec2", "hadaVec");
	for (i = 0; i < rowVec * colVec; i++) {
    	printf("%d \t %f \t %f \t %f \n", i, vec1[i], vec2[i], hadaVec[i]);
	}

	printf("The dot poduct is %f. \n", sum);
   	printf("OpenCL elapsed time = %f seconds. \n", (double)(stop - start) / CLOCKS_PER_SEC);

   	// step 13: free used memory
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseMemObject(bufferA);
	clReleaseMemObject(bufferB);
	clReleaseMemObject(bufferC);
	clReleaseContext(context);
	free(vec1);
	free(vec2);
	free(hadaVec);
	free(platforms);
	free(devices);
	if (status != 0) {
		printf("Step 13: Failed to deallocate memory. Error code = %d. \n", status);
	}
}

/* 'InitializeVec' initializes vectors */
int InitializeVec() {
	n = 3;
	rowVec = n, colVec = 1;  // row and column size of vectors
	int i;
	
	// set the size of the storage and setup the storage for the vectors
	dataSizeVec = colVec * rowVec * sizeof(float);
	vec1 = (float *)malloc(dataSizeVec);
	vec2 = (float *)malloc(dataSizeVec);
	hadaVec = (float *)malloc(dataSizeVec);
	
	srand(time(NULL));  // randomize seed	
	// generate vectors
	for (i = 0; i < rowVec * colVec; i++) {
		vec1[i] = rand() % 100 + 1;  // random number between [1, 100]
	}
	for (i = rowVec * colVec - 1; i >=0; i--) {
		vec2[i] = rand() % 100 + 1;  // random number between [1, 100]
	}
}

/* 'HadamardMult' takes the Hadamard product of two vectors i.e. elementwise multiplies two vectors */
float HadamardMult() {
	// step 5: create buffer objects
	bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, dataSizeVec, NULL, &status);
	bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, dataSizeVec, NULL, &status);
	bufferC = clCreateBuffer(context, CL_MEM_READ_WRITE, dataSizeVec, NULL, &status);
	if (status != 0) {
		printf("Step 5: Failed to create memory buffers. Error code = %d. \n", status);
	}

	// step 6: write buffer objects
	status = clEnqueueWriteBuffer(queue, bufferA, CL_FALSE, 0, dataSizeVec, vec1, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(queue, bufferB, CL_FALSE, 0, dataSizeVec, vec2, 0, NULL, NULL);
	if (status != 0) {
		printf("Step 6: Failed to copy data to memory buffers. Error code = %d. \n", status);
	}

	// step 7: create program objects	
	program = clCreateProgramWithSource(context, 1, (const char **)&HadaMult, NULL, &status);
	if (status != 0) {
		printf("Step 7: Failed to create program objects. Error code = %d. \n", status);
	}
 
	// step 8: build program executables
	status = clBuildProgram(program, numDevices, devices, NULL, NULL, NULL);
	if (status != 0) {
		printf("Step 8: Failed to build program executables. Error code = %d. \n", status);
	}

	// step 9: create kernel objects
	kernel = clCreateKernel(program, "Hadamard", &status);
	if (status != 0) {
		printf("Step 9: Failed to create kernel objects. Error code = %d. \n", status);
	}

	// step 10: set kernel arguments
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferA);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferB);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferC);
	clSetKernelArg(kernel, 3, sizeof(int), &rowVec);
	clSetKernelArg(kernel, 4, sizeof(int), &colVec);	
	if (status != 0) {
		printf("Step 10: Failed to set kernel arguments. Error code = %d. \n", status);
	}

	// step 11: set up work-items structure
	size_t localWorkSize[1];
	size_t globalWorkSize[1];
	localWorkSize[0] = n;
	globalWorkSize[0] = rowVec * colVec;
	if (status != 0) {
		printf("Step 11: Failed to initialize global and local workspace size. Error code = %d. \n", status);
	}

	// step 12: execute kernels
	status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	if (status != 0) {
		printf("Step 12: Failed to execute the kernel. Error code = %d. \n", status);
	}

	// step 13: read buffer objects
	status = clEnqueueReadBuffer(queue, bufferC, CL_TRUE, 0, dataSizeVec, hadaVec, 0, NULL, NULL);
	if (status != 0) {
    	printf("Step 13: Failed to transfer data back to host. Error code = %d. \n", status);
	}
}

/* 'VecSum' sums the products obtained from HadamardMult() to complete the dot product */
float VecSum() {
	int i;
	float *p;
	float sum = 0.0;
	for (i = 0; i < rowVec * colVec; i++) {
		sum = sum + hadaVec[i];
	}
	p = &sum;
	return *p;
}
