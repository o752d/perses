typedef void Void;
void foo() {
  int X;
  X = sizeof(int (void a));
  X = sizeof(int (int, void));
  X = sizeof(int (void, ...));
  X = sizeof(int (Void a));
  X = sizeof(int (int, Void));
  X = sizeof(int (Void, ...));
  X = sizeof(int (void));
  X = sizeof(int (Void));
}
void bar(Void) {
}
void f(const void);
