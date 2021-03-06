#pragma omp for simd
#pragma omp for simd foo
void test_no_clause() {
  int i;
#pragma omp for simd
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd
  ++i;
}
void test_branch_protected_scope() {
  int i = 0;
L1:
  ++i;
  int x[24];
#pragma omp parallel
#pragma omp for simd
  for (i = 0; i < 16; ++i) {
    if (i == 5)
      goto L1;
    else if (i == 6)
      return;
    else if (i == 7)
      goto L2;
    else if (i == 8) {
    L2:
      x[i]++;
    }
  }
  if (x[0] == 0)
    goto L2;
  else if (x[1] == 1)
    goto L1;
}
void test_invalid_clause() {
  int i;
#pragma omp parallel
#pragma omp for simd foo bar
  for (i = 0; i < 16; ++i)
    ;
}
void test_non_identifiers() {
  int i, x;
#pragma omp parallel
#pragma omp for simd;
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd linear(x);
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(x);
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd, private(x);
  for (i = 0; i < 16; ++i)
    ;
}
extern int foo();
void test_safelen() {
  int i;
#pragma omp for simd safelen
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4, , 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(4, 8)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(2.5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(foo())
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(-5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(0)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(5 - 5)
  for (i = 0; i < 16; ++i)
    ;
}
void test_simdlen() {
  int i;
#pragma omp for simd simdlen
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4, , 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(4, 8)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(2.5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(foo())
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(-5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(0)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd simdlen(5 - 5)
  for (i = 0; i < 16; ++i)
    ;
}
void test_safelen_simdlen() {
  int i;
#pragma omp for simd simdlen(6) safelen(5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd safelen(5) simdlen(6)
  for (i = 0; i < 16; ++i)
    ;
}
void test_collapse() {
  int i;
#pragma omp parallel
#pragma omp for simd collapse
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4, , 4)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(4)
  for (int i1 = 0; i1 < 16; ++i1)
    for (int i2 = 0; i2 < 16; ++i2)
      for (int i3 = 0; i3 < 16; ++i3)
        for (int i4 = 0; i4 < 16; ++i4)
          foo();
#pragma omp parallel
#pragma omp for simd collapse(4, 8)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(2.5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(foo())
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(-5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(0)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(5 - 5)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd collapse(2)
  for (i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j)
#pragma omp for simd reduction(+ : i, j)
      for (int k = 0; k < 16; ++k)
        i += j;
}
void test_linear() {
  int i;
#pragma omp for simd linear(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(int)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(0)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
  int x, y;
#pragma omp for simd linear(x :)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x :, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x : 1)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x : 2 * 2)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x : 1, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x : 1, y, z : 1)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x) linear(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd private(x) linear(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x) private(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x, y : 0)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd linear(x) lastprivate(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(x) linear(x)
  for (i = 0; i < 16; ++i)
    ;
}
void test_aligned() {
  int i;
#pragma omp for simd aligned(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(int)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(0)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
  int *x, y, z[25];
#pragma omp for simd aligned(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(z)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x :)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x :, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x : 1)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x : 2 * 2)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x : 1, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x : 1, y, z : 1)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x) aligned(z, x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp for simd aligned(x, y, z) aligned(y, z)
  for (i = 0; i < 16; ++i)
    ;
}
void test_private() {
  int i;
#pragma omp parallel
#pragma omp for simd private(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(int)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(0)
  for (i = 0; i < 16; ++i)
    ;
  int x, y, z;
#pragma omp parallel
#pragma omp for simd private(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd private(x, y, z)
  for (i = 0; i < 16; ++i) {
    x = y * i + z;
  }
}
void test_lastprivate() {
  int i;
#pragma omp parallel
#pragma omp for simd lastprivate(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(int)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(0)
  for (i = 0; i < 16; ++i)
    ;
  int x, y, z;
#pragma omp parallel
#pragma omp for simd lastprivate(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
}
void test_firstprivate() {
  int i;
#pragma omp parallel
#pragma omp for simd firstprivate(
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd firstprivate(,
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd firstprivate(, )
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd firstprivate()
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd firstprivate(int)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd firstprivate(0)
  for (i = 0; i < 16; ++i)
    ;
  int x, y, z;
#pragma omp parallel
#pragma omp for simd lastprivate(x) firstprivate(x)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(x, y) firstprivate(x, y)
  for (i = 0; i < 16; ++i)
    ;
#pragma omp parallel
#pragma omp for simd lastprivate(x, y, z) firstprivate(x, y, z)
  for (i = 0; i < 16; ++i)
    ;
}
void test_loop_messages() {
  float a[100], b[100], c[100];
#pragma omp parallel
#pragma omp for simd
  for (float fi = 0; fi < 10.0; fi++) {
    c[(int)fi] = a[(int)fi] + b[(int)fi];
  }
#pragma omp parallel
#pragma omp for simd
  for (double fi = 0; fi < 10.0; fi++) {
    c[(int)fi] = a[(int)fi] + b[(int)fi];
  }
}
