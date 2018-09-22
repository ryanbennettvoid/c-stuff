
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

  cudaError_t err = cudaSuccess;

  // allocate arrays on GPU,
  // cuda takes ownership of device pointers
  err = cudaMalloc( (void **) &deviceInput, sizeof(int)*N );
  if ( err != cudaSuccess )
  {
    fprintf( stderr, "could not allocate on GPU\n" );
  }

  err = cudaMalloc( (void **) &deviceOutput, sizeof(int)*N );
  if ( err != cudaSuccess )
  {
    fprintf( stderr, "could not allocate on GPU\n" );
  }

  // set input values
  for ( int i = 0; i < N; i++ )
    hostInput[i] = i;

  // copy input to GPU
  err = cudaMemcpy( deviceInput, hostInput, sizeof(int)*N, cudaMemcpyHostToDevice );
  if ( err != cudaSuccess )
  {
    fprintf( stderr, "could not copy from hostInput to deviceInput\n" );
  }

  // run GPU code on N threads- one per element
  fn<<<N, 1>>>( deviceInput, deviceOutput );

  // copy output from GPU to CPU
  err = cudaMemcpy( hostOutput, deviceOutput, sizeof(int)*N, cudaMemcpyDeviceToHost );
  if ( err != cudaSuccess )
  {
    fprintf( stderr, "could not copy from deviceOutput to hostOutput\n" );
  }

  for ( int i = 0; i < N; i++ )
  {
    printf( "%d\n", hostOutput[i] );
  }

  err = cudaFree( deviceInput );
  if ( err != cudaSuccess )
  {
    fprintf( stderr, "could not free deviceInput from GPU: %s\n", cudaGetErrorString(err) );
  }

  err = cudaFree( deviceOutput );
  if ( err != cudaSuccess )
  {
    fprintf( stderr, "could not free deviceOutput from GPU: %s\n", cudaGetErrorString(err) );
  }

  return 0;
}