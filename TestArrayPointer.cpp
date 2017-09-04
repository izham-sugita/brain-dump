#include<cstdlib>
#include<cstdio>

#define N 4

using namespace std;

int main()
{

  //set during runtime
  int M=4;
  
  float* A[N]; //combining static and dynamic array definition

  for(int i=0; i<N; ++i){
    A[i] = new float[M];
  }

  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      A[i][j] = 1.0;
      printf("A[%d][%d] = %f\n", i, j, A[i][j]);
    }
  }

  //std way to define dynamic array using pointer
  float** B;
  B = new float*[N];
  for(int i=0; i<N; ++i){
    B[i] = new float[M];
  }

  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      B[i][j] = 1.0;
      printf("B[%d][%d] = %f\n", i, j, B[i][j]);
    }
  }


  //creating array of pointers
  float* A3D[N][N];

  for(int i=0; i<N; ++i){
    for(int j=0; j<N; ++j){
      A3D[i][j] = new float[N];
    }
  }

  printf("\n");
  for(int i=0; i<N; ++i){
    for(int j=0; j<N; ++j){
      for(int k=0; k<N; ++k){
	A3D[i][j][k] = 2.0;
	printf("A3D[%d][%d][%d] = %.4f \t", i,j,k, A3D[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }

  
}
