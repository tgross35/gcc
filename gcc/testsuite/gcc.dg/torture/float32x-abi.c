/* Test _Float32x.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float32x } */
/* { dg-require-effective-target float32x_runtime } */

#define BASE_SUFFIX 32
#define EXTENDED 1
#include "floatn-abi.h"
