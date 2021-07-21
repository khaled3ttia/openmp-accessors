// Base class ctor
template <access_mode A, typename T>
Accessor_Base<A,T>::Accessor_Base(T* data, size_t len):_data(data), _len(len){}

// specialized Child with READ access ctor
template <typename T>
Accessor<READ,T>::Accessor(T* data, size_t len): Accessor_Base<READ, T>(data, len){}

// specialized Child with any other access mode ctor
template <access_mode A, typename T>
Accessor<A,T>::Accessor(T* data, size_t len): Accessor_Base<A,T>(data, len){}

// READ [] operator
template <typename T>
const T& Accessor<READ, T>::operator[](const int idx) const { return this->_data[idx]; }

// other access modes [] operator 
template <access_mode A, typename T>
T& Accessor<A, T>::operator[](const int idx) const { return this->_data[idx]; }


