












typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;

typedef long int int64_t;







typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;



typedef unsigned long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
typedef long int intmax_t;
typedef unsigned long int uintmax_t;

int i;
uintptr_t __attribute__((noinline,const)) bar(int ***p) { return (uintptr_t)p; }
void __attribute__((noinline))
foo(void)
{
  int *y;
  int **a = &y, **x;
  int ***p;
  uintptr_t b;
  b = bar(&a);
  p = (int ***)b;
  x = *p;
  *x = &i;
  *y = 0;
}
extern void abort (void);
int main()
{
  i = 1;
  foo ();
  if (i != 0)
    abort ();
  return 0;
}
