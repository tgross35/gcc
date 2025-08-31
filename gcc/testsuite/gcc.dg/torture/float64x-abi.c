/* Test _Float64x.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float64x } */
/* { dg-require-effective-target float64x_runtime } */

#define BASE_SUFFIX 64
#define EXTENDED 1

#if defined(__x86_64__) || defined(__i386__)
// The first 80 bits are an x87 long double, the rest can be garbage.
#define CHECK_FIRST_N_BITS 80
#endif

#include "floatn-abi.h"
