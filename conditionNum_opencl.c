/* Calculate the condition number of a random symmetric diagonally matrix using OpenCL */

# include <stdio.h>
# include <math.h>
# include <stdlib.h> 
# include <time.h> 
# include <CL/cl.h> 

// declare global variables
int n;

float *A = NULL;
float *B = NULL;
float *C = NULL;
float *Chat = NULL;
float *X = NULL;
float *Xhat = NULL;

size_t dataSizeMat, dataSizeVec;

int rowMat = 0, colMat = 0, rowVec = 0, colVec = 0;

cl_int status, powerStatus, iPowerStatus;

cl_uint numPlatforms = 0, numDevices = 0;
cl_platform_id *platforms = NULL;
cl_device_id *devices = NULL;

cl_context powerContext = NULL;
cl_context iPowerContext = NULL;

cl_command_queue powerQueue = NULL;
cl_command_queue iPowerQueue = NULL;

cl_program powerProgram = NULL;
cl_program iPowerProgram = NULL;

cl_kernel powerKernel = NULL;
cl_kernel iPowerKernel = NULL;

cl_mem bufferA, bufferB, bufferC, bufferX;

// declare functions
int InitializeMatVec();
int MatVecMult(float *P);
float VecMult(float *P, float *Q);
float Jacobi(float *P, float *Q);

// set up kernel for matrix-vector multiplication
const char *Power =
"__kernel                                                   			\n"
"void MatVecMult(__global float *outputC,								\n"
"            int rowMat,                                      			\n"
"            int colVec,                                      			\n"
"            __global float *inputA,                        			\n"
"            __global float *inputB)                       				\n"
"{                                                          			\n"
"   int tid = get_global_id(0);					            			\n"
"   int j = tid / rowMat;                                     			\n"
"   int i = tid % rowMat;  // modulo arithmetic               			\n"
"   float sum = 0.0f;                                      				\n"
"   int k;                												\n"
"   for (k = 0; k < rowMat; k++) {                            			\n"
"      sum += inputA[i + k * rowMat] * inputB[k + j * colVec];			\n"
"   }                                                       			\n"
"   outputC[i + j * rowMat] = sum;                            			\n"
"}                                                          			\n";

// set up kernel for jacobi iterative method
const char *iPower =
"__kernel                                                   			\n"
"void Jacobi(__global float *outputX,									\n"
"            __global float *inputQ,                        			\n"
"            __global float *inputA,                        			\n"
"            __global float *inputP,                        			\n"
"			 int rowVec,												\n"
"			 int colVec)												\n"
"{                                                          			\n"
"   float sum, tol = 0.00005, error = 10.0 * tol;     					\n"
"	float sqNormP = 0.0, sqNormX = 0.0, normP, normX;					\n"
"	int maxIter = 200, iter = 0;										\n"
"	int i = get_global_id(0);											\n"
"	int j = i / rowVec;													\n"
"	while (error > tol && iter < maxIter) {								\n"
"		for (i = 0; i < rowVec * colVec; i++) {							\n"
"			sum = 0.0;													\n"
"			for (j = 0; j < rowVec * colVec; j++) {						\n"
"				if (j != i) {											\n"
"					sum += inputA[i + j * rowVec] * inputP[j];			\n"
"				}														\n"
"			}															\n"
"			outputX[i] = (inputQ[i] - sum) / inputA[i + i * rowVec];	\n"
"		}																\n"
" 		for (i = 0; i < rowVec * colVec; i++) {							\n"  
"			sqNormP = sqNormP + inputP[i] * inputP[i];					\n"
"		}																\n"
"		normP = sqrt(sqNormP);											\n"
"		for (i = 0; i < rowVec * colVec; i++) {							\n"
"			sqNormX = sqNormX + outputX[i] * outputX[i];				\n"
"		}																\n"
"		normX = sqrt(sqNormX);											\n"
"		error = fabs((normX - normP) / normX);							\n"
"		for (i = 0; i < rowVec * colVec; i++) {							\n"
"			inputP[i] = outputX[i];										\n"
"		}																\n"
"		iter += 1;														\n"
"	}																	\n"
"}																		\n";

