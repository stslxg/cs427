#include <stdio.h>
#include "math.h"
#include "cuda.h"
#include "cuda_runtime.h"

#define M 5000
#define N 10000
#define TILE_WIDTH 8
const float sigma = 100.0f;

float x[M][N];
float k[M][M];

__global__ void RBFkernel(float *dX, float *dK) {

#define IDX_k(i,j) ((i) * M + (j))
#define IDX(i,j) ((i) * N + (j))

  __shared__ float TILE_i[TILE_WIDTH][TILE_WIDTH];
  __shared__ float TILE_j[TILE_WIDTH][TILE_WIDTH];

  float value = 0;
  float value1 = 0;
  
  int bi = blockIdx.x * blockDim.x;
  int bj = blockIdx.y * blockDim.y;
  int ti = threadIdx.x;
  int tj = threadIdx.y;
  
  int i = bi + ti;
  int j = bj + tj;

  int m,k;
  for (m = 0; m < (N + TILE_WIDTH - 1) / TILE_WIDTH; ++m) {
    if (bi + ti < M && m * TILE_WIDTH + tj < N)
      TILE_i[ti][tj] = dX[IDX(bi + ti, m * TILE_WIDTH + tj)];
    if (bj + ti < M && m * TILE_WIDTH + tj < N)
      TILE_j[ti][tj] = dX[IDX(bj + ti, m * TILE_WIDTH + tj)];
    __syncthreads();
    
    if (i < M && j < M)
      for (k = 0; k < TILE_WIDTH; ++k) {
	if (m * TILE_WIDTH + k < N)
	  value += (TILE_i[ti][k] - TILE_j[tj][k]) * (TILE_i[ti][k] - TILE_j[tj][k]);
	/*	if (m * TILE_WIDTH + k + TILE_WIDTH / 2 < N) 
		value1 += (TILE_i[ti][k + TILE_WIDTH / 2] - TILE_j[tj][k + TILE_WIDTH / 2]) * (TILE_i[ti][k + TILE_WIDTH / 2] - TILE_j[tj][k + TILE_WIDTH / 2]); */
      }
    __syncthreads();
  }

  if (i < M && j < M) {
    dK[IDX_k(i,j)] = exp(- (value + value1) / (2 * sigma * sigma));
  }
}

void init() {
  int i,j;
  for(i = 0; i < M; ++i)
    for(j = 0; j < N; ++j)
      x[i][j] = (i + j) / 20000.0f;
}

void calculateRBFkernel() {
  cudaSetDevice(0);

  float *dX = NULL;
  float *dK = NULL;
  
  cudaMalloc((void**) &dX, sizeof(float) * M * N);
  cudaMalloc((void**) &dK, sizeof(float) * M * M);
  cudaMemcpy(dX, x, sizeof(float) * M * N, cudaMemcpyHostToDevice);

  dim3 DimGrid((M + TILE_WIDTH - 1) / TILE_WIDTH, (M + TILE_WIDTH - 1) / TILE_WIDTH);
  dim3 DimBlock(TILE_WIDTH, TILE_WIDTH);

  RBFkernel<<<DimGrid, DimBlock>>>(dX, dK);

  cudaMemcpy(k, dK, sizeof(float) * M * M, cudaMemcpyDeviceToHost);
  cudaFree(dX);
  cudaFree(dK);
}

void output() {
  /*int i,j;
      for(i = 0; i < M; ++i) {
    for (j = 0; j < M; ++j)
      printf("%f ", k[i][j]);
    printf("\n");
    }*/
}

int main() {
  init();
  calculateRBFkernel();
  output();
  return 0;
}
