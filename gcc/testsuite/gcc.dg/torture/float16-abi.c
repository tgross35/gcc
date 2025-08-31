/* Test _Float16.  */
/* { dg-do run } */
/* { dg-options "-Wno-old-style-definition" } */
/* { dg-add-options float16 } */
/* { dg-require-effective-target float16_runtime } */

#define BASE_SUFFIX 16
#define EXTENDED 0
#include "floatn-abi.h"
