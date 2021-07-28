//=== libompx/Accessor_c.h - Accessor class definition ----*- C -*-===//
//
// Part of the libompx Project, under the MIT License.
// See libompx/LICENSE.txt for license information
//
//===-------------------------------------------------------------===//
///
/// \file
/// This file contains the
/// 
/// 
///
//===-------------------------------------------------------------===//


#ifndef LIBOMPX_ACCESSOR_H
#define LIBOMPX_ACCESSOR_H

/// Macro required to concatenate type and access mode as needed
#define concat(x,y) x ## y
#define doconcat(x,y) concat(x,y)
#define NAME(g) doconcat(doconcat(g,ACCESS_MODE),TYPE)


// generate code for int
#define TYPE int

// int, read
#define ACCESS_MODE read_
#define K to
#include "acc.def"
#undef K
#undef ACCESS_MODE

// int, write
#define ACCESS_MODE write_
#define K from
#include "acc.def"
#undef K
#undef ACCESS_MODE

// int, read_write
#define ACCESS_MODE read_write_
#define K tofrom
#include "acc.def"
#undef K
#undef ACCESS_MODE

#undef TYPE

// generate code for float
#define TYPE float

// float, read
#define ACCESS_MODE read_
#define K to
#include "acc.def"
#undef K
#undef ACCESS_MODE

// float, write
#define ACCESS_MODE write_
#define K from
#include "acc.def"
#undef K
#undef ACCESS_MODE

// float, read_write
#define ACCESS_MODE read_write_ 
#define K tofrom
#include "acc.def"
#undef K
#undef ACCESS_MODE

#undef TYPE

// generate code for double
#define TYPE double

// double, read
#define ACCESS_MODE read_
#define K to
#include "acc.def"
#undef K
#undef ACCESS_MODE

// double, write
#define ACCESS_MODE write_
#define K from
#include "acc.def"
#undef K
#undef ACCESS_MODE

// double, read_write
#define ACCESS_MODE read_write_ 
#define K tofrom
#include "acc.def"
#undef K
#undef ACCESS_MODE

#undef TYPE


#endif

///===--- vim: set ft=c sw=2 ts=2 sts=2 et: ----------------------===///
