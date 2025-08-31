/* Test _Float32.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float32 } */
/* { dg-require-effective-target float32_runtime } */

#define BASE_SUFFIX 32
#define EXTENDED 0
#include "floatn-abi.h"
