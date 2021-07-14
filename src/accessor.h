// enum to hold different access modes
enum access_mode{READ, WRITE, READ_WRITE};

// Accessor Class Declaration
template <access_mode A, typename T>
class Accessor {
	
// _data and _len need to be public to be used in declare mapper
public:
    // pointer to the data
	T* _data;   
    // length of data
    size_t _len; 
    // ctor
	Accessor(T*, size_t);

    T& operator [](int);
};

// different mappers based on access mode
#pragma omp declare mapper(Accessor<READ, double> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(Accessor<WRITE, double> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(Accessor<READ_WRITE, double> a) map(tofrom: a._data[0:a._len])

#include "accessor_impl.h"
