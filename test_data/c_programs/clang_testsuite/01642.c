int printf(char const *, ...);
typedef long unsigned int size_t;
typedef long int intmax_t;
typedef long unsigned int uintmax_t;
typedef long int ptrdiff_t;
typedef int wchar_t;
void test() {
  printf("%s", (int) 123);
  printf("abc%0f", "testing testing 123");
  printf("%u", (long) -12);
  printf("%p", 123);
  printf("%c\n", "x");
  printf("%c\n", 1.23);
  printf("%+.2d", (unsigned long long) 123456);
  printf("%1d", (long double) 1.23);
  printf("%0+s", (unsigned) 31337);
  printf("%#p", (void *) 0);
  printf("% +f", 1.23);
  printf("%0-f", 1.23);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-non-iso"
  printf("%1$f:%2$.*3$f:%4$.*3$f\n", 1, 2, 3, 4);
#pragma clang diagnostic pop
  printf("%10.5d", 1l);
  printf("%.2c", 'a');
  printf("%0-f", 1.23);
  printf("%hhs", "foo");
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-non-iso"
  printf("%1$zp", (void *)0);
#pragma clang diagnostic pop
  unsigned long val = 42;
  printf("%X", val);
  printf("%f", (size_t) 42);
  printf("%f", (intmax_t) 42);
  printf("%f", (uintmax_t) 42);
  printf("%f", (ptrdiff_t) 42);
  typedef size_t my_size_type;
  typedef intmax_t my_intmax_type;
  typedef uintmax_t my_uintmax_type;
  typedef ptrdiff_t my_ptrdiff_type;
  typedef int my_int_type;
  printf("%f", (my_size_type) 42);
  printf("%f", (my_intmax_type) 42);
  printf("%f", (my_uintmax_type) 42);
  printf("%f", (my_ptrdiff_type) 42);
  printf("%f", (my_int_type) 42);
  printf("%ld", "foo");
  printf("%o", (long) 42);
  printf("%u", (long) 42);
  printf("%x", (long) 42);
  printf("%X", (long) 42);
  printf("%i", (unsigned long) 42);
  printf("%d", (unsigned long) 42);
  printf("%F", (long double) 42);
  printf("%e", (long double) 42);
  printf("%E", (long double) 42);
  printf("%g", (long double) 42);
  printf("%G", (long double) 42);
  printf("%a", (long double) 42);
  printf("%A", (long double) 42);
}
int scanf(char const *, ...);
void test2(int intSAParm[static 2]) {
  char str[100];
  char *vstr = "abc";
  short shortVar;
  unsigned short uShortVar;
  int intVar;
  int intAVar[2];
  unsigned uIntVar;
  float floatVar;
  double doubleVar;
  long double longDoubleVar;
  long longVar;
  unsigned long uLongVar;
  long long longLongVar;
  unsigned long long uLongLongVar;
  size_t sizeVar;
  intmax_t intmaxVar;
  uintmax_t uIntmaxVar;
  ptrdiff_t ptrdiffVar;
  enum {A, B, C} enumVar;
  scanf("%lf", str);
  scanf("%lf", vstr);
  scanf("%ls", str);
  scanf("%ls", str);
  scanf("%f", &shortVar);
  scanf("%f", &uShortVar);
  scanf("%p", &intVar);
  scanf("%f", intAVar);
  scanf("%f", intSAParm);
  scanf("%Lf", &uIntVar);
  scanf("%ld", &floatVar);
  scanf("%f", &doubleVar);
  scanf("%d", &longDoubleVar);
  scanf("%f", &longVar);
  scanf("%f", &uLongVar);
  scanf("%f", &longLongVar);
  scanf("%f", &uLongLongVar);
  scanf("%d", &enumVar);
  scanf("%f", &sizeVar);
  scanf("%f", &intmaxVar);
  scanf("%f", &uIntmaxVar);
  scanf("%f", &ptrdiffVar);
  typedef size_t my_size_type;
  typedef intmax_t my_intmax_type;
  typedef uintmax_t my_uintmax_type;
  typedef ptrdiff_t my_ptrdiff_type;
  typedef int my_int_type;
  scanf("%f", (my_size_type*)&sizeVar);
  scanf("%f", (my_intmax_type*)&intmaxVar);
  scanf("%f", (my_uintmax_type*)&uIntmaxVar);
  scanf("%f", (my_ptrdiff_type*)&ptrdiffVar);
  scanf("%f", (my_int_type*)&intVar);
  scanf("%o", &longVar);
  scanf("%u", &longVar);
  scanf("%x", &longVar);
  scanf("%X", &longVar);
  scanf("%i", &uLongVar);
  scanf("%d", &uLongVar);
  scanf("%F", &longDoubleVar);
  scanf("%e", &longDoubleVar);
  scanf("%E", &longDoubleVar);
  scanf("%g", &longDoubleVar);
  scanf("%G", &longDoubleVar);
  scanf("%a", &longDoubleVar);
  scanf("%A", &longDoubleVar);
}
