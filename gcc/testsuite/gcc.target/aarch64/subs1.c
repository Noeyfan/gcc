/* { dg-do run } */
/* { dg-options "-O2 --save-temps -fno-inline" } */

extern void abort (void);

int
subs_si_test1 (int a, int b, int c)
{
  int d = a - c;

  /* { dg-final { scan-assembler "subs\tw\[0-9\]+, w\[0-9\]+, w\[0-9\]+" } } */
  if (d == 0)
    return a + c;
  else
    return b + d + c;
}

int
subs_si_test2 (int a, int b, int c)
{
  int d = a - 0xff;

  /* { dg-final { scan-assembler "subs\tw\[0-9\]+, w\[0-9\]+, #255" } } */
  if (d == 0)
    return a + c;
  else
    return b + d + c;
}

int
subs_si_test3 (int a, int b, int c)
{
  int d = a - (b << 3);

  /* { dg-final { scan-assembler "subs\tw\[0-9\]+, w\[0-9\]+, w\[0-9\]+, lsl 3" } } */
  if (d == 0)
    return a + c;
  else
    return b + d + c;
}

typedef long long s64;

s64
subs_di_test1 (s64 a, s64 b, s64 c)
{
  s64 d = a - c;

  /* { dg-final { scan-assembler "subs\tx\[0-9\]+, x\[0-9\]+, x\[0-9\]+" } } */
  if (d == 0)
    return a + c;
  else
    return b + d + c;
}

s64
subs_di_test2 (s64 a, s64 b, s64 c)
{
  s64 d = a - 0xff;

  /* { dg-final { scan-assembler "subs\tx\[0-9\]+, x\[0-9\]+, #255" } } */
  if (d == 0)
    return a + c;
  else
    return b + d + c;
}

s64
subs_di_test3 (s64 a, s64 b, s64 c)
{
  s64 d = a - (b << 3);

  /* { dg-final { scan-assembler "subs\tx\[0-9\]+, x\[0-9\]+, x\[0-9\]+, lsl 3" } } */
  if (d == 0)
    return a + c;
  else
    return b + d + c;
}

int main ()
{
  int x;
  s64 y;

  x = subs_si_test1 (29, 4, 5);
  if (x != 33)
    abort ();

  x = subs_si_test1 (5, 2, 20);
  if (x != 7)
    abort ();

  x = subs_si_test2 (29, 4, 5);
  if (x != -217)
    abort ();

  x = subs_si_test2 (1024, 2, 20);
  if (x != 791)
    abort ();

  x = subs_si_test3 (35, 4, 5);
  if (x != 12)
    abort ();

  x = subs_si_test3 (5, 2, 20);
  if (x != 11)
    abort ();

  y = subs_di_test1 (0x130000029ll,
		     0x320000004ll,
		     0x505050505ll);

  if (y != 0x45000002d)
    abort ();

  y = subs_di_test1 (0x5000500050005ll,
		     0x2111211121112ll,
		     0x0000000002020ll);
  if (y != 0x7111711171117)
    abort ();

  y = subs_di_test2 (0x130000029ll,
		     0x320000004ll,
		     0x505050505ll);
  if (y != 0x955050433)
    abort ();

  y = subs_di_test2 (0x130002900ll,
		     0x320000004ll,
		     0x505050505ll);
  if (y != 0x955052d0a)
    abort ();

  y = subs_di_test3 (0x130000029ll,
		     0x064000008ll,
		     0x505050505ll);
  if (y != 0x3790504f6)
    abort ();

  y = subs_di_test3 (0x130002900ll,
		     0x088000008ll,
		     0x505050505ll);
  if (y != 0x27d052dcd)
    abort ();

  return 0;
}

