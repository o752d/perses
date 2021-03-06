



typedef float vf2_t __attribute__((vector_size (8)));


typedef float vf4_t __attribute__((vector_size (16)));


typedef int vi4_t __attribute__((vector_size (16)));


typedef long double vlf1_t __attribute__((vector_size (16)));


union int128_t
{
  __int128 i;
  struct
    {
      signed long long l64;
      signed long long h64;
    };
};



struct hfa_fx1_t
{
  float a;
};

struct hfa_fx2_t
{
  float a;
  float b;
};

struct hfa_fx3_t
{
  float a;
  float b;
  float c;
};

struct hfa_dx2_t
{
  double a;
  double b;
};

struct hfa_dx4_t
{
  double a;
  double b;
  double c;
  double d;
};

struct hfa_ldx3_t
{
  long double a;
  long double b;
  long double c;
};

struct hfa_ffs_t
{
  float a;
  float b;
  struct hfa_fx2_t c;
};

union hfa_union_t
{
  struct
    {
      float a;
      float b;
    } s;
  float c;
};



struct non_hfa_fx5_t
{
  float a;
  float b;
  float c;
  float d;
  float e;
};

struct non_hfa_ffs_t
{
  float a;
  float b;
  struct hfa_dx2_t c;
};

struct non_hfa_ffs_2_t
{
  struct
    {
      int a;
      int b;
    } s;
  float c;
  float d;
};

struct hva_vf2x1_t
{
  vf2_t a;
};

struct hva_vf2x2_t
{
  vf2_t a;
  vf2_t b;
};

struct hva_vi4x1_t
{
  vi4_t a;
};

struct non_hfa_ffd_t
{
  float a;
  float b;
  double c;
};

struct non_hfa_ii_t
{
  int a;
  int b;
};

struct non_hfa_c_t
{
  char a;
};

struct non_hfa_ffvf2_t
{
  float a;
  float b;
  vf2_t c;
};

struct non_hfa_fffd_t
{
  float a;
  float b;
  float c;
  double d;
};

union non_hfa_union_t
{
  double a;
  float b;
};

struct x0
{
  char ch;
  int i;
} y0 = { 'a', 12345 };

struct x1
{
  int a;
  int b;
  int c;
  int d;
} y1 = { 0xdeadbeef, 0xcafebabe, 0x87654321, 0xabcedf975 };

struct x2
{
  long long a;
  long long b;
  char ch;
} y2 = { 0x12, 0x34, 0x56 };

union x3
{
  char ch;
  int i;
  long long ll;
} y3;

union x4
{
  int i;
  struct x2 y2;
} y4;

struct x5
{
  union int128_t qword;
} y5;


void init_data ()
{

  y3.ll = 0xfedcba98LL;


  y4.y2.a = 0x78;
  y4.y2.b = 0x89;
  y4.y2.ch= 0x9a;


  y5.qword.l64 = 0xfdb9753102468aceLL;
  y5.qword.h64 = 0xeca8642013579bdfLL;
}


enum aapcs64_test_kind
{
  TK_PARAM = 0,
  TK_VA_ARG,
  TK_RETURN
};

int which_kind_of_test;

extern int printf (const char*, ...);
extern void abort (void);
extern void dumpregs () __asm("myfunc");
enum structure_type
{
  flat = 0,
  i32in128,
  f32in64,
  i8in64,
  i16in64,
  i32in64,
};



typedef long unsigned int size_t;
int memcmp (void *, void *, size_t);



const int element_size[] = { 1, 4, 4, 1, 2, 4 };
const int block_reverse_size[] = { 1, 16, 8, 8, 8, 8 };

