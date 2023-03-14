#include <stdio.h>
#include <omp.h>

template<typename T>  // oh no! template is a C++ feature, not in ANSI C !
T VectorSum(T *v, int n) {
  T sum;
  int i;

#define N 10
  omp_set_num_threads(N);
#pragma omp parallel for num_threads(N) shared(v) private(i) reduction(+: sum) schedule(static, 1)
  for (i = 0; i < n; ++i)
    sum += v[i];

  return sum;
}

long long v[1000];
int n;
long long sum;

void input() {
  int i;
  scanf("%d", &n);
  for (i = 0; i < n; ++i) scanf("%lld", v+i);
}

void output() {
  printf("%lld\n", sum);
}

int main() {
  input();
  sum = VectorSum(v, n);
  output();
  return 0;
}
