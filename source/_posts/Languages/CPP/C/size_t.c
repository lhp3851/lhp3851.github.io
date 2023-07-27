#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// #include <threads.h>

void sizet_attr()
{
  const size_t N = 100;
  int numbers[N];
  for (size_t ndx = 0; ndx < N; ++ndx)
    numbers[ndx] = ndx;
  printf("SIZE_MAX = %zu\n", SIZE_MAX);
  size_t size = sizeof numbers;
  printf("size = %zu\n", size);
}

void abortProgram()
{
  FILE *fp = fopen("data.txt", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "error opening file data.txt in function main()\n");
    abort();
  }
  fclose(fp);
}

void floatAttr()
{
  printf("FLT_RADIX    = %d\n", FLT_RADIX);
  printf("DECIMAL_DIG  = %d\n", DECIMAL_DIG);
  printf("FLT_MIN      = %e\n", FLT_MIN);
  printf("FLT_MAX      = %e\n", FLT_MAX);
  printf("FLT_EPSILON  = %e\n", FLT_EPSILON);
  printf("FLT_DIG      = %d\n", FLT_DIG);
  printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
  printf("FLT_MIN_EXP  = %d\n", FLT_MIN_EXP);
  printf("FLT_MIN_10_EXP  = %d\n", FLT_MIN_10_EXP);
  printf("FLT_MAX_EXP     = %d\n", FLT_MAX_EXP);
  printf("FLT_MAX_10_EXP  = %d\n", FLT_MAX_10_EXP);
  printf("FLT_ROUNDS      = %d\n", FLT_ROUNDS);
  printf("FLT_EVAL_METHOD = %d\n", FLT_EVAL_METHOD);
  // printf("FLT_HAS_SUBNORM = %d\n", FLT_HAS_SUBNORM);
}

void itoa(int n, int base, char *buf)
{
  div_t dv = {.quot = n};
  char *p = buf;
  do
  {
    dv = div(dv.quot, base);
    *p++ = "0123456789abcdef"[abs(dv.rem)];
  } while (dv.quot);

  if (n < 0)
    *p++ = '-';
  *p-- = '\0';

  while (buf < p)
  {
    char c = *p;
    *p-- = *buf;
    *buf++ = c;
  } // reverse
}

atomic_int acnt;
int cnt;

int f(void *thr_data)
{
  for (int n = 0; n < 1000; ++n)
  {
    ++cnt;
    ++acnt;
  }
  return 0;
}

// void thread_example(){
//     thrd_t thr[10];
//     for (int n = 0; n < 10; ++n)
//         thrd_create(&thr[n], f, NULL);
//     for (int n = 0; n < 10; ++n)
//         thrd_join(thr[n], NULL);

//     printf("The atomic counter is %u\n", acnt);
//     printf("The non-atomic counter is %u\n", cnt);
// }

int main(void)
{
  printf("%lld", UINT64_C(0x123));
  sizet_attr();
  // abortProgram();
  floatAttr();
  intmax_t x = INT8_MAX + 2;
  printf("%ld", imaxabs(x));

  const char *string = "abcde312$#@";
  const char *low_alpha = "qwertyuiopasdfghjklzxcvbnm";

  size_t spnsz = strspn(string, low_alpha);
  printf("After skipping initial lowercase letters from '%s'\n"
         "The remainder is '%s'\n",
         string, string + spnsz);
}