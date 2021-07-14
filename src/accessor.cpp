#include <random>
#include <iostream>
#include <omp.h>
#include "utils.h"
#include "accessor.h"

constexpr int NROWS = 1;
constexpr int NCOLS = 10;

int main(){
   

    double* a = new double[NROWS * NCOLS];
    double* b = new double[NROWS * NCOLS];
    double* c = new double[NROWS * NCOLS];

    generateMatrix(NROWS, NCOLS, 0.7, a);
    std::cout << "A: " ;
    printVector(a, 0, NROWS*NCOLS);

    
    generateMatrix(NROWS, NCOLS, 0.5, b);
    std::cout << "B: " ;
    printVector(b, 0, NROWS*NCOLS);


    Accessor<READ, double> acc_a(a, NROWS*NCOLS); 
    Accessor<READ, double> acc_b(b, NROWS*NCOLS);
    Accessor<WRITE, double> acc_c(c, NROWS*NCOLS);

#pragma omp target teams distribute parallel for 
    for (int i = 0; i < NROWS*NCOLS; i++){
        acc_c[i] = acc_a[i] + acc_b[i];
    } 


    std::cout << "After device:" << std::endl;
    std::cout << "C: ";
    printVector(c, 0, NROWS*NCOLS);
    
    delete [] a;
    delete [] b;
    delete [] c;
}
