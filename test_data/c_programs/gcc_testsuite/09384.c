





static inline unsigned
foo (void *x)
{
  unsigned y = *(volatile unsigned *) (x);
  return (y >> 24) | ((y >> 8) & 0xff00) | ((y & 0xff00) << 8) | (y << 24);
}

void
bar (void *x, void *y, int z)
{
  unsigned c;
  while (z--)
    {
      c = foo (y);
      *(unsigned *) x = (c & 0xf80000) >> 9 | (c & 0xf800) >> 6
   | (c & 0xf8) >> 3 | (c & 0x80000000) >> 16;
    }
}
