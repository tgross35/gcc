/* Test _Float64.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float64 } */
/* { dg-require-effective-target float64_runtime } */

#define BASE_SUFFIX 64
#define EXTENDED 0
#include "floatn-abi.h"
