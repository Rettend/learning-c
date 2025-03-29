#include <stdio.h>

// Number literals

int main(void) {
  int a = 23;
  int b = 0xaa22ff;
  int c = 034;
  int d = 0b1010;

  printf("%d\n", a);
  printf("%x\n", b);
  printf("%o\n", c);
  printf("%b\n", d);

  return 0;
}
