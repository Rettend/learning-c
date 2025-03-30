#include <stdio.h>

// Printf

int main(void) {

  int a = 4;
  printf("%d\n", a);

  unsigned int b = 4;
  printf("%u\n", b);

  char c = 1;
  printf("%hhd\n", c);
  printf("%c\n", c);

  short d = 2;
  printf("%hd\n", d);

  long long e = 8;
  printf("%lld\n", e);

  float f = 4.0;
  printf("%f\n", f);

  int *p = &a;
  printf("%p\n", p);

  char *s = "asd";
  printf("%s\n", s);

  printf("%%\n");

  printf("%e\n", 1000.);
  printf("%e\n", 1000000.);
  printf("%g\n", 1000.);
  printf("%g\n", 1000000.);

  printf("#%5d#\n", 32);
  printf("#%-5d#\n", 32);
  printf("#%05d#\n", 32);

  printf("#% d#\n", 32);
  printf("#% d#\n", -32);
  printf("#%+d#\n", 32);
  printf("#%+d#\n", -32);

  printf("#%.2f#\n", 32.126);

  printf("#%*d#\n", 10, 32);
  printf("#%*.*f#\n", 10, 3, 32.);

  printf("%'ld\n", 1000000000000000000); // needs locale set

  size_t size = 2;
  printf("%zu", size);

  return 0;
}
