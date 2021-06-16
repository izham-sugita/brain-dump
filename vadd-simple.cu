#include<stdio.h>

#include<cuda_runtime.h>

/*
This is a simple vector addtion program.
C = A + B
*/

/*
CUDA Kernel Device Code starts with __global__ keyword
*/
__global__ void vadd( float *A, float *B, float *C, int N)
{

  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < N){
    C[i] = A[i] + B[i];
  }
  
}

/*Host function*/
int main()
{

  //call for error code to check CUDA calls
  cudaError_t err = cudaSuccess;

  //vector length
  int N = 50000;
  size_t size = N * sizeof(float);
  printf("Vector addition of %d elements.\n", N);

  //Allocate memory for host
  float *h_A = (float *)malloc(size);
  float *h_B = (float *)malloc(size);
  float *h_C = (float *)malloc(size);
  
  //Error check

  //Initialized value for host vectors
  for(int i=0; i< N; ++i){
    h_A[i] = rand() / (float)RAND_MAX;
    h_B[i] = rand() / (float)RAND_MAX;
    h_C[i] = 0.0f; //good practice in numerical method
  }
  
  //allocate device vectors
  float *d_A = NULL;
  err = cudaMalloc( (void **)&d_A, size ); //err to check for error

  float *d_B = NULL;
  err = cudaMalloc( (void **)&d_B, size ); //err to check for error

  float *d_C = NULL;
  err = cudaMalloc( (void **)&d_C, size ); //err to check for error

  //No error check; could be fatal but let skip it for a while

  //Copy host vectors h_A, h_B to device vectors d_A, d_B
  printf("Copy input data from host memory to the CUDA device.\n");

  err = cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
  err = cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

  //Launch the vector addition kernel
  int threadsperblock = 256;
  int blockspergrid = (N + threadsperblock-1) / threadsperblock;
  printf("Launching CUDA kernel with %d blocks and %d threads.\n", blockspergrid,
	 threadsperblock);

  vadd<<<blockspergrid, threadsperblock >>>(d_A, d_B, d_C, N); //the kernel call

  err = cudaGetLastError();
  //minimal checking; at least need to know kernel success.
  if(err != cudaSuccess)
  {
    printf("Failed to launch vadd kernel, error code %s.\n",
	   cudaGetErrorString(err) );
    exit(EXIT_FAILURE);
  }

  //Copy device result vector to host result vector in host memory
  printf("Copying output data from CUDA device to host memory.\n");
  err = cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

  if(err != cudaSuccess)
    {
      printf("Failed to copy data from device, error %s.\n", cudaGetErrorString(err) );
      exit(EXIT_FAILURE);
    }

  //verify result
  for(int i=0; i<N; ++i){

    if( fabs(h_A[i] + h_B[i] - h_C[i] ) > 1.0e-5 ){
      printf("Result verification failed at element %d \n", i);
      exit(EXIT_FAILURE);
    }
  }

  printf("Kernel success!\n");

  //Free device global memory
  err = cudaFree(d_A);
  err = cudaFree(d_B);
  err = cudaFree(d_C);

  //Free host memory
  free(h_A);
  free(h_B);
  free(h_C);

  return 0;
        
}
