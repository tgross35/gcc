/* Test _Float128x.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float128x } */
/* { dg-require-effective-target float128x_runtime } */

#define BASE_SUFFIX 128
#define EXTENDED 1
#include "floatn-abi.h"
