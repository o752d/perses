


struct str
{
  unsigned a:1, b:1;
};

static struct str test;

unsigned foo(struct str *s)
{
  return s->a;
}

unsigned bar(struct str *s)
{
  return s->a;
}

int main()
{
  test.a = 0;
  test.b = 1;

  return foo (&test) == bar (&test);
}
