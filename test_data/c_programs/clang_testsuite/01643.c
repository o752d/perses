int printf(const char *, ...);
const char* f(const char *s) __attribute__((format_arg(1)));
void g(const char *s) {
  printf("%d", 123);
  printf("%d %d", 123);
  printf(f("%d"), 123);
  printf(f("%d %d"), 123);
}
