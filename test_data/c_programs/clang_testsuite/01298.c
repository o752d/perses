void *fail1(int a) __attribute__((alloc_size));
void *fail2(int a) __attribute__((alloc_size()));
void *fail3(int a) __attribute__((alloc_size(0)));
void *fail4(int a) __attribute__((alloc_size(2)));
void *fail5(int a, int b) __attribute__((alloc_size(0, 1)));
void *fail6(int a, int b) __attribute__((alloc_size(3, 1)));
void *fail7(int a, int b) __attribute__((alloc_size(1, 0)));
void *fail8(int a, int b) __attribute__((alloc_size(1, 3)));
int fail9(int a) __attribute__((alloc_size(1)));
int fail10 __attribute__((alloc_size(1)));
void *fail11(void *a) __attribute__((alloc_size(1)));
void *fail12(int a) __attribute__((alloc_size("abc")));
void *fail12(int a) __attribute__((alloc_size(1, "abc")));
void *fail13(int a) __attribute__((alloc_size(1U<<31)));
int (*PR31453)(int) __attribute__((alloc_size(1)));
