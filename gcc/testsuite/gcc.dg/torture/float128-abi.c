/* Test _Float128.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float128 } */
/* { dg-require-effective-target float128_runtime } */

#define BASE_SUFFIX 128
#define EXTENDED 0
#include "floatn-abi.h"
