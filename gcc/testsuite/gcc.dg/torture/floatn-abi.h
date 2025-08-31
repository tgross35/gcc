/* Smoke tests for that parameter passing and returning works correctly,
   including varargs.

   Define WIDTH to the float width and EXT to 1 for _FloatNx or 0 for
   _FloatN. For types where the data representation is smaller than the
   type's width (x86 _Float64x), CHECK_FIRST_N_BITS should also be defined.
*/

#define __STDC_WANT_IEC_60559_TYPES_EXT__

#include <float.h>
#include <stdarg.h>
#include <stddef.h>

#define _CONCAT(X, Y) X##Y
#define CONCAT(X, Y) _CONCAT (X, Y)
#define FLT_MAC(S) CONCAT (CONCAT (CONCAT (FLT, SUFFIX_UPPER), _), S)

#if EXTENDED
#define SUFFIX CONCAT (BASE_SUFFIX, x)
#define SUFFIX_UPPER CONCAT (BASE_SUFFIX, X)
#else
#define SUFFIX BASE_SUFFIX
#define SUFFIX_UPPER BASE_SUFFIX
#endif

#define TYPE CONCAT (_Float, SUFFIX)
#define TYPE_NAN (TYPE) (0.0 / 0.0)
#define TYPE_INF (TYPE) (1.0 / 0.0)
#define TYPE_PI (TYPE)3.14159265358979323846

/* Needed to account for float types with padding */
#ifdef  CHECK_FIRST_N_BITS
#define MEMCMP_BYTES (CHECK_FIRST_N_BITS / 8)
#else
#define MEMCMP_BYTES sizeof (TYPE)
#endif

#define assert_biteq(a, b, ...)                                               \
  do                                                                          \
    {                                                                         \
      TYPE _a = a;                                                            \
      TYPE _b = b;                                                            \
      /* We make a reasonable assumption that the end of the useful bits is   \
         byte-aligned, even for types that have padding. */                   \
      if (memcmp (&_a, &_b, MEMCMP_BYTES))                                    \
        {                                                                     \
          printf ("a (%#llx) != b (%#llx) ", _a, _b);                         \
          printf (__VA_ARGS__);                                               \
          exit (1);                                                           \
        }                                                                     \
    }                                                                         \
  while (0)

void exit (int);
int printf (const char *, ...);
int memcmp (const void *, const void *, size_t);

#define NUM_INPUTS 16

/* Populated with an ascending bitpattern */
volatile TYPE in_pat[NUM_INPUTS] = { TYPE_NAN };
/* Also check some semantically meaningful values */
volatile TYPE in_vals[NUM_INPUTS] = {
  0.0,           -0.0,           1.0,           -1.0,
  123.45678,     -123.45678,     TYPE_INF,      -TYPE_INF,
  TYPE_NAN,      -TYPE_NAN,      FLT_MAC (MAX), -FLT_MAC (MAX),
  FLT_MAC (MIN), -FLT_MAC (MIN), TYPE_PI,       -TYPE_PI,
};

volatile int va_i_res = 0;
volatile TYPE va_res[NUM_INPUTS] = { TYPE_NAN };
volatile TYPE pass_res[NUM_INPUTS] = { TYPE_NAN };
volatile TYPE pass_res2[NUM_INPUTS] = { TYPE_NAN };
volatile TYPE add_res = TYPE_NAN;
volatile TYPE sub_res = TYPE_NAN;
volatile TYPE mul_res = TYPE_NAN;
volatile TYPE div_res = TYPE_NAN;

void __attribute__ ((noinline))
do_pass (TYPE x0, TYPE x1, TYPE x2, TYPE x3, TYPE x4, TYPE x5, TYPE x6,
         TYPE x7, TYPE x8, TYPE x9, TYPE x10, TYPE x11, TYPE x12, TYPE x13,
         TYPE x14, TYPE x15)
{
  pass_res[0] = x0;
  pass_res[1] = x1;
  pass_res[2] = x2;
  pass_res[3] = x3;
  pass_res[4] = x4;
  pass_res[5] = x5;
  pass_res[6] = x6;
  pass_res[7] = x7;
  pass_res[8] = x8;
  pass_res[9] = x9;
  pass_res[10] = x10;
  pass_res[11] = x11;
  pass_res[12] = x12;
  pass_res[13] = x13;
  pass_res[14] = x14;
  pass_res[15] = x15;
}

/* Add a perturbation to help catch stack misalignments */
void __attribute__ ((noinline))
do_pass2 (char _c, TYPE x0, TYPE x1, TYPE x2, TYPE x3, TYPE x4, TYPE x5,
          TYPE x6, TYPE x7, TYPE x8, TYPE x9, TYPE x10, TYPE x11, TYPE x12,
          TYPE x13, TYPE x14, TYPE x15)
{
  pass_res2[0] = x0;
  pass_res2[1] = x1;
  pass_res2[2] = x2;
  pass_res2[3] = x3;
  pass_res2[4] = x4;
  pass_res2[5] = x5;
  pass_res2[6] = x6;
  pass_res2[7] = x7;
  pass_res2[8] = x8;
  pass_res2[9] = x9;
  pass_res2[10] = x10;
  pass_res2[11] = x11;
  pass_res2[12] = x12;
  pass_res2[13] = x13;
  pass_res2[14] = x14;
  pass_res2[15] = x15;
}

TYPE __attribute__ ((noinline))
do_return (volatile TYPE *p)
{
  return *p;
}

void __attribute__ ((noinline))
do_va (int _unused, ...)
{
  va_list va;
  va_start (va, _unused);
  for (int i = 0; i < NUM_INPUTS; ++i)
    {
      va_res[i] = va_arg (va, TYPE);
    }
  va_end (va);
}

/* Check basic operations which may involve the libcall ABI */
void __attribute__ ((noinline))
do_math (TYPE a, TYPE b)
{
  add_res = a + b;
  sub_res = a - b;
  mul_res = a * b;
  div_res = a / b;
}

void
test_one (volatile TYPE in[NUM_INPUTS])
{
  do_pass (in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7], in[8],
           in[9], in[10], in[11], in[12], in[13], in[14], in[15]);
  do_pass2 (0, in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7], in[8],
            in[9], in[10], in[11], in[12], in[13], in[14], in[15]);
  do_va (0, in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7], in[8],
         in[9], in[10], in[11], in[12], in[13], in[14], in[15]

  );

  for (int i = 0; i < NUM_INPUTS; ++i)
    {
      assert_biteq (in[i], pass_res[i], "pass error at index %d\n", i);
      assert_biteq (in[i], pass_res2[i], "pass2 error at index %d\n", i);
      assert_biteq (in[i], do_return (&in[i]), "return error at index %d\n",
                    i);
      assert_biteq (in[i], va_res[i], "va error at index %d\n", i);
    }
}

int
main ()
{
  for (int i = 0; i < NUM_INPUTS * sizeof (TYPE); ++i)
    {
      /* Populate with an increasing bitpattern */
      ((unsigned char *)in_pat)[i] = (i % 254) + 1;
    }

  test_one (in_pat);
  test_one (in_vals);

  do_math (1.5, -3.0);
  assert_biteq (add_res, -1.5, "add error\n");
  assert_biteq (sub_res, 4.5, "sub error\n");
  assert_biteq (mul_res, -4.5, "mul error\n");
  assert_biteq (div_res, -0.5, "div error\n");
}
