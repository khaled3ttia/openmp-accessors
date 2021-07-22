# libompx::Accessor
User-friendly Data Movement for OpenMP target offloading

## About
`Accessor` is a header that augments OpenMP target offloading directives, that eliminates the need for the user to write `map` clauses
Instead, users can directly create an `Accessor` object around their data pointer, and specify the desired access mode as follows:

    double * data = new data[N];
    // initialize data here as needed
    Accessor<READ, double> data_Acc(data, N);

In the previous example, an `Accessor` object around `data` is instaniated, with the `READ` access mode.
Now, the user can use OpenMP target directive without needing to write a map clause for `data` or `data_Acc` as follows:
    
    #pragma omp target teams distribute parallel for
    // device region code that reads from data_Acc 

## How it works?
`Accessor` header provides an abstraction layer around raw pointers to dynamically allocated memory, which also takes data region size as a constructor parameter
It allows the user to specify a template parameter defining one of the following access modes: `READ`, `WRITE`, `READ_WRITE`, or `ALLOC`. 
Then, the header provides a set of pre-defined mappers (using `#pragma omp declare mapper`) for different access modes and data types.

## How to use?
In order to use `Accessor`, you need an OpenMP offloading-capable compiler (i.e. `clang`). In your application, include both `<omp.h>` and the header file `"Accessor.h"`
The `Accessor` class takes two template parameters `libompx::Accessor<access_mode A, typename T>` and two constructor arguments `(T* data, size_t len)`. Full examples are
available in libompx/examples
