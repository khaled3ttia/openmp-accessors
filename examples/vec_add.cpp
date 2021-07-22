#include <iostream>
#include <omp.h>
#include "utils.h"
#include "Accessor.h"

constexpr int NROWS = 1;
constexpr int NCOLS = 10;
using namespace libompx;
int main(){
   

    int* a = new int[NROWS * NCOLS];
    int* b = new int[NROWS * NCOLS];
    int* c = new int[NROWS * NCOLS];

    generateIntMatrix(NROWS, NCOLS, 0.7, a);
    std::cout << "A: " ;
    printVector(a, 0, NROWS*NCOLS);

    
    generateIntMatrix(NROWS, NCOLS, 0.5, b);
    std::cout << "B: " ;
    printVector(b, 0, NROWS*NCOLS);


    Accessor<READ, int> acc_a(a, NROWS*NCOLS); 
    Accessor<READ, int> acc_b(b, NROWS*NCOLS);
    Accessor<READ_WRITE, int> acc_c(c, NROWS*NCOLS);

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
