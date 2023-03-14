#include <stdio.h>
#include <omp.h>

template<typename T>  // oh no! template is a C++ feature, not in ANSI C !
void MatrixMultiplication(T *A, T *B, T *C, int n, int m, int l) {
  int i, j, k;

#define I_A(i,j) ((i) * n + (j))
#define I_B(i,j) ((i) * m + (j))
#define I_C(i,j) ((i) * n + (j))
#define N 1000

#pragma omp parallel shared(A, B, C) private(i, j, k) num_threads(N) 
  {
#pragma omp for
    for (i = 0; i < n; ++i)
      for (j = 0; j < l; ++j)
	C[I_C(i,j)] = 0;

#pragma omp for
    for (i = 0; i < n; ++i)
      for (j = 0; j < l; ++j)
	for (k = 0; k < m; ++k)
	  C[I_C(i,j)] += A[I_A(i,k)] * B[I_B(k,j)];
  }
}

long long a[1000], b[1000], c[1000];

#define l_a 10
#define l_b 20
#define l_c 5
#define INDEX_A(i,j) (i * l_a + j)
#define INDEX_B(i,j) (i * l_b + j)
#define INDEX_C(i,j) (i * l_a + j)

void input() {
  int i, j;
  for (i = 0; i < l_a; ++i)
    for (j = 0; j < l_b; ++j)
      a[INDEX_A(i,j)] = i * l_a + j;

  for (i = 0; i < l_b; ++i)
    for (j = 0; j < l_c; ++j)
      b[INDEX_B(i,j)] = i * l_b + j;
}

void output() {
  int i, j;
  for (i = 0; i < l_a; ++i) {
    for (j = 0; j < l_c; ++j)
      printf("%lld ", c[INDEX_C(i,j)]);
    printf("\n");
  }
}

int main() {
  input();
  MatrixMultiplication(a, b, c, l_a, l_b, l_c);
  output();
  return 0;
}