int
validate_memory (void *mem1, char *mem2, size_t size, enum structure_type type)
{
  unsigned int i;
  char *cmem1 = (char *) mem1;
  switch (type)
    {
    case f32in64:
    case i32in128:
    default:
      break;
    }
  return memcmp (mem1, mem2, size);
}
void testfunc(char* stack)
{


  { float __x = 1.0f; ; if (validate_memory (&__x, stack + 64, sizeof (float), flat) != 0) abort(); }

  { struct x0 __x = y0; ; if (validate_memory (&__x, stack + 128, sizeof (struct x0), flat) != 0) abort(); }
  { struct x1 __x = y1; ; if (validate_memory (&__x, stack + 136, sizeof (struct x1), flat) != 0) abort(); }
  { struct x2 * ptr; ; ptr = *(struct x2 **)(stack + 152); if (memcmp (ptr, &y2, sizeof (struct x2)) != 0) abort (); }
  { union x3 __x = y3; ; if (validate_memory (&__x, stack + 160, sizeof (union x3), flat) != 0) abort(); }
  { union x4 * ptr; ; ptr = *(union x4 **)(stack + 168); if (memcmp (ptr, &y4, sizeof (union x4)) != 0) abort (); }
  { struct x5 __x = y5; ; if (validate_memory (&__x, stack + 176, sizeof (struct x5), flat) != 0) abort(); }
  { struct x0 __x = y0; ; if (validate_memory (&__x, stack + 336, sizeof (struct x0), flat) != 0) abort(); }
  { struct x1 __x = y1; ; if (validate_memory (&__x, stack + 336 +8, sizeof (struct x1), flat) != 0) abort(); }
  { struct x2 * ptr; ; ptr = *(struct x2 **)(stack + 336 +24); if (memcmp (ptr, &y2, sizeof (struct x2)) != 0) abort (); }
  { union x3 __x = y3; ; if (validate_memory (&__x, stack + 336 +32, sizeof (union x3), flat) != 0) abort(); }
  { union x4 * ptr; ; ptr = *(union x4 **)(stack + 336 +40); if (memcmp (ptr, &y4, sizeof (union x4)) != 0) abort (); }

  { int __x = 1; ; if (validate_memory (&__x, stack + 336 +48, sizeof (int), flat) != 0) abort(); }



  { struct x5 __x = y5; ; if (validate_memory (&__x, stack + 336 +64, sizeof (struct x5), flat) != 0) abort(); }

  { int __x = 2; ; if (validate_memory (&__x, stack + 336 +80, sizeof (int), flat) != 0) abort(); }

  return;
}
typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;



__attribute__ ((noinline)) void
dummy_func (int w0, int w1, int w2, int w3, int w4, int w5, int w6, int w7,
     float s0, float s1, float s2, float s3, float s4, float s5,
     float s6, float s7)
{
  asm ("");
  return;
}


void myfunc(


  float,

  struct x0,
  struct x1,
  struct x2,
  union x3,
  union x4,
  struct x5,
  struct x0,
  struct x1,
  struct x2,
  union x3,
  union x4,

  int,



  struct x5,

  int

) ;






void stdarg_func(


  float _f65535,
  ...

)
{

  va_list ap;

  __builtin_va_start(ap, _f65535);;


  dummy_func (0, 0, 0, 0, 0, 0, 0, 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);


  __sync_synchronize ();
    {



  float _x65535 = _f65535;

  struct x0 _x1 = __builtin_va_arg(ap, struct x0);
  struct x1 _x2 = __builtin_va_arg(ap, struct x1);
  struct x2 _x3 = __builtin_va_arg(ap, struct x2);
  union x3 _x4 = __builtin_va_arg(ap, union x3);
  union x4 _x5 = __builtin_va_arg(ap, union x4);
  struct x5 _x6 = __builtin_va_arg(ap, struct x5);
  struct x0 _x7 = __builtin_va_arg(ap, struct x0);
  struct x1 _x8 = __builtin_va_arg(ap, struct x1);
  struct x2 _x9 = __builtin_va_arg(ap, struct x2);
  union x3 _x10 = __builtin_va_arg(ap, union x3);
  union x4 _x11 = __builtin_va_arg(ap, union x4);

  int _x12 = __builtin_va_arg(ap, int);



  struct x5 _x13 = __builtin_va_arg(ap, struct x5);

  int _x14 = __builtin_va_arg(ap, int);



      myfunc (


  _x65535,

  _x1,
  _x2,
  _x3,
  _x4,
  _x5,
  _x6,
  _x7,
  _x8,
  _x9,
  _x10,
  _x11,

  _x12,



  _x13,

  _x14

);
    }
  __builtin_va_end(ap);
}




int main()
{




  init_data ();






  which_kind_of_test = TK_VA_ARG;
  stdarg_func(



  1.0f,

  y0,
  y1,
  y2,
  y3,
  y4,
  y5,
  y0,
  y1,
  y2,
  y3,
  y4,

  1,



  y5,

  2

);
  return 0;
}

