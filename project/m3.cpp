#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <omp.h>

#define MAX_M 6
#define MAX_N 20
#define MAX_CLASS 4
#define BUF_LEN 50
#define MAX_TEST 37786
#define MAX_THREAD_NUM 20

double threshold = 0.85f;

int main(int argc, char* argv[]) {
  if (argc <  4) {
    printf("A M3 Program for SVMlinear and KNN\n");
    printf("Usage: %s <predict_output_file_folder> <output_file_folder> [A|B|C|D] <M=6> <N=20> <threshold=0.85>\n", argv[0]);
    printf("Reading prediction output files from <predict_output_file_folder>/[A|B|C|D]/{positive numbers}-{negative numbers}.txt,\n");
    printf("outputing results to <output_file_folder>/[A|B|C|D].txt.\n");
    return 0;
  }
  
  char* predict_output_file_folder = argv[1];
  char* output_file_folder = argv[2];
  int M = 6, N = 20;
  if (argc >= 5) M = atoi(argv[4]);
  if (argc >= 6) N = atoi(argv[5]);
  if (argc >= 7) threshold = atof(argv[6]);
  char sub_class = argv[3][0];

  char predict_output_file[M][N][BUF_LEN];
  char output_file[BUF_LEN];
 
  FILE* predict_output_file_handle[M][N];
  FILE* output_file_handle;
  
  double _max[MAX_TEST], _min[M][MAX_TEST], tmp;

  int i, j, k, l, tid, ttid;
 
  snprintf(output_file, BUF_LEN, "%s/%c.txt", output_file_folder, sub_class);
  output_file_handle = fopen(output_file, "w");

#pragma omp parallel for num_threads(MAX_THREAD_NUM) schedule(dynamic) default(shared) private(l)
  for (l = 0; l < MAX_TEST; ++l) {
      _max[l] = 0.0f;
  }

#pragma omp parallel for num_threads(MAX_THREAD_NUM) schedule(dynamic) default(shared) private(i, l)
  for (i = 0; i < M; ++i) {
    for (l = 0; l < MAX_TEST; ++l) {
      _min[i][l] = 1.0f;
    }
  }

  //fprintf(stderr, "ok\n");
  omp_set_nested(1);
#pragma omp parallel for num_threads(M) schedule(static) default(shared) private(i, j, l, tmp)
  for (i = 0; i < M; ++i) {
#pragma omp parallel for num_threads(N) schedule(static) default(shared) private(j, l, tmp)
    for (j = 0; j < N; ++j) {
      snprintf(predict_output_file[i][j], BUF_LEN, "%s/%c/%d-%d.txt", predict_output_file_folder, sub_class, i, j);
      predict_output_file_handle[i][j] = fopen(predict_output_file[i][j], "r");

      //fprintf(stderr, "ok1 %d %d\n", i, j);
      for (l = 0; l < MAX_TEST; ++l) {
	fscanf(predict_output_file_handle[i][j], "%lf", &tmp);
#pragma omp critical(crimin)
	{
	  _min[i][l] = std::min(tmp, _min[i][l]);
	}
      }
      
      //fprintf(stderr, "ok2 %d %d\n", i, j);      
      fclose(predict_output_file_handle[i][j]);
    }
#pragma omp parallel for num_threads(MAX_THREAD_NUM) schedule(dynamic) default(shared) private(l)
    for (l = 0; l < MAX_TEST; ++l) {
#pragma omp critical(crimax)
      {
	_max[l] = std::max(_min[i][l], _max[l]);
      }
    }
  }
  
  for (l = 0; l < MAX_TEST; ++l) {
    fprintf(output_file_handle, "%lf\n", _max[l]);
  }

  fclose(output_file_handle);

  return 0;
}
