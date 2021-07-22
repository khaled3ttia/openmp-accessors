baseline:
	clang++ -fopenmp -fopenmp-targets=nvptx64 -O3 -gline-tables-only baseline.cpp -o base.exe
sycl:
	clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda-sycldevice sycl.cpp -o sycl.exe
acc:
	clang++ -std=c++20 -fopenmp -fopenmp-targets=nvptx64 -O3 -gline-tables-only accessor.cpp -o acc.exe
