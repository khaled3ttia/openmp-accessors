enum access_mode{READ, WRITE, READ_WRITE};
template <typename T>
class Accessor {
	
private:
	T* _data; 
    size_t _len; 
	access_mode _mode;

public:
	Accessor(T*, size_t,  access_mode=READ_WRITE);
    T* getData();
    size_t getLen();
	access_mode getMode();
	void setData(T*);
    void setLength(size_t);
	void setMode(access_mode);
    T& operator [](int);

#pragma omp declare mapper(Accessor<double> a) map(a, a._data[0:a._len])
};

#include "accessor_impl.h"
