//=== libompx/Accessor.h - Accessor class definition ----*- C++ -*-===//
//
// Part of the OMP-UL Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Accessor class, which is
/// used to wrap dynamically allocated regions pointers to provide 
/// transparent data movement through OpenMP declare mapper
///
//===-------------------------------------------------------------===//


#ifndef LIBOMPX_ACCESSOR_H
#define LIBOMPX_ACCESSOR_H

namespace libompx {
    
    /// enum to hold different access modes
    enum access_mode{READ, WRITE, READ_WRITE, ALLOC};

    /// Base Accessor Class Declaration, not intended for direct use by
    /// user
    template <access_mode A, typename T>
    class Accessor_Base {
    protected:
        /// Constructor to be used only by child classes
        Accessor_Base(T* data, size_t len):_data(data), _len(len) {};
    public:

        // _data and _len need to be public to be used in declare mapper
        // pointer to the data
        
        /// Pointer to the original data allocated by user 
        T* _data;   

        /// Length of user-allocated data region
        size_t _len;
        
        /// Returns the length of the user-specified data region
        size_t getLen() const{ return _len; };
        
        /// Return a pointer the start of data region
        const T* begin() const { return _data; };

        /// Returns a pointer to the end of data region
        const T* end() const { return _data+_len; };
    };

    /// Child Accessor 1: All access modes except for READ
    template <access_mode A, typename T>
    class Accessor: public Accessor_Base<A, T>{
    public:

        /// Accessor constructor
        Accessor(T* data, size_t len): Accessor_Base<A, T>(data, len){ };

        /// Returns a pointer to the user-specified data region
        T* getData() const{ return this->_data; };

        /// [] operator overloading returns a reference to a data element
        /// to allow data maniuplation in WRITE/READ_WRITE modes
        T& operator[](const int idx) const { return this->_data[idx]; };
    };

    /// Child Accessor 2: access_mode specialized for READ
    template <typename T>
    class Accessor<READ, T>: public Accessor_Base<READ, T>{
    public:
        /// Accessor constructor 
        Accessor(T* data, size_t len): Accessor_Base<READ, T>(data, len) {};
        
        /// Returns a const pointer to the user-specified data region
        /// to prevent modification of data elements (since access_mode is READ)
        const T* getData() const { return this->_data; };

        /// [] operator overloading  returns a const reference to prevent 
        /// modification of data elements (since access_mode is READ)
        const T& operator[](const int idx) const { return this->_data[idx]; };
    };
}

/// different mappers based on access mode
#pragma omp declare mapper(libompx::Accessor<libompx::READ, double> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, double> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, double> a) map(tofrom: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::ALLOC, double> a) map(alloc: a._data[0:a._len])

#pragma omp declare mapper(libompx::Accessor<libompx::READ, float> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, float> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, float> a) map(tofrom: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::ALLOC, float> a) map(alloc: a._data[0:a._len])

#pragma omp declare mapper(libompx::Accessor<libompx::READ, int> a) map(to: a._data[0:a._len]) 
#pragma omp declare mapper(libompx::Accessor<libompx::WRITE, int> a) map(from: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::READ_WRITE, int> a) map(tofrom: a._data[0:a._len])
#pragma omp declare mapper(libompx::Accessor<libompx::ALLOC, int> a) map(alloc: a._data[0:a._len])


#endif

///===--- vim: set ft=cpp sw=2 ts=2 sts=2 et: ----------------------===///
