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

    Accessor<double> acc_a(a, NROWS*NCOLS,  READ); 

    generateMatrix(NROWS, NCOLS, 0.7, a);
    std::cout << "A: " ;
    printVector(a, 0, NROWS*NCOLS);
   
    std::cout << "Accessor A: {";
    for (int i = 0; i < NROWS*NCOLS; i++){
        std::cout << acc_a[i] << " ";
    } 
    std::cout << "} " <<  std::endl;

    delete [] a;
}
