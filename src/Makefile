baseline:
	clang++ -fopenmp -fopenmp-targets=nvptx64 -O3 -g baseline.cpp -o base.exe
sycl:
	clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda-sycldevice sycl.cpp -o sycl.exe
acc:
	clang++ -fopenmp -fopenmp-targets=nvptx64 -O3 -g accessor.cpp -o acc.exe
