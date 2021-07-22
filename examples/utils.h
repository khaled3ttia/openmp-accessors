//=== examples/utils.h - Helper Functions for Accessor Examples ----*- C++ -*-===//
//
// Part of the OMP-UL Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the helper functions  
/// used in the examples for libompx::Accessor header 
///
//===-------------------------------------------------------------===//
#ifndef LIBOMPX_EXAMPLES_UTILS
#define LIBOMPX_EXAMPLES_UTILS

#include <random>

/// A function to populate a matrix with random values given a sparsity value
void generateIntMatrix(int nrows, int ncols, float nnzRate, int *&vals){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> nnzDist(0,1);
    std::uniform_int_distribution<> valsDist(1,9999);
    
    for (int i = 0 ; i < nrows; i++){
        for (int j = 0 ; j < ncols; j++){
            if (nnzDist(gen) < nnzRate){

                vals[i*ncols + j] = valsDist(gen);
            }else{
                vals[i*ncols + j] = 0;
            }
        }
    }
}

/// A function to print a vector to std::out 
template <typename T>
void printVector(T* ptr, int start, int end){
	std::cout << "{\t";
	for (int i = start; i < end; i++){
		if (i == end-1){
			std::cout << (T)ptr[i] << "\t}" << std::endl;
		}else{
			std::cout << (T)ptr[i] << "\t";
		}
	}
}

#endif

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------===///
