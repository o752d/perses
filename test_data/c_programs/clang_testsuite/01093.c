void abc(void *);
void Test5(double X) {
  abc(&X);
  {
    int X;
    abc(&X);
    {
      float X;
      abc(&X);
    }
  }
}
