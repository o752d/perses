



extern void abort (void);
struct X {
  unsigned char pad : 4;
  unsigned int a : 32;
  unsigned int b : 24;
  unsigned int c : 6;
} __attribute__((packed));




int main (void)
{
  struct X x;
  unsigned int bad_bits;

  x.pad = -1;
  x.a = -1;
  x.b = -1;
  x.c = -1;

  bad_bits = ((unsigned int)-1) ^ *(1+(unsigned int *) &x);
  if (bad_bits != 0)
    abort ();
  return 0;
}