int main() {
	clock_t start, stop;

	float lambda0 = 1.0, largeLambda, smallLambda;
	float tol = 0.00005, error = 10.0 * tol;
	float normSq, norm;
	int maxIter = 200, iter = 0, i;
	
	InitializeMatVec();

	for (i = 0; i < rowMat * colMat; i++) {
    	printf("i = %d \t A = %f \n", i, A[i]);  // column-wise
	}

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

	// step 3: create context for matrix-vector multiplication
	powerContext = clCreateContext(NULL, numDevices, devices, NULL, NULL, &powerStatus);
	if (powerStatus != 0) {
		printf("Step 3 kernel Power. Failed to create the context. Error code = %d. \n", powerStatus);
	}

	// step 3: create context for Jacobi iterative method
	iPowerContext = clCreateContext(NULL, numDevices, devices, NULL, NULL, &iPowerStatus);
	if (iPowerStatus != 0) {
		printf("Step 3 kernel iPower. Failed to create the context. Error code = %d. \n", iPowerStatus);
	}

  	// step 4: set up command queue for matrix-vector multiplication
	powerQueue = clCreateCommandQueue(powerContext, devices[0], 0, &powerStatus);
	if (powerStatus != 0) {
		printf("Step 4 kernel Power. Failed to set up the command queue. Error code = %d. \n", powerStatus);
	}

	// step 4: set up command queue for Jacobi iterative method
	iPowerQueue = clCreateCommandQueue(iPowerContext, devices[0], 0, &iPowerStatus);
	if (iPowerStatus != 0) {
		printf("Step 4 kernel iPower. Failed to set up the command queue. Error code = %d. \n", iPowerStatus);
	}

	start = clock();

	/* CALCULATE LARGEST EIGENVALUE */	
	
	MatVecMult(B);  // obtain C, where C = A * B		
	while (error > tol && iter < maxIter) {
		normSq = VecMult(C, C);	
		norm = sqrt(normSq);
		for (i = 0; i < rowVec * colVec; i++) {
			Chat[i] = C[i] / norm;  // normalize C
		}

		// obtain Rayleigh quotient tranpose(Chat) * A * Chat
		MatVecMult(Chat);  // 1st part of Rayleigh. Also updates old C with new C.
		largeLambda = VecMult(Chat, C);  // continue with 2nd part

		error = fabs((largeLambda - lambda0) / largeLambda);  // relative error
		lambda0 = largeLambda;  // update old eigenvalue with new one
		iter += 1;
	}

	// reset variables for next calculation
	lambda0 = 1.0, error = 10.0 * tol, maxIter = 200, iter = 0, normSq = 0.0, norm = 0.0;

	/* CALCULATE SMALLEST EIGENVALUE */

	Jacobi(B, B);  // Solve A * B = B. The solution is labeled X.
	while (error > tol && iter < maxIter) {
		normSq = VecMult(X, X);	
		norm = sqrt(normSq);
		for (i = 0; i < rowVec * colVec; i++) {
			Xhat[i] = X[i] / norm;  // normalize X
		}
							
		// obtain Rayleigh quotient tranpose(Xhat) * A * Xhat
		MatVecMult(Xhat);  // 1st part of Rayleigh: C = transpose(Xhat) * A
		smallLambda = VecMult(C, Xhat);  // 2nd part of Rayleigh
				
		error = fabs((smallLambda - lambda0) / smallLambda);  // relative error
		lambda0 = smallLambda;  // update old smallest eigenvalue with new one
		Jacobi(X, Xhat);  // update old solution with new one
		iter += 1;
	}

	stop = clock();

	printf("The largest eigenvalue is %f \n", largeLambda);
	printf("The smallest eigenvalue is %f \n", smallLambda);
	printf("The condition number of the matrix is %f \n", fabs(largeLambda / smallLambda));
	printf("OpenCL CPU elapsed time = %f seconds. \n", (double)(stop - start) / CLOCKS_PER_SEC);
 
  	// step 14: free used memory
  	clReleaseKernel(powerKernel);
	clReleaseKernel(iPowerKernel);

	clReleaseProgram(powerProgram);
	clReleaseProgram(iPowerProgram);

	clReleaseCommandQueue(powerQueue);
	clReleaseCommandQueue(iPowerQueue);

	clReleaseMemObject(bufferA);
	clReleaseMemObject(bufferB);
	clReleaseMemObject(bufferC);
	clReleaseMemObject(bufferX);

	clReleaseContext(powerContext);
	clReleaseContext(iPowerContext);

	free(A);
	free(B);
	free(C);
	free(Chat);
	free(X);
	free(Xhat);
	free(platforms);
	free(devices);

	if (status != 0) {
		printf("Step 13: Failed to deallocate memory. Error code = %d. \n", status);
	}
}

