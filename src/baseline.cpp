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



constexpr int NROWS = 1;
constexpr int NCOLS = 10;

int main(){
   

    double* a = new double[NROWS * NCOLS];
    double* b = new double[NROWS * NCOLS];
    double* c = new double[NROWS * NCOLS];

    generateMatrix(NROWS, NCOLS, 0.7, a);

    std::cout << "A: {" ;
    for (int i = 0 ; i < NROWS * NCOLS ; i++){
	if (i == NROWS * NCOLS - 1){
		std::cout << a[i] << "}" << std::endl;
	}else{
		std::cout << a[i] << " "; 
	}

    }

    generateMatrix(NROWS, NCOLS, 0.2, b);

    std::cout << "B: {" ;
    for (int i = 0 ; i < NROWS * NCOLS ; i++){
	if (i == NROWS * NCOLS - 1){
		std::cout << b[i] << "}" << std::endl;
	}else{
		std::cout << b[i] << " "; 
	}

    }


#pragma omp target teams distribute parallel for map (to:a[0:NROWS*NCOLS], b[0:NROWS*NCOLS]) map(from:c[0:NROWS*NCOLS]) 
    for (int i = 0; i < NROWS * NCOLS; i++){
    
        c[i] = a[i] + b[i];
    }


    std::cout << "C: {" ;
    for (int i = 0 ; i < NROWS * NCOLS ; i++){
	if (i == NROWS * NCOLS - 1){
		std::cout << c[i] << "}" << std::endl;
	}else{
		std::cout << c[i] << " "; 
	}

    }


}
