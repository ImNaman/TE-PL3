#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <cuda.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

__global__ void matrixMulShared(int* A, int* B, int* C, int n)
{
	__shared__ int sA[8][8];//allocate shared memory per block
	__shared__ int sB[8][8];

	//find Row and Column corresponding to a data element for each thread
	int Row = blockDim.y*blockIdx.y + threadIdx.y;
	int Col = blockDim.x*blockIdx.x + threadIdx.x;
	int Cvalue = 0;

	sA[threadIdx.y][threadIdx.x] = 0;
	sB[threadIdx.y][threadIdx.x] = 0;

	//iterate through TILEs to traverse whole WIDTH tile = blockdim.x here 8
	for (int k = 0; k<(((n - 1) / 8) + 1); k++)
	{
		// copy values of data TILE into shared memory
		if (Row<n && (threadIdx.x + (k * 8))<n)
			sA[threadIdx.y][threadIdx.x] = A[(Row*n) + threadIdx.x + (k * 8)];
		else
			sA[threadIdx.y][threadIdx.x] = 0;
		if (Col<n && (threadIdx.y + (k * 8))<n)
			sB[threadIdx.y][threadIdx.x] = B[(threadIdx.y + (k * 8))*n + Col];
		else
			sB[threadIdx.y][threadIdx.x] = 0;
		//synchronize to confirm that whole partial product corresponding to all threads of the block has been calculated
		__syncthreads();

		for (int j = 0; j<8; ++j)
			Cvalue += sA[threadIdx.y][j] * sB[j][threadIdx.x];
	}
	if (Row<n && Col<n)
		C[Row*n + Col] = Cvalue;
}
void matMulOnHost(int* A, int* B, int* C, int n)
{
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
		{
			C[i*n + j] = 0;
			for (int k = 0; k<n; k++)
				C[i*n + j] += A[i*n + k] * B[k*n + j];
		}
	return;
}
int main(int argc, char ** argv)
{
	
	int *hostA, *hostB, *hostC, *hC, *devA, *devB, *devC, n;
	cout << "Enter n: ";
	cin >> n;

	//allocate host side memory
	hostA = (int*)malloc(sizeof(int)*n*n);
	hostB = (int*)malloc(sizeof(int)*n*n);
	hostC = (int*)malloc(sizeof(int)*n*n);
	hC = (int*)malloc(sizeof(int)*n*n);


	for (int i = 0; i<n*n; i++)
		hostA[i] = rand() % 10;
	for (int i = 0; i<n*n; i++)
		hostB[i] = rand() % 10;
	

	//allocate device memory
	cudaMalloc((void **)&devA, sizeof(int)*n*n);
	cudaMalloc((void **)&devB, sizeof(int)*n*n);
	cudaMalloc((void **)&devC, sizeof(int)*n*n);

	clock_t begin = clock();

	matMulOnHost(hostA, hostB, hC, n);

	clock_t end = clock();
	double time2 = (double)(end - begin) / CLOCKS_PER_SEC;


	//copy value from host to device
	cudaMemcpy(devA, hostA, sizeof(int)*n*n, cudaMemcpyHostToDevice);
	cudaMemcpy(devB, hostB, sizeof(int)*n*n, cudaMemcpyHostToDevice);
	//calculate execution configuration
	dim3 dimBlock(8, 8, 1);
	dim3 dimGrid((n / 8) + 1, (n / 8) + 1, 1);//creating just sufficient no of blocks


	
	float time1;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	matrixMulShared << <dimGrid, dimBlock >> >(devA, devB, devC, n);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);

	//time taken in kernel call calculated
	cudaEventElapsedTime(&time1, start, stop);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	

	cudaDeviceSynchronize();
	cudaMemcpy(hostC, devC, sizeof(int)*n*n, cudaMemcpyDeviceToHost);

	cout << "\nMatrix A:\n";
	for (int i = 0, k = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++, k++)
			cout << hostA[k] << "\t";
		cout << endl;
	}
	cout << "\nMatrix B:\n";
	for (int i = 0, k = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++, k++)
			cout << hostB[k] << "\t";
		cout << endl;
	}
	cout << "\nMatrix multiplication using shared memory:\n";
	for (int i = 0, k = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++, k++)
			cout << hostC[k] << "\t";
		cout << endl;
	}
	cout << "\nMatrix multiplication on host:\n";
	for (int i = 0, k = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++, k++)
			cout << hC[k] << "\t";
		cout << endl;
	}
	cudaFree(devA);
	cudaFree(devB);
	cudaFree(devC);
	free(hostA);
	free(hostB);
	free(hostC);
	free(hC);


	
	printf("\n\nTime taken by cuda is %f (ms)\n", time1);
	time2= time2 * 1000;
	printf("\n\nTime taken by host is %f (ms)\n", time2);
	return 0;
}