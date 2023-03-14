#include <stdio.h>
#include "math.h"
#include "cuda.h"
#include "cuda_runtime.h"

#define M 500
#define N 1000
#define TILE_WIDTH 16
const float sigma = 100.0f;

float x[M][N];
float k[M][M];

__global__ void test_kernel(float *dK) {
#define IDX_k(i,j) ((i) * M + (j))

  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;

  if (i < M && j < M)
    dK[IDX_k(i,j)] = exp(dK[IDX_k(i,j)]);
}

void init() {
  int i,j;
  for(i = 0; i < M; ++i)
    for(j = 0; j < N; ++j)
      x[i][j] = (i + j) / 2000.0f;
}

void work() {
  int i,j,ii;
  for(i = 0; i < M; ++i)
    for(j = 0; j < M; ++j) {
      k[i][j] = 0;
      for (ii = 0; ii < N; ++ii)
	k[i][j] += (x[i][ii] - x[j][ii]) * (x[i][ii] - x[j][ii]);
      k[i][j] = - k[i][j] / (2.0 * sigma * sigma);
    }

  cudaSetDevice(0);
  float *dK = NULL;
  cudaMalloc((void**) &dK, sizeof(float) * M * M);
  cudaMemcpy(dK, k, sizeof(float) * M * M, cudaMemcpyHostToDevice);

  dim3 DimGrid((M + TILE_WIDTH - 1) / TILE_WIDTH, (M + TILE_WIDTH - 1) / TILE_WIDTH);
  dim3 DimBlock(TILE_WIDTH, TILE_WIDTH);
  
  test_kernel<<<DimGrid, DimBlock>>>(dK);
  
  cudaMemcpy(k, dK, sizeof(float) * M * M, cudaMemcpyDeviceToHost);
  cudaFree(dK);
}

void output() {
  int i,j;
  for(i = 0; i < M; ++i) {
    for (j = 0; j < M; ++j)
      printf("%f ", k[i][j]);
    printf("\n");
  }
}

int main() {
  init();
  work();
  output();
  return 0;
}
