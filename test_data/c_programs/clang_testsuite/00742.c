struct A {
  char c;
  int i;
};
struct B {
  int c;
  unsigned char x;
};
union U { struct A a; struct B b; };
void check(union U *u, union U *v) {
  *u = *v;
}
