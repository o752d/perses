



void abort (void);

int test (int v)
{
  return ((signed char) (v ? 0x100 : 0)) ? 17 : 18;
}

int main()
{
  if (test (2) != 18)
    abort ();
  return 0;
}
