#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max_line_len = 1024;
static char *line1 = NULL;
static char *line2 = NULL;

static char* readline(FILE *input)
{
	int len;
	if (fgets(line1, max_line_len, input) == NULL) return NULL;

	while (strrchr(line1, '\n') == NULL) {
		max_line_len *= 2;
		line1 = (char *) realloc(line1, max_line_len);
		len = (int) strlen(line1);
		if (fgets(line1 + len, max_line_len - len, input) == NULL)
			break;
	}
	return line1;
}

int main(int argc, char *argv[])
{
  FILE *input, *output, *input2;
	char replace[8];
	char *pch;
	int tmp, count = 0, right_count = 0;
	int len;

	input = fopen(argv[1], "r");
	input2 = fopen(argv[2], "r");
	line1 = (char *) malloc(max_line_len*sizeof(char));
	while (readline(input) != NULL) {
	  fscanf(input2, "%d", &tmp);
	  count++;
	  if (line1[0] == '1' && tmp == 1 || line1[0] == '0' && tmp == 0) right_count++;
	}

	printf("precision: %f\n", float(right_count) / float(count));
	free(line1);
	fclose(input);
	fclose(input2);

	return 0;
}


