int f0() {
  int x;
  unsigned short n = 1;
  int *a = &x;
  int *b = &x;
  a = a - n;
  b -= n;
  return a == b;
}
int f1(int *a) {
  long b = a - (int*) 1;
  a -= (int*) 1;
  return b == (long) a;
}
int f2(long n) {
  int *b = n + (int*) 1;
  n += (int*) 1;
  return b == (int*) n;
}
