#ifndef ACCESSOR_H
#define ACCESSOR_H

namespace libompx {
    
    // enum to hold different access modes
    enum access_mode{READ, WRITE, READ_WRITE};

    // Base Accessor Class Declaration
    template <access_mode A, typename T>
    class Accessor_Base {
    protected:
        // Constructor to be used only by child classes
        Accessor_Base(T* data, size_t len):_data(data), _len(len) {};
    public:
        // _data and _len need to be public to be used in declare mapper
        // pointer to the data
        T* const _data;   
        // length of data
        size_t _len;
        
        size_t getLen() const{ return _len; };
        
        const T* begin() const { return _data; };

        const T* end() const { return _data+_len; };
    };

    // Child Accessor 1: All access modes except for READ
    template <access_mode A, typename T>
    class Accessor: public Accessor_Base<A, T>{
    public:
        Accessor(T* data, size_t len): Accessor_Base<A, T>(data, len){ };

        T* getData() const{ return this->_data; };

        // operator returns a reference
        // To allow data maniuplation in WRITE/READ_WRITE modes
        T& operator[](const int idx) const { return this->_data[idx]; };
    };

    // Child Accessor 2: access_mode specialized for READ
    template <typename T>
    class Accessor<READ, T>: public Accessor_Base<READ, T>{
    public:
        Accessor(T* data, size_t len): Accessor_Base<READ, T>(data, len) {};
        
        const T* getData() const { return this->_data; };

        // operator returns a const reference to prevent modification
        const T& operator[](const int idx) const { return this->_data[idx]; };
    };
}

// different mappers based on access mode
#pragma omp declare mapper(libompx::Accessor<libompx::READ, double> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, double> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, double> a) map(tofrom: a._data[0:a._len])

#pragma omp declare mapper(libompx::Accessor<libompx::READ, float> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, float> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, float> a) map(tofrom: a._data[0:a._len])

#pragma omp declare mapper(libompx::Accessor<libompx::READ, int> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, int> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, int> a) map(tofrom: a._data[0:a._len])

#endif
