HEADERDIR=../include/
CXX=clang++
CXXFLAGS=-std=c++11 -fopenmp -fopenmp-targets=nvptx64 -O3 -gline-tables-only -I $(HEADERDIR)
CXXSYCLFLAGS=-fsycl -fsycl-targets=nvptx64-nvidia-cuda-sycldevice 

all: vec_add vec_add_base

vec_add:
	$(CXX) $(CXXFLAGS) vec_add.cpp -o vec_add.exe

vec_add_sycl:
	$(CXX) $(CXXSYCLFLAGS) vec_add_sycl.cpp -o vec_add_sycl.cpp

vec_add_base:
	$(CXX) $(CXXFLAGS) vec_add_base.cpp -o vec_add_base.exe

clean:
	rm -rf *.exe
