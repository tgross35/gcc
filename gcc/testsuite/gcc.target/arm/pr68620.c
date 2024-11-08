/* { dg-do compile } */
/* { dg-skip-if "-mpure-code supports M-profile without Neon only" { *-*-* } { "-mpure-code" } } */
/* { dg-require-effective-target arm_arch_v7a_ok } */
/* { dg-options "-mfp16-format=ieee -mfpu=auto -mfloat-abi=softfp" } */
/* { dg-add-options arm_arch_v7a } */

#include "arm_neon.h"

float16x4_t __attribute__((target("fpu=neon-fp16")))
foo (float32x4_t arg)
{
    return vcvt_f16_f32 (arg);
}
