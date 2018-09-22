
// reference: https://gist.github.com/dpiponi/1502434

// compile: nvcc ./main.cu -o cuda

// NOTES
// - sudo apt-get install nvidia-cuda-toolkit
// - must use .cu suffix to compile properly
// - must have nVidia GPU with CUDA capabilities

#define N 1000

#include <stdio.h>

__global__
void fn( int *input, int *output )
{
  int i = blockIdx.x;
  if ( i < N )
  {
    output[i] = input[i] * 2;
  }
}

int main()
{

  int hostInput[N], hostOutput[N];
  int *deviceInput, *deviceOutput;

  // allocate arrays on GPU,
  // cuda takes ownership of device pointers
  cudaMalloc( (void **) &deviceInput, sizeof(int)*N );
  cudaMalloc( (void **) &deviceOutput, sizeof(int)*N );

  // set input values
  for ( int i = 0; i < N; i++ )
    hostInput[i] = i;

  // copy input to GPU
  cudaMemcpy( deviceInput, hostInput, sizeof(int)*N, cudaMemcpyHostToDevice );

  // run GPU code on N threads- one per element
  fn<<<N, 1>>>( deviceInput, deviceOutput );

  // copy output from GPU to CPU
  cudaMemcpy( hostOutput, deviceOutput, sizeof(int)*N, cudaMemcpyDeviceToHost );

  for ( int i = 0; i < N; i++ )
  {
    printf( "%d\n", hostOutput[i] );
  }

  cudaFree( deviceInput );
  cudaFree( deviceOutput );

  return 0;
}