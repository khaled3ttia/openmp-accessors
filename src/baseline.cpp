#include <random>
#include <iostream>
#include <omp.h>
#include "utils.h"

constexpr int NROWS = 1;
constexpr int NCOLS = 10;

int main(){
   

    double* a = new double[NROWS * NCOLS];
    double* b = new double[NROWS * NCOLS];
    double* c = new double[NROWS * NCOLS];

    generateMatrix(NROWS, NCOLS, 0.7, a);
    std::cout << "A: " ;
    printVector(a, 0, NROWS*NCOLS);
    

    generateMatrix(NROWS, NCOLS, 0.2, b);
    std::cout << "B: " ;
    printVector(b, 0, NROWS*NCOLS);

#pragma omp target teams distribute parallel for map (to:a[0:NROWS*NCOLS], b[0:NROWS*NCOLS]) map(from:c[0:NROWS*NCOLS]) 
    for (int i = 0; i < NROWS * NCOLS; i++){
    
        c[i] = a[i] + b[i];
    }


    std::cout << "C: " ;
    printVector(c, 0, NROWS*NCOLS);


    delete [] a;
    delete [] b;
    delete [] c;
}
