#include <CL/sycl.hpp>
#include "utils.h"
using namespace sycl;

constexpr int NROWS = 1;
constexpr int NCOLS = 10;
class add_vec;

int main(){

	// Create a GPU queue
	cl::sycl::queue Queue{ gpu_selector{} };
	
	// Print Selected Device Info
	std::cout << "Selected Device: " << Queue.get_device().get_info<sycl::info::device::name>() << "\n";

	// Host data
	int* a = new int[NROWS * NCOLS];
	int* b = new int[NROWS * NCOLS];
	int* c = new int[NROWS * NCOLS];

	// generate A matrix (on host)
	generateIntMatrix(NROWS, NCOLS, 0.7, a);
	std::cout << "A: "; 	
	printVector(a, 0, NROWS*NCOLS);

	// generate B matrix (on host)
	generateIntMatrix(NROWS, NCOLS, 0.2, b);
	std::cout << "B: ";
	printVector(b, 0, NROWS*NCOLS);

	// Create Buffers around A, B, and C in order to access them 
	// from devices
	buffer<int> bufA = sycl::buffer(a, sycl::range(NROWS*NCOLS));
	buffer<int> bufB = sycl::buffer(b, sycl::range(NROWS*NCOLS));
	buffer<int> bufC = sycl::buffer(c, sycl::range(NROWS*NCOLS));

	// Submit work to the GPU queue
	Queue.submit([&](handler &h){
			// Cannot access buffers directly, we need accessors
			accessor a_acc(bufA, h, read_only);
			accessor b_acc(bufB, h, read_only);
			accessor c_acc(bufC, h, write_only);
			// Parallel for to do the work in parallel
			// Note: needs a name (add_vec) which is defined earlier as a class
			h.parallel_for<add_vec>(NROWS*NCOLS, [=](sycl::id<1> i){
					c_acc[i] = a_acc[i] + b_acc[i];
				});
			});
	
	// Matrix C (which is written on device) can only be obtained using the buffer bufC: changes are not propagated to double *c (This is how Sycl/DPC++ works!)
	// In order to access the buffer, we need a host accessor 
	host_accessor host_accessor(bufC);
	std::cout << "C: ";
	std::cout << "{\t";
	for (int i = 0; i < NROWS*NCOLS; i++){
		if (i == NROWS * NCOLS - 1){
			std::cout << host_accessor[i] << "\t}" << std::endl;
		}else{
			std::cout << host_accessor[i] << "\t";
		}
	}

	delete [] a;
	delete [] b;
	delete [] c;	
}

