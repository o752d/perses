




int
f1(int x, int y, int z)
{
  if (x > 100)
    {
      x++;
      z = -z;
    }
  else
    {
      x = -x;
      y = -y;
    }
  return x + y + z;
}
