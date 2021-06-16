#include<stdio.h>

#include<cuda.h>
#include<cuda_runtime.h>

//vector addition kernel
__global__ void vadd(float *a, float *b, float *c, int N)
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if(i < N){
    c[i] = a[i] + b[i];
  }
}

int main()
{

  int N = 50000; //vector elements
  cudaError_t err = cudaSuccess;
  
  //Allocate memory space using unified memory
  float *va, *vb, *vc;

  //pick one for error checking
  err = cudaMallocManaged( &va, N*sizeof(float) );
  if(err != cudaSuccess){
    printf("Failed to allocate using unified memory, error code %s. \n",
	   cudaGetErrorString(err) );
    exit(EXIT_FAILURE);
  }
  
  err = cudaMallocManaged( &vb, N*sizeof(float) );
 if(err != cudaSuccess){
    printf("Failed to allocate using unified memory, error code %s. \n",
	   cudaGetErrorString(err) );
    exit(EXIT_FAILURE);
  }
  
  cudaMallocManaged( &vc, N*sizeof(float) );

  //Initiate value for each vector
  for(int i=0; i<N; ++i){
    va[i] = rand() / (float)RAND_MAX;
    vb[i] = rand() / (float)RAND_MAX;
    vc[i] = 0.0f;
  }

  //Launching kernel
  int threads = 256;
  int blocks = (N + threads - 1) / threads;
  printf("Blocks: %d, Threads: %d\n", blocks, threads);
  vadd<<<blocks, threads>>>(va, vb, vc, N);

  //Need to synchronize for data transfer
  cudaDeviceSynchronize();
  
  err = cudaGetLastError();
  if(err != cudaSuccess){
    printf("Failed to launch kernel, error code %s\n", cudaGetErrorString(err) );
  }
  
  //Checking answer
  float eps;
  for(int i=0; i<N; ++i){
    eps = va[i] + vb[i] - vc[i];
    if (eps > 1.0e-5){
      printf("Result verification failed at element %d \n", i);
      exit(EXIT_FAILURE);
    }
  }

  printf("Kernel and unified memory test success!\n");

  //Free memory; only required the use of cudaFree
  cudaFree(va);
  cudaFree(vb);
  cudaFree(vc);
  
  
}

