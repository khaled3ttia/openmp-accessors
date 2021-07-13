#include <random>

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

void printVector(double* ptr, int start, int end){
	std::cout << "{\t";
	for (int i = start; i < end; i++){
		if (i == end-1){
			std::cout << ptr[i] << "\t}" << std::endl;
		}else{
			std::cout << ptr[i] << "\t";
		}
	}
}


