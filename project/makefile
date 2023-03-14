CC47	= /usr/bin/g++

all: m3

m3: m3.cpp m3_result.cpp
	${CC47} -fopenmp m3.cpp -o m3
	${CC47} m3_result.cpp -o m3_res

clean:
	rm *.o -rf
