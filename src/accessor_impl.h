template <typename T>
Accessor<T>::Accessor(T* data, size_t len, access_mode mode):_data(data), _len(len), _mode(mode){}

template <typename T>
T* Accessor<T>::getData() { return _data; }

template <typename T>
size_t Accessor<T>::getLen() { return _len; }

template <typename T>
access_mode Accessor<T>::getMode() { return _mode; } 

template <typename T>
void Accessor<T>::setData(T* data) { _data = data; }

template <typename T>
void Accessor<T>::setLength(size_t len) { _len = len; }

template <typename T>
void Accessor<T>::setMode(access_mode mode) { _mode = mode; }

template <typename T>
T& Accessor<T>::operator[](int idx){ return _data[idx]; }


