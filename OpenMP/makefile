CC47	= /usr/bin/g++

all: openmp_test

openmp_test: vector.c matrix.c
	${CC47} -fopenmp vector.c -o vector_test
	${CC47} -fopenmp matrix.c -o matrix_test

clean:
	rm *.o -rf
	rm *test -rf
