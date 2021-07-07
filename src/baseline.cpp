#include <random>
#include <iostream>
#include <omp.h>

void generateMatrix(int nrows, int ncols, double nnzRate, double *&vals){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0,1);
    std::uniform_real_distribution<> dist2(1,1e6);
    for (int i = 0 ; i < nrows; i++){
        for (int j = 0 ; j < ncols; j++){
            if (dist(gen) < nnzRate){

                vals[i*ncols + j] = dist2(gen);
            }else{
                vals[i*ncols + j] = 0;
            }
        }

    }

}

constexpr int NROWS = 1000;
constexpr int NCOLS = 1000;

int main(){
   

    double* a = new double[NROWS * NCOLS];
    double* b = new double[NROWS * NCOLS];
    double* c = new double[NROWS * NCOLS];

    generateMatrix(NROWS, NCOLS, 0.7, a);
    generateMatrix(NROWS, NCOLS, 0.2, b);

    for (int i = 0; i < NROWS * NCOLS; i++){
    
        c[i] = a[i] + b[i];
    }


}
