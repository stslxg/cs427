#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <omp.h>

#define MAX_TEST 37786
#define MAX_CLASS 4
#define BUF_LEN 20

char* line;

int max_line_len = 1024;

static char* readline(FILE *input)
{
	int len;
	if (fgets(line, max_line_len, input) == NULL) return NULL;

	while (strrchr(line, '\n') == NULL) {
		max_line_len *= 2;
		line = (char *) realloc(line, max_line_len);
		len = (int) strlen(line);
		if (fgets(line + len, max_line_len - len, input) == NULL)
			break;
	}
	return line;
}


int main(int argc, char* argv[]) {
  if (argc <  3) {
    printf("Getting M3 results\n");
    printf("Usage: %s <M3_output_file_folder> <output_file_name> <test_file_name=test.txt>\n", argv[0]);
    printf("Reading M3 output files from <M3_output_file_folder>/[A|B|C|D].txt,\n");
    printf("outputing results to file <output_file_name>\n");
    return 0;
  }
  
  char* M3_output_file_folder = argv[1];
  char* output_file_name = argv[2];
  FILE* output_file_handle;

  char* test_file_name = "test.txt";
  if (argc >=4) test_file_name = argv[3];
  FILE* test_file_handle = fopen(test_file_name, "r");

  char M3_output_file[MAX_CLASS][BUF_LEN];
  FILE* M3_output_file_handle[MAX_CLASS];
  
  int i, j, k, l;
 
  output_file_handle = fopen(output_file_name, "w");

  for (i = 0; i < MAX_CLASS; ++i) {
    snprintf(M3_output_file[i], BUF_LEN, "%s/%c.txt", M3_output_file_folder, char('A' + i));
    M3_output_file_handle[i] = fopen(M3_output_file[i], "r");
  }

  line = (char*) malloc(sizeof(char) * max_line_len);
  int right_count = 0;
  for (l = 0; l < MAX_TEST; ++l) {
    double max = 0.0f, tmp;
    int max_i = 0;
    for (i = 0; i < MAX_CLASS; ++i) {
      fscanf(M3_output_file_handle[i], "%lf", &tmp);
      if (tmp > max) {
	max = tmp;
	max_i = i;
      }
    }
    fprintf(output_file_handle, "%c\n", char('A' + max_i));
    
    readline(test_file_handle);
    if (line[0] == char('A' + max_i)) right_count++;
  }

  printf("precision: %lf\n", (double) right_count / MAX_TEST);
  fclose(output_file_handle);

  return 0;
}
