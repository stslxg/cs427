CC47 = /usr/bin/g++
NVCC = /opt/cuda/bin/nvcc

all: cuda_test cuda
cuda: RBFkernel.cu
	${NVCC} RBFkernel.cu -o kernel
	./kernel

cuda_test: RBFkernel_old.cu RBF_test.cu
	${NVCC} RBF_test.cu -o kernel_c
	${NVCC} RBFkernel_old.cu -o kernel_cuda
	./kernel_cuda > b.txt
	./kernel_c > a.txt
	diff a.txt b.txt > c.txt

clean:
	rm *.o -rf
	rm kernel* -rf
	rm *txt -rf