// 'InitializeMatVec' initializes matrix A and vector B
int InitializeMatVec() {
	n = 3;  // size of matrix and vector
	rowMat = n, colMat = n;  // row and column size of matrix A
	rowVec = colMat, colVec = 1;  // row and column size of vectors

	// set the size of the storage and setup the storage for the matrices
	dataSizeMat = colMat * rowMat * sizeof(float);
	dataSizeVec = colVec * rowVec * sizeof(float);
	
	A = (float *)malloc(dataSizeMat);
	B = (float *)malloc(dataSizeVec);
	C = (float *)malloc(dataSizeVec);
	Chat = (float *)malloc(dataSizeVec);	
	X = (float *)malloc(dataSizeVec);
	Xhat = (float *)malloc(dataSizeVec);
		
	// generate a random symmetric diagonally dominant matrix A
	int i, j, sum[i], offDiagSum[i];
	srand(time(NULL));  // randomize seed
	for (i = 0; i < rowMat; i++) {
		sum[i] = 0;
        offDiagSum[i] = 0;
        for (j = 0; j < colMat; j++) {
            A[i * colMat + j] = rand() % 100 + 1;  // random number between [1, 100]
            if (j <= i) {  // below diagonal
                A[i * colMat + j] = A[j * colMat + i];  // obtain transpose(A) = A
            }
            sum[i] += A[i * colMat + j];  // sum of each row
            if (j != i) {
                offDiagSum[i] += A[i * colMat + j];  // sum of off-diagonal entries in each row
            }
            // replace diagonal entry with random number between [offDiagSum, sum] for diagonal dominance
            A[i * colMat + i] = rand() % (sum[i] + 1 - offDiagSum[i]) + offDiagSum[i];
        }
        if (rowMat == 2) {
        	A[0] = A[3];  // preserve symmetry for n = 2 case        
    	}
    }
    
    for (i = 0; i < rowVec * colVec; i++) {
		B[i] = 2.0;  // initial solution for Jacobi and power method
	}
}

