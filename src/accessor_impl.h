template <access_mode A, typename T>
Accessor<A, T>::Accessor(T* data, size_t len):_data(data), _len(len){}

template <access_mode A, typename T>
T& Accessor<A, T>::operator[](int idx){ return _data[idx]; }