// 'MatVecMult' multiplies matrix 'A' with vector 'B' to obtain resultant vector 'C'
int MatVecMult(float *P) {
	// step 5: create buffer objects
	bufferA = clCreateBuffer(powerContext, CL_MEM_READ_ONLY, dataSizeMat, NULL, &powerStatus);
	bufferB = clCreateBuffer(powerContext, CL_MEM_READ_WRITE, dataSizeVec, NULL, &powerStatus);
	bufferC = clCreateBuffer(powerContext, CL_MEM_READ_WRITE, dataSizeVec, NULL, &powerStatus);
	if (powerStatus != 0) {
		printf("Step 5 kernel Power. Failed to create memory buffers. Error code = %d. \n", powerStatus);
	}

	// step 6: write buffer objects
	powerStatus = clEnqueueWriteBuffer(powerQueue, bufferA, CL_FALSE, 0, dataSizeMat, A, 0, NULL, NULL);
	powerStatus = clEnqueueWriteBuffer(powerQueue, bufferB, CL_FALSE, 0, dataSizeVec, P, 0, NULL, NULL);
	if (powerStatus != 0) {
		printf("Step 6 kernel Power. Failed to copy data to memory buffers. Error code = %d. \n", powerStatus);
	}

	// step 7: create program objects	
	powerProgram = clCreateProgramWithSource(powerContext, 1, (const char**)&Power, NULL, &powerStatus);
	if (powerStatus != 0) {
		printf("Step 7 kernel Power. Failed to create program objects. Error code = %d. \n", powerStatus);
	}
 
	// step 8: build program executables
	powerStatus = clBuildProgram(powerProgram, numDevices, devices, NULL, NULL, NULL);
	if (powerStatus != 0) {
		printf("Step 8 kernel Power. Failed to build program executables. Error code = %d. \n", powerStatus);
	}

	// step 9: create kernel objects
	powerKernel = clCreateKernel(powerProgram, "MatVecMult", &powerStatus);
	if (powerStatus != 0) {
		printf("Step 9 kernel Power. Failed to create kernel objects. Error code = %d. \n", powerStatus);
	}

	// step 10: set kernel arguments
	clSetKernelArg(powerKernel, 0, sizeof(cl_mem), &bufferC);
	clSetKernelArg(powerKernel, 1, sizeof(int), &rowMat);
	clSetKernelArg(powerKernel, 2, sizeof(int), &colVec);
	clSetKernelArg(powerKernel, 3, sizeof(cl_mem), &bufferA);
	clSetKernelArg(powerKernel, 4, sizeof(cl_mem), &bufferB);
	if (powerStatus != 0) {
		printf("Step 10 kernel Power. Failed to set kernel arguments. Error code = %d. \n", powerStatus);
	}

	// step 11: set up work-items structure
	size_t localWorkSize[1];
	size_t globalWorkSize[1];
	localWorkSize[0] = n;
	globalWorkSize[0] = rowVec * colVec;
	if (powerStatus != 0) {
		printf("Step 11 kernel Power. Failed to initialize global and local workspace size. Error code = %d. \n", powerStatus);
	}

	// step 12: execute kernels
	powerStatus = clEnqueueNDRangeKernel(powerQueue, powerKernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	if (powerStatus != 0) {
		printf("Step 12 kernel Power. Failed to execute the kernel. Error code = %d. \n", powerStatus);
	}

	// step 13: read buffer objects
	powerStatus = clEnqueueReadBuffer(powerQueue, bufferC, CL_TRUE, 0, dataSizeVec, C, 0, NULL, NULL);
	if (powerStatus != 0) {
    	printf("Step 13 kernel Power. Failed to transfer data back to host. Error code = %d. \n", powerStatus);
	}
}

// 'Jacobi' solves AP = Q by Jacobi iterative method. The solution is labeled X.
float Jacobi(float *P, float *Q) {
	// step 5: create buffer objects
	bufferA = clCreateBuffer(iPowerContext, CL_MEM_READ_ONLY, dataSizeMat, NULL, &iPowerStatus);
	bufferB = clCreateBuffer(iPowerContext, CL_MEM_READ_WRITE, dataSizeVec, NULL, &iPowerStatus);
	bufferC = clCreateBuffer(iPowerContext, CL_MEM_READ_WRITE, dataSizeVec, NULL, &iPowerStatus);
	bufferX = clCreateBuffer(iPowerContext, CL_MEM_READ_WRITE, dataSizeVec, NULL, &iPowerStatus);
	if (iPowerStatus != 0) {
		printf("Step 5 kernel iPower. Failed to create memory buffers. Error code = %d. \n", iPowerStatus);
	}

	// step 6: write buffer objects
	iPowerStatus = clEnqueueWriteBuffer(iPowerQueue, bufferA, CL_FALSE, 0, dataSizeMat, A, 0, NULL, NULL);
	iPowerStatus = clEnqueueWriteBuffer(iPowerQueue, bufferB, CL_FALSE, 0, dataSizeVec, P, 0, NULL, NULL);
	iPowerStatus = clEnqueueWriteBuffer(iPowerQueue, bufferC, CL_FALSE, 0, dataSizeVec, Q, 0, NULL, NULL);
	if (iPowerStatus != 0) {
		printf("Step 6 kernel iPower. Failed to copy data to memory buffers. Error code = %d. \n", iPowerStatus);
	}

	// step 7: create program objects	
	iPowerProgram = clCreateProgramWithSource(iPowerContext, 1, (const char**)&iPower, NULL, &iPowerStatus);
	if (iPowerStatus != 0) {
		printf("Step 7 kernel iPower. Failed to create program objects. Error code = %d. \n", iPowerStatus);
	}
 
	// step 8: build program executables
	iPowerStatus = clBuildProgram(iPowerProgram, numDevices, devices, NULL, NULL, NULL);
	if (iPowerStatus != 0) {
		printf("Step 8 kernel iPower. Failed to build program executables. Error code = %d. \n", iPowerStatus);
	}

	// step 9: create kernel objects
	iPowerKernel = clCreateKernel(iPowerProgram, "Jacobi", &iPowerStatus);
	if (iPowerStatus != 0) {
		printf("Step 9 kernel iPower. Failed to create kernel objects. Error code = %d. \n", iPowerStatus);
	}

	// step 10: set kernel arguments
	clSetKernelArg(iPowerKernel, 0, sizeof(cl_mem), &bufferX);
	clSetKernelArg(iPowerKernel, 1, sizeof(cl_mem), &bufferC);
	clSetKernelArg(iPowerKernel, 2, sizeof(cl_mem), &bufferA);
	clSetKernelArg(iPowerKernel, 3, sizeof(cl_mem), &bufferB);
	clSetKernelArg(iPowerKernel, 4, sizeof(int), &rowVec);
	clSetKernelArg(iPowerKernel, 5, sizeof(int), &colVec);
	if (iPowerStatus != 0) {
		printf("Step 10 kernel iPower. Failed to set kernel arguments. Error code = %d. \n", iPowerStatus);
	}

	// step 11: set up work-items structure
	size_t localWorkSize[1];
	size_t globalWorkSize[1];
	localWorkSize[0] = n;
	globalWorkSize[0] = rowVec * colVec;
	if (iPowerStatus != 0) {
		printf("Step 11 kernel iPower. Failed to initialize global and local workspace size. Error code = %d. \n", iPowerStatus);
	}

	// step 12: execute kernels
	iPowerStatus = clEnqueueNDRangeKernel(iPowerQueue, iPowerKernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	if (iPowerStatus != 0) {
		printf("Step 12 kernel iPower. Failed to execute the kernel. Error code = %d. \n", iPowerStatus);
	}

	// step 13: read buffer objects
	iPowerStatus = clEnqueueReadBuffer(iPowerQueue, bufferX, CL_TRUE, 0, dataSizeVec, X, 0, NULL, NULL);
	if (iPowerStatus != 0) {
    	printf("Step 13 kernel iPower. Failed to transfer data back to host. Error code = %d. \n", iPowerStatus);
	}
}

// 'VecMult' multiplies two vectors 'P' and 'Q'
float VecMult(float *P, float *Q) {
	int i;
	float *p;
	float sum = 0.0;
	for (i = 0; i < rowVec * colVec; i++) {
		sum = sum + P[i] * Q[i];
	}
	p = &sum;
	return *p;
}
